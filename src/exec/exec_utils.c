/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:54:44 by kabusitt          #+#    #+#             */
/*   Updated: 2022/11/19 19:54:45 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	check_delim(t_prog *prog, int z)
{
	while (check_type(prog, next_op(prog, z), "RAID"))
	{
		z = next_op(prog, z) + 1;
		if (prog->type[z - 1] == DELIM
			|| prog->type[z - 1] == DELIM_TAB)
			redir_delim(prog, prog->token[z], z);
	}
}
