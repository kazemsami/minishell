/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:43:56 by anifanto          #+#    #+#             */
/*   Updated: 2022/03/01 15:47:57 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_prog *prog, int i)
{
	if (!ft_strcmp(prog->token[i], "<")
		|| !ft_strcmp(prog->token[i], "<<")
		|| !ft_strcmp(prog->token[i], ">"))
		return (1);
	return (0);
}

int	cnt_fix(t_prog *prog, int i)
{
	int	cnt;

	cnt = 0;
	while (prog->token[i] && ft_strcmp(prog->token[i], "|") != 0)
	{
		++i;
		++cnt;
	}
	return (cnt);
}

void	swap_tokens(t_prog *prog, int i)
{
	char	*tmp;
	int		sv;
	int		times;

	sv = i;
	times = 0;
	while (times < 2)
	{
		tmp = prog->token[i];
		while (prog->token[i + 1] && ft_strcmp(prog->token[i + 1], "|") != 0)
		{
			prog->token[i] = prog->token[i + 1];
			++i;
		}
		prog->token[i] = tmp;
		i = sv;
		times++;
	}
}

void	fix_token(t_prog *prog)
{
	int		i;

	i = 0;
	while (prog->token[i])
	{
		if ((i == 0 && is_redir(prog, i))
			|| (i > 0 && !ft_strcmp(prog->token[i - 1], "|")
				&& is_redir(prog, i)))
		{
			if (cnt_fix(prog, i) > 2)
				swap_tokens(prog, i);
		}
		++i;
	}
}

void	fix_type(t_prog *prog)
{
	int	i;

	i = 0;
	while (prog->token[i])
	{
		prog->type[i] = get_type(prog, i);
		++i;
	}
}
