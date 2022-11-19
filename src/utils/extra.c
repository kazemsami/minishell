/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:46:04 by kabusitt          #+#    #+#             */
/*   Updated: 2022/11/19 19:57:36 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	set_default(t_prog *prog)
{
	prog->fdin = -1;
	prog->fdout = -1;
	prog->exec = 1;
	prog->pipnum = 0;
	prog->delim = 0;
	prog->redinput = 0;
	prog->redoutput = 0;
	g_pid.pipsize = 0;
	g_pid.size = 0;
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

int	print_error_d(char *str)
{
	struct stat	chk;

	if (stat(str, &chk) == 0)
	{
		if (chk.st_mode & S_IFDIR)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd(": is a directory", 2);
		}
		else
			print_cmd_error(str);
	}
	else
		print_cmd_error(str);
	if (!ft_strcmp("Permission denied", strerror(errno)))
		return (1);
	return (0);
}

void	fix_global(t_prog *prog)
{
	if (pipe_size(prog) > 0)
	{
		prog->exec = 0;
		pipe_init(prog);
		g_pid.pipfd = prog->pipfd;
		g_pid.pipsize = prog->pipes;
	}
	else
	{
		g_pid.pid = malloc(sizeof(int) * 1);
		g_pid.status = malloc(sizeof(int) * 1);
		g_pid.size = 1;
		g_pid.pid[0] = 1;
		g_pid.status[0] = 1;
	}
}

void	remove_quotes(char **cmd)
{
	char	*tmp;

	tmp = quotes_extra(*cmd);
	free(*cmd);
	*cmd = tmp;
}

char	*get_prompt(t_prog *prog)
{
	char	*ret;
	char	*tmp;
	char	*trunc;

	tmp = get_env("USER", prog);
	ret = ft_strjoin("\033[0;32m", tmp, 0);
	free(tmp);
	ret = ft_strjoin(ret, "@", 1);
	tmp = malloc(sizeof(char) * 100);
	gethostname(tmp, 100);
	trunc = ft_strchr(tmp, '.');
	*trunc = '\0';
	ret = ft_strjoin(ret, tmp, 1);
	free(tmp);
	ret = ft_strjoin(ret, ": \033[0;34m", 1);
	tmp = getcwd(NULL, 0);
	ret = ft_strjoin(ret, tmp, 1);
	free(tmp);
	ret = ft_strjoin(ret, "\033[0;37m$ ", 1);
	return (ret);
}
