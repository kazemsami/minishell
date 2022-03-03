/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:46:04 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/03 20:16:27 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_default(t_prog *prog)
{
	prog->fdin = -1;
	prog->fdout = -1;
	prog->exec = 1;
	prog->err = 0;
	prog->pipnum = 0;
	prog->delim = 0;
	prog->redinput = 0;
	prog->redoutput = 0;
	g_pid.size = 0;
	g_pid.index = 0;
	if (g_pid.pid)
		free(g_pid.pid);
	if (g_pid.status)
		free(g_pid.status);
}

void	print_error_d(t_prog *prog, char *str)
{
	if (errno == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		prog->ret = 127;
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": is a directory", 2);
		prog->ret = 126;
	}
}

void	fix_global(t_prog *prog)
{
	if (pipe_size(prog) > 0)
	{
		prog->exec = 0;
		pipe_init(prog);
	}
	else
	{
		g_pid.pid = malloc(sizeof(int) * 1);
		g_pid.status = malloc(sizeof(int) * 1);
		g_pid.size = 1;
		ft_bzero(g_pid.pid, 1);
		ft_bzero(g_pid.status, 1);
	}
}
