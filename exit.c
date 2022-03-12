/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <anifanto@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:33:05 by anifanto          #+#    #+#             */
/*   Updated: 2022/03/07 11:03:39 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_full_exit(t_prog *prog)
{
	free_split(prog->env);
	free_split(prog->token);
	free(prog->type);
	exit(prog->ret);
}

static void	ft_print_error_exit(t_prog *prog)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(prog->token[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	prog->ret = 255;
}

static int	ft_check_digit(char *str)
{
	unsigned long long int	number;
	int						sign;

	sign = 1;
	number = 0;
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		number = (number * 10) + (*str - '0');
		str++;
	}
	if (number > 9223372036854775808U && sign == -1)
		return (0);
	else if (number > 9223372036854775807 && sign == 1)
		return (0);
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

void	ft_exit(t_prog *prog)
{
	if (prog->token[1])
	{
		if (!ft_check_digit(prog->token[1]))
			ft_print_error_exit(prog);
		else
		{
			prog->ret = ft_atoi_ms(prog->token[1]);
			if (prog->token[2])
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
	ft_full_exit(prog);
}
