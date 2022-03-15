/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:22:58 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/15 14:27:53 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_size(char *line)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	skip_space(line, &i);
	while (line[i])
	{
		if (skip_notsep(line, &i) > 0)
			cnt++;
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			if ((line[i] == '>' && line[i + 1] && line[i + 1] == '>')
				|| (line[i] == '<' && line[i + 1] && line[i + 1] == '<'))
			{
				if (check_hyphen(line, i))
					++i;
				++i;
			}
			++cnt;
			++i;
		}
		skip_space(line, &i);
	}
	return (cnt);
}

int	str_size(char *line, int i)
{
	int	cnt;

	cnt = 0;
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
	{
		++cnt;
		if ((line[i] == '>' && line[i + 1] && line[i + 1] == '>')
			|| (line[i] == '<' && line[i + 1] && line[i + 1] == '<'))
		{
			++cnt;
			if (line[i] == '<' && line[i + 1] && line[i + 1] == '<'
				&& line[i + 2] && line[i + 2] == '-')
				++cnt;
		}
	}
	else
		cnt_notsep(line, i, &cnt);
	return (cnt);
}

void	cpy_str(char *line, char *str, int *i, int *z)
{
	char	c;

	c = 0;
	while (line[*i])
	{
		if (line[*i] == 1 && line[(*i) + 1] && !c
			&& (line[(*i) + 1] == '\'' || line[(*i) + 1] == '\"'))
			;
		else if (!c && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[*i];
		else if (c == line[*i])
			c = 0;
		else if (line[*i] == ' ' && !c)
			break ;
		else
		{
			if ((line[*i] == '>' || line[*i] == '|' || line[*i] == '<') && !c)
				break ;
			if (line[*i] != '\"' && line[*i] != '\'')
				str[(*z)++] = line[*i];
		}
		if (line[*i] == '\"' || line[*i] == '\'')
			str[(*z)++] = line[*i];
		(*i)++;
	}
}

char	*find_token(char *line, int *i)
{
	char	*str;
	int		z;

	str = malloc(sizeof(char) * (str_size(line, *i) + 1));
	if (!str)
		return (NULL);
	z = 0;
	if (line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
	{
		str[z++] = line[(*i)++];
		if ((line[(*i) - 1] == '>' && line[*i] && line[*i] == '>')
			|| (line[(*i) - 1] == '<' && line[*i] && line[*i] == '<'))
		{
			str[z++] = line[(*i)++];
			if (check_hyphen(line, *i - 2))
				str[z++] = line[(*i)++];
		}
		str[z] = '\0';
	}
	else
	{
		cpy_str(line, str, i, &z);
		str[z] = '\0';
	}
	return (str);
}

void	get_token(char *line, t_prog *prog)
{
	int		i;
	int		z;

	prog->token = malloc(sizeof(char *) * (token_size(line) + 1));
	prog->type = malloc(sizeof(char *) * token_size(line));
	i = 0;
	z = 0;
	skip_space(line, &i);
	while (line[i])
	{
		prog->token[z] = find_token(line, &i);
		skip_space(line, &i);
		++z;
	}
	prog->token[z] = 0;
	fix_token(prog);
	fix_type(prog);
}
