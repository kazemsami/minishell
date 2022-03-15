/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 22:59:30 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/15 18:02:12 by kabusitt         ###   ########.fr       */
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

char	*quotes_extra(char *str)
{
	char	*tmp;
	int		i;
	int		chk;
	int		z;

	tmp = malloc(sizeof(char) * (cnt_noquotes(str) + 1));
	i = 0;
	chk = 0;
	z = 0;
	while (str[i])
	{
		if (str[i] == '\"' && chk == 0)
			chk = 1;
		else if (str[i] == '\'' && chk == 0)
			chk = 2;
		else if (str[i] == '\"' && chk == 1)
			chk = 0;
		else if (str[i] == '\'' && chk == 2)
			chk = 0;
		else
			tmp[z++] = str[i];
		++i;
	}
	tmp[z] = '\0';
	return (tmp);
}

void	close_pip(t_prog *prog)
{
	int	pip;

	pip = prog->pipnum * 2;
	if (!prog->pipnum)
		close(prog->pipfd[0]);
	else if (prog->pipnum > 0 && prog->pipes != prog->pipnum)
	{
		close(prog->pipfd[pip]);
		close(prog->pipfd[pip - 1]);
	}
	else if (prog->pipes == prog->pipnum)
		close(prog->pipfd[pip - 1]);
}
