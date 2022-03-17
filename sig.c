/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 23:09:18 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/17 17:40:04 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int sig)
{
	int	flag;
	int	i;

	flag = 1;
	i = 0;
	(void)sig;
	while (g_pid.size > 0 && i < g_pid.size)
	{
		if (g_pid.pid[i] != 0)
			flag = 0;
		++i;
	}
	if (flag)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 2);
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		write(2, "\n", 1);
}

void	sig_quit(int sig)
{
	int	flag;
	int	i;

	flag = 1;
	i = 0;
	while (g_pid.size > 0 && i < g_pid.size)
	{
		if (g_pid.pid[i] != 0)
			flag = 0;
		++i;
	}
	if (!flag)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putnbr_fd(sig, 2);
		ft_putendl_fd("", 2);
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 2);
	}
}

void	interrupt_delim(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", 2);
	write(2, "\n", 1);
	close(g_pid.in);
	close(g_pid.out);
	close(g_pid.fd);
	weird_close();
	fclose(stdout);
	fclose(stdin);
	fclose(stderr);
	exit(1);
}

int	next_pipe(t_prog *prog, int i)
{
	if (prog->err && pipe_size(prog) > 0)
	{
		g_pid.status[g_pid.index++] = -1;
		close_piptmp(prog);
		prog->ret = 1;
	}
	else if (prog->err)
	{
		g_pid.status[g_pid.index++] = -1;
		prog->ret = 1;
	}
	if (prog->redoutput)
		dup2(prog->out, 1);
	if (prog->redinput || prog->delim)
		dup2(prog->in, 0);
	prog->delim = 0;
	prog->redinput = 0;
	prog->redoutput = 0;
	while (prog->token[i])
	{
		if (prog->type[i] == PIPE)
			return (i);
		++i;
	}
	return (i - 1);
}

int	check_hyphen(char *line, int i)
{
	if (line[i] == '<' && line[i + 1] && line[i + 1] == '<'
		&& line[i + 2] && line[i + 2] == '-')
		return (1);
	return (0);
}
