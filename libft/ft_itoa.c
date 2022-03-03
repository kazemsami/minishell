/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:37:04 by kabusitt          #+#    #+#             */
/*   Updated: 2021/12/21 18:57:34 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_size(long nbr)
{
	size_t	sz;

	sz = 0;
	if (nbr < 0)
	{
		sz++;
		nbr = -nbr;
	}
	while (nbr > 0)
	{
		nbr /= 10;
		sz++;
	}
	return (sz + 1);
}

static void	int_to_string(char *str, long nbr, size_t len)
{
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	str[len] = '\0';
	len--;
	while (nbr > 0)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	size_t	sz;
	long	nbr;
	char	*str;

	nbr = n;
	sz = check_size(nbr);
	if (n == 0)
		return (ft_strdup("0"));
	str = malloc(sizeof(char) * sz);
	if (!str)
		return (NULL);
	int_to_string(str, nbr, sz - 1);
	return (str);
}
