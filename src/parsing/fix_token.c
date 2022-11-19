/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:43:56 by anifanto          #+#    #+#             */
/*   Updated: 2022/11/19 13:36:41 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

void	swap_token(t_prog *prog, int z, int i)
{
	char	*tmp;

	tmp = prog->token[z];
	prog->token[z] = prog->token[i + 2];
	prog->token[i + 2] = tmp;
	prog->type[z] = prog->type[i + 2];
}

static void	find_fix(t_prog *prog, int *i, int *z, int *cnt)
{
	int	chk;

	chk = 0;
	if (prog->type[*i] != CMD && prog->type[*i] != ARG
		&& prog->type[*i] != PIPE)
	{
		if (*z == 0)
			*z = *i;
		while (prog->token[*i + 2] && prog->type[*i + 2] == ARG)
		{
			swap_token(prog, (*z)++, (*i)++);
			chk = 1;
		}
		if (chk)
			(*cnt)++;
	}
}

void	fix_token(t_prog *prog)
{
	int		i;
	int		z;
	int		cnt;
	char	**sv;
	int		*sv_tmp;

	i = 0;
	z = 0;
	cnt = 0;
	sv = NULL;
	while (prog->token[i + 1] && prog->token[i + 2])
	{
		search_token(&sv, &sv_tmp, prog, i);
		find_fix(prog, &i, &z, &cnt);
		if ((!prog->token[i + 1] || !prog->token[i + 2]
				|| !prog->token[i + 3] || prog->type[i + 2] == PIPE) && sv)
		{
			sv = token_ret(prog, &cnt, z, &sv);
			sv = type_ret(prog, &cnt, z, &sv_tmp);
		}
		i++;
	}
}
