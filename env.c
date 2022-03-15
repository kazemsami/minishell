/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:39:21 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/15 17:00:58 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cpy_env(char **env)
{
	char	**new;
	int		i;

	i = 0;
	while (env[i])
		++i;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		++i;
	}
	new[i] = 0;
	return (new);
}

int	check_quotes(char *line)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (line[i])
	{
		if (line[i] == '\"' && quotes == 0)
			quotes = 1;
		else if (line[i] == '\"' && quotes == 1)
			quotes = 0;
		else if (line[i] == '\'' && quotes == 0)
			quotes = 2;
		else if (line[i] == '\'' && quotes == 2)
			quotes = 0;
		if (line[i] == '$' && (quotes == 1 || quotes == 0))
			line[i] = 1;
		++i;
	}
	return (quotes);
}

char	*find_not_env(char *str, int *z)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i] && str[i] != 1)
		i++;
	if (i < 1)
		return (NULL);
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	*z = i;
	i = 0;
	while (str[i] && str[i] != 1)
	{
		new[i] = str[i];
		++i;
	}
	new[i] = '\0';
	return (new);
}

void	expand(char **cmd, t_prog *prog)
{
	char	*tmp;
	char	*expan;
	int		i;

	i = 0;
	tmp = find_not_env(*cmd, &i);
	expan = find_env(*cmd, prog, i);
	free(*cmd);
	*cmd = ft_strjoin(tmp, expan, 0);
	if (tmp)
		free(tmp);
	if (expan)
		free(expan);
}

char	*find_env(char *str, t_prog *prog, int i)
{
	char	*ret;
	char	tmp[2];

	ret = NULL;
	tmp[1] = '\0';
	while (str[i])
	{
		if (str[i] == 1 && str[i + 1] != '\0')
		{
			do_env(str, ++i, prog, &ret);
			i += env_len(str, i);
		}
		else if (str[i])
		{
			if (str[i] == 1)
				tmp[0] = '$';
			else
				tmp[0] = str[i];
			ret = ft_strjoin(ret, tmp, 1);
			++i;
		}
	}
	return (ret);
}
