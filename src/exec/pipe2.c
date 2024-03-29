/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:23:17 by kabusitt          #+#    #+#             */
/*   Updated: 2022/11/19 19:13:50 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	pipe_size(t_prog *prog)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (prog->token[i])
	{
		if (prog->type[i] == PIPE)
			++cnt;
		++i;
	}
	return (cnt);
}

void	close_pipes(t_prog *prog)
{
	int	i;
	int	sz;

	sz = prog->pipes * 2;
	i = 0;
	while (i < sz)
		close(prog->pipfd[i++]);
}

void	close_piptmp(t_prog *prog)
{
	int	pip;

	pip = prog->pipnum * 2;
	if (prog->pipnum != 0)
		close(prog->pipfd[pip - 2]);
	if (prog->pipes != prog->pipnum)
		close(prog->pipfd[pip + 1]);
}

void	builtin_pipe(t_prog *prog)
{
	int	pip;

	pip = prog->pipnum * 2;
	close_pip(prog);
	if (prog->pipes != prog->pipnum && !prog->redoutput)
		dup2(prog->pipfd[pip + 1], 1);
	if (prog->pipnum > 0 && !prog->redinput)
		dup2(prog->pipfd[pip - 2], 0);
}

void	reset_fd(t_prog *prog)
{
	dup2(prog->in, 0);
	dup2(prog->out, 1);
}
