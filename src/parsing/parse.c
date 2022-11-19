/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:57:38 by kabusitt          #+#    #+#             */
/*   Updated: 2022/11/19 17:37:05 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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
		if (line[i] == 1 && line[i + 1] && !c
			&& (line[i + 1] == '\'' || line[i + 1] == '\"'))
			(*cnt)--;
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
			if (line[i] != '\"' && line[i] != '\'')
				(*cnt)++;
		}
		if (line[i] == '\"' || line[i] == '\'')
			(*cnt)++;
		++i;
	}
}

int	parseline(t_prog *prog)
{
	char	*line;
	char	*read_line_print;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	read_line_print = get_prompt(prog);
	line = readline(read_line_print);
	free(read_line_print);
	if (!line)
	{
		readline_fix(prog, 0);
		return (1);
	}
	if (line[0])
	{
		return (do_parse(prog, line));
	}
	free(line);
	return (2);
}

void	parse_exec(t_prog *prog, int i)
{
	char	**cmd;

	cmd = parse_cmd(prog, i);
	if (cmd[0] && is_builtin(cmd[0]))
		builtin_chk(prog, cmd);
	else if (cmd[0])
		exec_cmd(prog, cmd);
	else
		g_pid.status[prog->pipnum] = -1;
	free_split(cmd);
}
