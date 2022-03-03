/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 12:16:11 by kabusitt          #+#    #+#             */
/*   Updated: 2021/12/23 12:45:40 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dststr;
	const char	*srcstr;

	if (n == 0 || dst == src)
		return (dst);
	if (!dst && !src)
		return (NULL);
	i = 0;
	dststr = (char *)dst;
	srcstr = (const char *)src;
	while (i < n)
	{
		dststr[i] = srcstr[i];
		++i;
	}
	return (dst);
}
