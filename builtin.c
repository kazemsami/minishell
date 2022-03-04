/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:33:15 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/04 18:09:32 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

void	builtin_exec(t_prog *prog, char **cmd)
{
	if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd(prog);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(prog);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		echo_cmd(prog, cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(prog, prog->env);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(prog, prog->env);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(prog, prog->env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(prog);
}

int	env_len(char *str, int i)
{
	int	len;

	len = 0;
	if (ft_isdigit(str[i]) || str[i] == '?')
		return (1);
	while ((str[i] && str[i] != 1) && (ft_isdigit(str[i]) || ft_isalpha(str[i])
			|| str[i] == '_'))
	{
		++i;
		++len;
	}
	return (len);
}

char	*env_name(char *str, int i, int len)
{
	char	*env;
	int		z;

	env = malloc(sizeof(char) * len);
	if (!env)
		return (NULL);
	z = 0;
	while (z < len - 2)
		env[z++] = str[i++];
	env[z++] = '=';
	env[z] = '\0';
	return (env);
}

char	*find_env(char *str, t_prog *prog, int i)
{
	char	*ret;
	char	tmp[2];

	ret = NULL;
	tmp[1] = '\0';
	while (str[i])
	{
		if (str[i] == 1 && str[i + 1] != '\0')
		{
			do_env(str, ++i, prog, &ret);
			i += env_len(str, i);
		}
		if (str[i])
		{
			if (str[i] == 1)
				tmp[0] = '$';
			else
				tmp[0] = str[i];
			ret = ft_strjoin(ret, tmp, 1);
			++i;
		}
	}
	return (ret);
}
