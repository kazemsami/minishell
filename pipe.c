/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:10:45 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/20 13:29:40 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_output(t_prog *prog, char *file, int type)
{
	if (prog->fdout > 0)
		close(prog->fdout);
	if (type == APPEND)
		prog->fdout = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		prog->fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (prog->fdout == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		prog->ret = 1;
		prog->err = 1;
		return ;
	}
	prog->redoutput = 1;
	dup2(prog->fdout, 1);
}

void	redir_input(t_prog *prog, char *file)
{
	if (prog->fdin > 0)
		close(prog->fdin);
	prog->fdin = open(file, O_RDONLY);
	if (prog->fdin == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		prog->ret = 1;
		prog->err = 1;
		return ;
	}
	prog->redinput = 1;
	dup2(prog->fdin, 0);
}

void	redir_delim(t_prog *prog, char *delim, int index)
{
	int		fd;
	int		pid;
	int		stat;

	stat = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	fd = open(".tmpdelim", O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (fd == -1)
		return ;
	g_pid.fd = fd;
	g_pid.in = prog->in;
	g_pid.out = prog->out;
	prog->delim = 1;
	pid = fork();
	if (!pid)
		loop_delim(prog, delim, fd, index);
	waitpid(pid, &stat, 0);
	if (stat != 0)
		prog->err = 1;
	dup_delim(fd);
	if (prog->type[next_op(prog, index)] == DELIM
		|| prog->type[next_op(prog, index)] == DELIM_TAB)
		dup2(prog->in, 0);
}

void	pipe_init(t_prog *prog)
{
	int	sz;
	int	i;
	int	*pfd;

	sz = pipe_size(prog);
	g_pid.size = sz + 1;
	g_pid.pid = malloc(sizeof(int) * (sz + 1));
	g_pid.status = malloc(sizeof(int) * (sz + 1));
	i = 0;
	while (i < g_pid.size)
	{
		g_pid.pid[i] = 1;
		g_pid.status[i] = 1;
		++i;
	}
	prog->pipes = sz;
	i = 0;
	pfd = malloc(sizeof(int) * (sz * 2));
	prog->pipfd = pfd;
	while (i < sz)
	{
		pipe(pfd + i * 2);
		++i;
	}
}

void	pipe_exec(t_prog *prog, char *path, char **cmd)
{
	int	pip;
	int	stat;

	stat = 0;
	if (prog->exec)
		stat = execve(path, cmd, prog->env);
	else
	{
		pip = prog->pipnum * 2;
		if (!prog->redoutput && prog->pipes != prog->pipnum)
			dup2(prog->pipfd[pip + 1], 1);
		if (!prog->delim && !prog->redinput && prog->pipnum > 0)
			dup2(prog->pipfd[pip - 2], 0);
		close_pip(prog);
		stat = execve(path, cmd, prog->env);
		close_pipes(prog);
	}
	print_error_d(path);
	close_std(prog, -1);
	exit(stat);
}
