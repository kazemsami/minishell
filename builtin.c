/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:33:15 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/02 16:46:56 by anifanto         ###   ########.fr       */
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
	while (str[i] && str[i] != 1 && str[i] != '\'')
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
	int		fnd_quote;
	char	tmp[2];

	ret = NULL;
	fnd_quote = 0;
	tmp[1] = '\0';
	while (str[i])
	{
		if (str[i] == 1 && str[i + 1] != '\0')
		{
			fnd_quote = 0;
			do_env(str, ++i, prog, &ret);
			i += env_len(str, i) - 1;
		}
		tmp[0] = str[i];
		if (str[i] == 1 && str[i + 1] == '\0' && dollar_am(str) % 2)
			ret = ft_strjoin(ret, "$", 1);
		if (str[i] == '\'' && !fnd_quote)
			fnd_quote = 1;
		if (str[i] && str[i] != 1 && fnd_quote)
			ret = ft_strjoin(ret, tmp, 1);
		++i;
	}
	return (ret);
}
