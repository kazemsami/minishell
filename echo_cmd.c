/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 22:59:30 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/10 16:50:19 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(char *str)
{
	int	i;

	i = 2;
	if (!str[2])
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_cmd(t_prog *prog, char **cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 1) && check_flag(cmd[i]))
	{
		flag = 1;
		++i;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!flag)
		printf("\n");
	prog->ret = 0;
}

char	**remove_cmd(char **cmd, int pos)
{
	char	**new_cmd;
	int		i;
	int		size;

	size = ft_env_size(cmd);
	new_cmd = (char **)malloc(sizeof(char *) * size);
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (i < pos)
	{
		new_cmd[i] = cmd[i];
		++i;
	}
	while (i < size - 1)
	{
		new_cmd[i] = cmd[i + 1];
		i++;
	}
	free(cmd[pos]);
	new_cmd[i] = NULL;
	free(cmd);
	return (new_cmd);
}
