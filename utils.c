/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 04:53:50 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/15 17:01:19 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_tabs(char *line)
{
	char	*new;
	int		i;
	int		z;

	i = 0;
	while (line[i] == '\t')
		++i;
	z = 0;
	while (line[i])
	{
		++i;
		++z;
	}
	new = malloc(sizeof(char) * (z + 1));
	i -= z;
	z = 0;
	while (line[i])
		new[z++] = line[i++];
	new[z] = '\0';
	free(line);
	return (new);
}

void	redir(t_prog *prog, int z)
{
	if (prog->type[z - 1] == REDIR)
		redir_output(prog, prog->token[z], REDIR);
	else if (prog->type[z - 1] == APPEND)
		redir_output(prog, prog->token[z], APPEND);
	else if (prog->type[z - 1] == DELIM
		|| prog->type[z - 1] == DELIM_TAB)
		redir_delim(prog, prog->token[z], z);
	else if (prog->type[z - 1] == INPUT)
		redir_input(prog, prog->token[z]);
}

int	ft_searh_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int	dollar_am(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == 1 && (str[i + 1] == 1 || str[i + 1] == '\0'))
			++cnt;
		++i;
	}
	return (cnt);
}

void	do_env(char *str, int i, t_prog *prog, char **ret)
{
	char	*env;
	char	*var;

	env = env_name(str, i, env_len(str, i) + 2);
	var = get_env(env, prog);
	if (env)
		free(env);
	*ret = ft_strjoin(*ret, var, 1);
	if (var)
		free(var);
}
