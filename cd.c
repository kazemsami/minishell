/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:51:40 by anifanto          #+#    #+#             */
/*   Updated: 2022/03/03 15:19:11 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_env(t_prog *prog, char **env, char *tmp)
{
	char	*path;
	int		now_pwd;
	int		old_pwd;

	now_pwd = ft_find_env(env, "PWD=");
	old_pwd = ft_find_env(env, "OLDPWD");
	path = ft_get_pwd(prog);
	if (old_pwd >= 0)
	{
		free(env[old_pwd]);
		env[old_pwd] = ft_strjoin("OLDPWD=", tmp, 0);
	}
	if (now_pwd >= 0)
	{
		free(env[now_pwd]);
		env[now_pwd] = ft_strjoin("PWD=", path, 0);
	}
	free(path);
}

static void	ft_change_dir(char *str, t_prog *prog)
{
	int	fd;

	fd = 0;
	if (chdir(str) < 0)
	{
		fd = open(str, O_DIRECTORY);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		if (access(str, 0) < 0)
			ft_putendl_fd(": No such file or directory", 2);
		else if (fd < 0)
			ft_putendl_fd("Permission denied", 2);
		if (fd > 0)
			close(fd);
		prog->ret = 1;
	}
}

static void	ft_go_to_dir(const char *path, t_prog *prog)
{
	char	*tmp;
	char	*new_path;

	tmp = ft_strrchr(path, '/');
	new_path = ft_substr(path, 0, ft_strlen(path) - ft_strlen(tmp) + 1);
	if (!new_path)
	{
		ft_putendl_fd("error allocating memory", 2);
		prog->ret = 1;
		return ;
	}
	ft_change_dir(new_path, prog);
	free(new_path);
}

int	ft_find_home_env(t_prog *prog, char **env)
{
	int	i;

	i = 0;
	while (env[i] && (ft_strncmp("HOME=", env[i], 4) != 0))
	{
		if (env[i + 1])
			i++;
		else
		{
			ft_putendl_fd("minishell: cd: HOME not set\n", 2);
			prog->ret = 1;
			return (-1);
		}
	}
	return (i);
}

void	ft_cd(t_prog *prog, char **env)
{
	int		i;
	char	*home;
	char	*path;

	i = ft_find_home_env(prog, env);
	if (i < 0)
		return ;
	path = ft_get_pwd(prog);
	home = env[i] + 5;
	if (!prog->token[1])
		ft_change_dir(home, prog);
	else if (!ft_strncmp(prog->token[1], "..", 3)
		&& ft_strlen(prog->token[1]) == 2)
		ft_go_to_dir(path, prog);
	else
		ft_change_dir(prog->token[1], prog);
	ft_change_env(prog, env, path);
	free(path);
}
