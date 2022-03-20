/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:48:08 by anifanto          #+#    #+#             */
/*   Updated: 2022/03/20 14:04:45 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_export_error(t_prog *prog, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_' ))
			break ;
		i++;
	}
	if ((str[i] && str[i] != '=') || ft_isdigit(str[0]) || (str[0] == '='))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		prog->ret = 1;
		return (0);
	}
	return (1);
}

static int	ft_var_exist(char **env, char *var)
{
	int		i;
	int		size;

	i = 0;
	size = ft_strlen(var);
	if (size == 1)
	{
		while (env[i])
		{
			if (env[i][0] == var[0] && (env[i][1] == '=' || !env[i][1]))
				return (1);
			i++;
		}
		return (0);
	}
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], size - 1)
			&& (env[i][size] == '=' || !env[i][size]))
			return (1);
		i++;
	}
	return (0);
}

static	void	ft_update_var(t_prog *prog, char *str, char *var)
{
	int	i;
	int	j;

	i = 0;
	while (prog->env[i])
	{
		j = 0;
		while (prog->env[i][j] == var[j]
			&& (var[j] && prog->env[i][j] != '='))
			j++;
		if (str[j] == '=' && (prog->env[i][j] == '=' || !prog->env[i][j]))
		{
			free(prog->env[i]);
			prog->env[i] = NULL;
			prog->env[i] = ft_strdup(str);
			return ;
		}
		i++;
	}
}

void	ft_export(t_prog *prog, char **cmd)
{
	int		i;
	char	*var;
	char	**new_env;

	i = 1;
	if (!(cmd[i]))
	{
		new_env = ft_distr_export(prog, prog->env);
		if (new_env)
		{
			ft_print_export(new_env);
			free(new_env);
		}
	}
	while (cmd[i] && ft_check_export_error(prog, cmd[i]))
	{
		var = ft_substr(cmd[i], 0, ft_searh_index(cmd[i], '='));
		if (ft_var_exist(prog->env, var))
			ft_update_var(prog, cmd[i], var);
		else
			ft_add_new_env(prog, cmd[i]);
		free(var);
		i++;
	}
}
