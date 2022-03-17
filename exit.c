/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:33:05 by anifanto          #+#    #+#             */
/*   Updated: 2022/03/17 13:51:17 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_full_exit(t_prog *prog, char **cmd)
{
	free_split(prog->env);
	free_split(prog->token);
	free(prog->type);
	free(g_pid.pid);
	free(g_pid.status);
	free_split(cmd);
	close_std(prog, -1);
	exit(prog->ret);
}

static void	ft_print_error_exit(t_prog *prog, char **cmd)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	prog->ret = 255;
}

static int	ft_check_digit(char *str, int sign)
{
	unsigned long long		number;

	number = 0;
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (ft_strlen(str) > 19)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		number = (number * 10) + (*str - '0');
		if (number > 9223372036854775808U && sign == -1)
			return (0);
		else if (number > 9223372036854775807 && sign == 1)
			return (0);
		str++;
	}
	return (1);
}

static int	ft_atoi_ms(char *str)
{
	unsigned long long int	number;
	int						sign;

	sign = 1;
	number = 0;
	while (*str == 32 || *str == '\n' || *str == '\r'
		|| *str == '\t' || *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		number = (number * 10) + (*str - '0');
		str++;
	}
	return ((number * sign) % 256);
}

void	ft_exit(t_prog *prog, char **cmd)
{
	if (cmd[1])
	{
		if (!ft_check_digit(cmd[1], 1))
			ft_print_error_exit(prog, cmd);
		else
		{
			prog->ret = ft_atoi_ms(cmd[1]);
			if (cmd[2])
			{
				ft_putendl_fd("exit", 2);
				ft_putendl_fd("minishell: exit: too many arguments", 2);
				prog->ret = 1;
				return ;
			}
			else
				ft_putendl_fd("exit", 1);
		}
	}
	else
		ft_putendl_fd("exit", 1);
	ft_full_exit(prog, cmd);
}
