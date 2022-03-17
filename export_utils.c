/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:48:55 by anifanto          #+#    #+#             */
/*   Updated: 2022/03/17 13:51:05 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(char **env)
{
	int		i;
	int		index;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		index = 0;
		printf ("declare -x " );
		if (ft_strchr(env[i], '='))
			index = ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='));
		if (!index)
			printf("%s\n", env[i]);
		else
		{
			tmp = ft_substr(env[i], 0, index + 1);
			printf("%s\"%s\"\n", tmp, env[i] + index + 1);
			free(tmp);
		}
		i++;
	}
}

char	**ft_new_export_envp(t_prog *prog, char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc((ft_env_size(env) + 1) * sizeof(char *));
	if (!new_env)
	{
		ft_putendl_fd("error allocating memory", 2);
		prog->ret = 1;
		return (NULL);
	}
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**ft_distr_export(t_prog *prog, char **env)
{
	char	**new_env;
	char	*tmp;
	int		i;
	int		j;

	new_env = ft_new_export_envp(prog, env);
	i = 0;
	while (new_env[i])
	{
		j = 0;
		while (new_env[j + 1])
		{
			if (ft_strncmp(new_env[j], new_env[j + 1],
					ft_strlen(new_env[j])) > 0)
			{
				tmp = new_env[j];
				new_env[j] = new_env[j + 1];
				new_env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (new_env);
}

void	readline_fix(t_prog *prog, int i)
{
	if (i == 0)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_putendl_fd("\x1B[Aexit", 1);
	}
	else
	{
		ft_putstr_fd("\x1B[A", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	close_std(prog, -1);
}
