/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:47:00 by anifanto          #+#    #+#             */
/*   Updated: 2022/03/17 17:30:32 by kabusitt         ###   ########.fr       */
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

void	close_std(t_prog *prog, int fd)
{
	if (fd > 0)
		close(fd);
	if (prog->fdout > 0)
		close(prog->fdout);
	if (prog->fdin > 0)
		close(prog->fdin);
	if (prog->delim && pipe_size(prog) > 0)
		close_pipes(prog);
	close(prog->in);
	close(prog->out);
	fclose(stdout);
	fclose(stdin);
	fclose(stderr);
}

void	weird_close(void)
{
	int	i;
	int	sz;

	i = 0;
	sz = g_pid.pipsize * 2;
	while (i < sz)
		close(g_pid.pipfd[i++]);
}
