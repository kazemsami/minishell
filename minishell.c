/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:07:13 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/03 18:43:25 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pid	g_pid;

void	close_fds(t_prog *prog)
{
	if (prog->fdin > 0)
		close(prog->fdin);
	if (prog->fdout > 0)
		close(prog->fdout);
}

int	next_op(t_prog *prog, int i)
{
	while (prog->token[i])
	{
		if (check_type(prog, i, "RAIDP"))
			return (i);
		++i;
	}
	return (i - 1);
}

void	run_prog(t_prog *prog)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (prog->token[i])
	{
		while (check_type(prog, next_op(prog, z), "RAID"))
		{
			z = next_op(prog, z) + 1;
			redir(prog, z);
		}
		if ((i == 0 || (i > 0 && prog->type[i - 1] == PIPE))
			&& !prog->err && prog->type[i] == CMD)
			parse_exec(prog, i);
		i = next_pipe(prog, i) + 1;
		z = i;
		prog->pipnum++;
	}
}

void	shell(t_prog *prog)
{
	int	i;

	fix_global(prog);
	run_prog(prog);
	i = 0;
	while (i < g_pid.size)
	{
		waitpid(g_pid.pid[i], &g_pid.status[i], 0);
		if (g_pid.status[i])
			prog->ret = g_pid.status[i] / 256;
		++i;
	}
	reset_fd(prog);
	close_fds(prog);
	if (pipe_size(prog) > 0)
		free(prog->pipfd);
	free_split(prog->token);
	free(prog->type);
}

int	main(int argc, char **argv, char **envp)
{
	t_prog	prog;
	int		ret;

	prog.in = dup(0);
	prog.out = dup(1);
	(void)argc;
	(void)argv;
	prog.env = cpy_env(envp);
	g_pid.pid = NULL;
	g_pid.status = NULL;
	prog.ret = 0;
	ft_check_env(&prog, prog.env);
	while (1)
	{
		set_default(&prog);
		ret = parseline(&prog);
		if (ret == 1)
			break ;
		if (ret == 0 && check_token(&prog))
			shell(&prog);
	}
	free_split(prog.env);
	return (0);
}
