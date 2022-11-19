/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 05:40:39 by kabusitt          #+#    #+#             */
/*   Updated: 2022/11/19 19:52:45 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	print_minishell(void)
{
	printf("\033[0;31m\n\n\n     #      #          #####     " \
	"#     #     #####     #####     #     #     " \
	"#######     #            #\n    # #    # #   " \
	"        #       # #   #       #      #       " \
	"   #     #     #           #            #\n  " \
	" #   #  #   #          #       #  #  #       " \
	"#       ##        #######     #######     #  " \
	"          #\n  #     ##     #         #      " \
	" #   # #       #         ##      #     #     " \
	"#           #            #\n #              #" \
	"        #       #    ##       #           #  " \
	"   #     #     #           #            #\n# " \
	"               #     #####     #     #     ##" \
	"###    #####      #     #     #######     ###" \
	"####      #######\n\n\n\n");
}

void	fix_env(t_prog *prog)
{
	int	z;
	int	chk;

	z = -1;
	while (prog->token[++z])
	{
		chk = z;
		if (ft_strchr(prog->token[z], 1))
		{
			expand(&(prog->token[z]), prog);
			if (prog->token[z][0] == '\0')
			{
				prog->token = remove_cmd(prog->token, z--);
			}
		}
		if (chk == z)
			remove_quotes(&(prog->token[z]));
	}
}

int	cnt_token(t_prog *prog, int i)
{
	int	cnt;

	cnt = 0;
	while (prog->token[i + 1] && prog->token[i + 2])
	{
		if (prog->type[i] == PIPE || prog->type[i + 1] == PIPE
			|| prog->type[i + 2] == PIPE)
			break ;
		if (prog->type[i] != ARG && prog->type[i] != CMD
			&& prog->type[i + 2] == ARG)
			cnt += 2;
		i++;
	}
	return (cnt);
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

void	print_cmd_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
}
