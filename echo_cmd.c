/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 22:59:30 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/02 17:00:00 by anifanto         ###   ########.fr       */
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
