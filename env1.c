/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:27:18 by anifanto          #+#    #+#             */
/*   Updated: 2022/03/02 18:31:30 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_env(char **env, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (len == 1)
	{
		while (env[i])
		{
			if (env[i][0] == str[0] && env[i][1] == '=')
				return (i);
			i++;
		}
		return (-1);
	}
	while (env[i])
	{
		if (!ft_strncmp(str, env[i], len - 1))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	ft_env(t_prog *prog)
{
	int	i;

	i = 0;
	while (prog->env[i])
	{
		if (ft_strrchr(prog->env[i], '='))
		{
			printf("%s\n", prog->env[i]);
		}
		i++;
	}
	prog->ret = 0;
}

void	ft_add_new_env(t_prog *prog, char *str)
{
	char	**new_env;
	int		i;
	int		size;

	i = 0;
	size = ft_env_size(prog->env);
	new_env = (char **)malloc(sizeof(char *) * (size + 2));
	while (prog->env[i])
	{
		new_env[i] = prog->env[i];
		i++;
	}
	new_env[i] = ft_strdup(str);
	i++;
	new_env[i] = NULL;
	free(prog->env);
	prog->env = new_env;
}

void	ft_check_env(t_prog *prog, char **env)
{
	char	*nb_dep;
	int		tmp;

	tmp = ft_find_env(env, "SHLVL=");
	if (tmp >= 0)
	{
		nb_dep = ft_itoa((ft_atoi(env[tmp] + 6) + 1) % 200);
		free(prog->env[tmp]);
		prog->env[tmp] = NULL;
		prog->env[tmp] = ft_strjoin("SHLVL=", nb_dep, 0);
		free(nb_dep);
	}
	else
		ft_add_new_env(prog, "SHLVL=1");
	tmp = ft_find_env(env, "OLDPWD");
	if (tmp < 0)
	{
		ft_add_new_env(prog, "OLDPWD");
	}
}
