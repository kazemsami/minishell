/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:01:50 by kabusitt          #+#    #+#             */
/*   Updated: 2022/02/18 04:46:49 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(t_prog *prog, int index)
{
	if (ft_strcmp(prog->token[index], ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(prog->token[index], ">") == 0)
		return (REDIR);
	else if (ft_strcmp(prog->token[index], "|") == 0)
		return (PIPE);
	else if (ft_strcmp(prog->token[index], "<") == 0)
		return (INPUT);
	else if (ft_strcmp(prog->token[index], "<<") == 0)
		return (DELIM);
	else if (ft_strcmp(prog->token[index], "<<-") == 0)
		return (DELIM_TAB);
	else if (index == 0 || prog->type[index - 1] > DELIM)
		return (CMD);
	else
		return (ARG);
}

int	check_type(t_prog *prog, int index, char *types)
{
	if (prog->type[index] == REDIR && ft_strchr(types, 'R'))
		return (1);
	else if (prog->type[index] == APPEND && ft_strchr(types, 'A'))
		return (1);
	else if (prog->type[index] == PIPE && ft_strchr(types, 'P'))
		return (1);
	else if (prog->type[index] == INPUT && ft_strchr(types, 'I'))
		return (1);
	else if ((prog->type[index] == DELIM || prog->type[index] == DELIM_TAB)
		&& ft_strchr(types, 'D'))
		return (1);
	else if (prog->type[index] == CMD && ft_strchr(types, 'C'))
		return (1);
	else if (prog->type[index] == ARG && ft_strchr(types, 'G'))
		return (1);
	return (0);
}

int	has_types(t_prog *prog, char *types)
{
	int	i;

	i = 0;
	while (prog->token[i])
	{
		if (check_type(prog, i, types))
			return (1);
		++i;
	}
	return (0);
}

int	check_token(t_prog *prog)
{
	int	i;

	i = 0;
	while (prog->token[i])
	{
		if (check_type(prog, i, "RAID")
			&& (!prog->token[i + 1] || check_type(prog, i + 1, "RAIDP")))
		{
			ft_putendl_fd("syntax error", 2);
			free_split(prog->token);
			free(prog->type);
			return (0);
		}
		else if (check_type(prog, i, "P")
			&& (!i || !prog->token[i + 1] || check_type(prog, i + 1, "RAIDP")))
		{
			ft_putendl_fd("syntax error", 2);
			free_split(prog->token);
			free(prog->type);
			return (0);
		}
		++i;
	}
	return (1);
}
