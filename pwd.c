/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:47:00 by anifanto          #+#    #+#             */
/*   Updated: 2022/03/01 15:47:03 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(t_prog *prog)
{
	char	*path;

	path = malloc(sizeof(char) * MAX_CH);
	if (!path)
	{
		ft_putendl_fd("error allocating memory", 2);
		prog->ret = 1;
		return (0);
	}
	if (getcwd(path, MAX_CH))
		return (path);
	else
	{
		free(path);
		prog->ret = 1;
		return (NULL);
	}
}

void	ft_pwd(t_prog *prog)
{
	char	*path;

	path = ft_get_pwd(prog);
	if (path)
	{
		printf("%s\n", path);
		free(path);
		prog->ret = 0;
		return ;
	}
	prog->ret = 1;
	return ;
}
