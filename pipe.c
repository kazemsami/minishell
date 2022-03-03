/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 00:10:45 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/03 15:59:13 by kabusitt         ###   ########.fr       */
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
		ft_putendl_fd("Failed to create file with that name", 2);
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
		ft_putstr_fd(file, 2);
		ft_putendl_fd(" : No such file or directory", 2);
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

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	fd = open(".tmpdelim", O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (fd == -1)
		return ;
	pid = fork();
	if (!pid)
		loop_delim(prog, delim, fd, index);
	waitpid(pid, NULL, 0);
	prog->delim = 1;
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
	ft_bzero(g_pid.pid, g_pid.size);
	ft_bzero(g_pid.status, g_pid.size);
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
		stat = execve(path, cmd, prog->env);
	}
	print_error_d(prog, path);
	close_pipes(prog);
	exit(stat);
}
