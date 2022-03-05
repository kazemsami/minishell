/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:45:48 by anifanto          #+#    #+#             */
/*   Updated: 2022/03/02 18:22:16 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_unset_error(t_prog *prog, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_' ))
			break ;
		i++;
	}
	if (str[i] || ft_isdigit(str[0]))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" ': not a valid identifier", 2);
		prog->ret = 1;
		return (0);
	}
	return (1);
}

static	char	**ft_change_unset_env(t_prog *prog, char **env, int tmp)
{
	char	**new_env;
	int		i;
	int		size;

	i = -1;
	size = ft_env_size(env);
	new_env = (char **)malloc(sizeof(char *) * size);
	if (!new_env)
	{
		ft_putendl_fd("error allocating memory", 2);
		prog->ret = 1;
		return (NULL);
	}
	while (++i < tmp)
		new_env[i] = env[i];
	while (i++ < size - 1)
		new_env[i - 1] = env[i];
	new_env[i] = NULL;
	free(env);
	return (new_env);
}

int	ft_check_variable(char *com, char *env)
{
	int	i;

	i = 0;
	while (com[i] == env[i] && com[i])
		i++;
	if (!com[i] && (!env[i] || env[i] == '='))
		return (1);
	return (0);
}

void	ft_unset(t_prog *prog, char **env)
{
	int	tmp;
	int	i;

	i = 1;
	if (!(env) || !(prog->token[i]))
		return ;
	while (prog->token[i] && ft_check_unset_error(prog, prog->token[i]))
	{
		tmp = ft_find_env(env, prog->token[i]);
		if (tmp >= 0)
		{
			if (ft_check_variable(prog->token[i], env[tmp]))
				prog->env = ft_change_unset_env(prog, prog->env, tmp);
		}
		i++;
	}
}
