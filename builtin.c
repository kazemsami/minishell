/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <anifanto@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:33:15 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/13 16:19:08 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp_lu(cmd, "cd")
		|| !ft_strcmp_lu(cmd, "echo") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp_lu(cmd, "env") || !ft_strcmp_lu(cmd, "pwd"))
		return (1);
	return (0);
}

void	builtin_exec(t_prog *prog, char **cmd)
{
	if (ft_strcmp_lu(cmd[0], "pwd") == 0)
		ft_pwd(prog);
	else if (ft_strcmp_lu(cmd[0], "env") == 0)
		ft_env(prog);
	else if (ft_strcmp_lu(cmd[0], "echo") == 0)
		echo_cmd(prog, cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(prog, cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(prog, cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(prog, prog->env, cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(prog, cmd);
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

int	ft_strcmp_lu(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i] || s1[i] + 32 == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}
