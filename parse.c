/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:38 by kabusitt          #+#    #+#             */
/*   Updated: 2022/03/03 18:43:38 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_space(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\f'
		|| line[*i] == '\v' || line[*i] == '\r')
		(*i)++;
}

int	skip_notsep(char *line, int *i)
{
	int		z;
	char	c;

	z = 0;
	c = 0;
	while (line[*i] && ((line[*i] != '>' && line[*i] != '<'
				&& line[*i] != '|') || c))
	{
		if (!c && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[*i];
		else if (c == line[*i])
			c = 0;
		if (line[*i] == ' ' && !c)
			break ;
		(*i)++;
		z++;
	}
	return (z);
}

void	cnt_notsep(char *line, int i, int *cnt)
{
	char	c;

	c = 0;
	while (line[i])
	{
		if (!c && (line[i] == '\'' || line[i] == '\"'))
			c = line[i];
		else if (c == line[i])
			c = 0;
		else if (line[i] == ' ' && !c)
			break ;
		else
		{
			if ((line[i] == '>' || line[i] == '|' || line[i] == '<') && !c)
				break ;
			(*cnt)++;
		}
		++i;
	}
}

int	parseline(t_prog *prog)
{
	char	*line;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	line = readline("Minishell> ");
	if (!line)
	{
		printf("\n");
		return (1);
	}
	if (line[0])
	{
		add_history(line);
		if (check_quotes(line) != 0)
		{
			ft_putendl_fd("error open quotes", 2);
			free(line);
			return (2);
		}
		get_token(line, prog);
		free(line);
		return (0);
	}
	free(line);
	return (2);
}

void	parse_exec(t_prog *prog, int i)
{
	char	**cmd;
	int		z;

	cmd = parse_cmd(prog, i);
	z = 0;
	while (cmd[z])
	{
		if (ft_strchr(cmd[z], 1))
			expand(&cmd[z], prog);
		++z;
	}
	if (is_builtin(cmd[0]))
		builtin_chk(prog, cmd);
	else
		exec_cmd(prog, cmd);
	free_split(cmd);
	prog->delim = 0;
	prog->redinput = 0;
	prog->redoutput = 0;
}
