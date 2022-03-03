/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:53:09 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/03 16:20:20 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i++]);
	}
	free(strs);
}

char	*find_bin(char *bin, char *cmd)
{
	struct dirent	*obj;
	DIR				*dir;
	char			*path;
	char			*tmp;

	dir = opendir(bin);
	if (!dir)
		return (NULL);
	path = NULL;
	obj = readdir(dir);
	while (obj)
	{
		if (ft_strcmp(obj->d_name, cmd) == 0)
		{
			tmp = ft_strjoin(bin, "/", 0);
			path = ft_strjoin(tmp, obj->d_name, 0);
			free(tmp);
			break ;
		}
		obj = readdir(dir);
	}
	closedir(dir);
	return (path);
}

void	fork_and_exec(char *path, char **cmd, t_prog *prog)
{
	if (ft_strchr(path, '/') != NULL)
	{
		g_pid.pid[g_pid.index] = fork();
		if (g_pid.pid[g_pid.index] == 0)
			pipe_exec(prog, path, cmd);
		close_piptmp(prog);
		g_pid.index++;
	}
	else
		print_error_c(prog, path);
}

int	exec_cmd(t_prog *prog, char **cmd)
{
	int		i;
	char	**bin;
	char	*path;

	i = 0;
	while (prog->env[i] && ft_strncmp(prog->env[i], "PATH=", 4) != 0)
		++i;
	if (!prog->env[i])
	{
		fork_and_exec(cmd[0], cmd, prog);
		return (0);
	}
	bin = ft_split(prog->env[i], ':');
	path = find_bin(bin[0] + 5, cmd[0]);
	i = 1;
	while (bin[i] && path == NULL)
		path = find_bin(bin[i++], cmd[0]);
	if (!path)
		fork_and_exec(cmd[0], cmd, prog);
	else
		fork_and_exec(path, cmd, prog);
	free_split(bin);
	free(path);
	return (0);
}

char	**parse_cmd(t_prog *prog, int i)
{
	char	**cmd;
	int		z;
	int		y;

	z = 0;
	while (prog->token[i] && !check_type(prog, i, "RAIDP"))
	{
		++z;
		++i;
	}
	cmd = malloc(sizeof(char *) * (z + 1));
	if (!cmd)
		return (NULL);
	i -= z;
	y = 0;
	while (y < z)
	{
		cmd[y++] = ft_strdup(prog->token[i++]);
	}
	cmd[y] = 0;
	return (cmd);
}
