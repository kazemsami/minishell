/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:46:04 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/10 16:17:06 by kabusitt         ###   ########.fr       */
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
	{
		free(g_pid.pid);
		g_pid.pid = NULL;
	}
	if (g_pid.status)
	{
		free(g_pid.status);
		g_pid.status = NULL;
	}
}

void	print_error_d(char *str)
{
	if (errno == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": is a directory", 2);
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

char	*rmv_quote(char *str, int i)
{
	char	*new;
	int		z;
	int		a;

	new = malloc(sizeof(char) * ft_strlen(str));
	if (!new)
		return (NULL);
	a = 0;
	z = 0;
	while (str[a])
	{
		if (a == i)
			a++;
		new[z++] = str[a++];
	}
	new[z] = '\0';
	free(str);
	return (new);
}

char	*fandr_quotes(char *str)
{
	int		i;
	int		chk;
	char	*tmp;

	i = -1;
	tmp = ft_strdup(str);
	chk = 0;
	while (tmp[++i])
	{
		if (tmp[i] == '\"' && chk == 0)
		{
			chk = 1;
			tmp = rmv_quote(tmp, i--);
		}
		else if (tmp[i] == '\'' && chk == 0)
			chk = 2;
		else if (tmp[i] == '\"' && chk == 1)
		{
			chk = 0;
			tmp = rmv_quote(tmp, i--);
		}
		else if (tmp[i] == '\'' && chk == 2)
			chk = 0;
	}
	return (tmp);
}
