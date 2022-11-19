/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:19:47 by kabusitt          #+#    #+#             */
/*   Updated: 2022/11/19 19:53:18 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	*find_type(t_prog *prog, int i)
{
	int	cnt;
	int	*ret;

	cnt = cnt_token(prog, i);
	if (cnt == 0)
		return (NULL);
	ret = malloc(sizeof(int) * (cnt));
	cnt = 0;
	while (prog->token[i + 1] && prog->token[i + 2])
	{
		if (prog->type[i] == PIPE || prog->type[i + 1] == PIPE
			|| prog->type[i + 2] == PIPE)
			break ;
		if (prog->type[i] != ARG && prog->type[i] != CMD
			&& prog->type[i + 2] == ARG)
		{
			ret[cnt++] = prog->type[i++];
			ret[cnt++] = prog->type[i];
		}
		i++;
	}
	return (ret);
}

static char	**find_token(t_prog *prog, int i)
{
	int		cnt;
	char	**ret;

	cnt = cnt_token(prog, i);
	if (cnt == 0)
		return (NULL);
	ret = malloc(sizeof(char *) * (cnt + 1));
	cnt = 0;
	while (prog->token[i + 1] && prog->token[i + 2])
	{
		if (prog->type[i] == PIPE || prog->type[i + 1] == PIPE
			|| prog->type[i + 2] == PIPE)
			break ;
		if (prog->type[i] != ARG && prog->type[i] != CMD
			&& prog->type[i + 2] == ARG)
		{
			ret[cnt++] = ft_strdup(prog->token[i++]);
			ret[cnt++] = ft_strdup(prog->token[i]);
		}
		i++;
	}
	ret[cnt] = 0;
	return (ret);
}

void	search_token(char ***sv, int **sv_tmp, t_prog *prog, int i)
{
	if (!(*sv))
	{
		*sv = find_token(prog, i);
		*sv_tmp = find_type(prog, i);
	}
}

char	**token_ret(t_prog *prog, int *cnt, int i, char ***sv)
{
	int	z;

	z = 0;
	while (z < (*cnt * 2))
	{
		free(prog->token[i]);
		prog->token[i++] = ft_strdup((*sv)[z++]);
	}
	free_split(*sv);
	return (NULL);
}

char	**type_ret(t_prog *prog, int *cnt, int i, int **sv_tmp)
{
	int	z;

	z = 0;
	while (z < (*cnt * 2))
	{
		prog->type[i++] = (*sv_tmp)[z++];
	}
	free(*sv_tmp);
	*cnt = 0;
	return (NULL);
}
