/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 13:32:36 by kabusitt          #+#    #+#             */
/*   Updated: 2021/12/21 19:07:10 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*dststr;
	const char	*srcstr;

	if (dst == src)
		return (dst);
	dststr = (char *)dst;
	srcstr = (const char *)src;
	if (srcstr < dststr)
	{
		while (len--)
			dststr[len] = srcstr[len];
		return (dst);
	}
	i = 0;
	while (i < len)
	{
		dststr[i] = srcstr[i];
		++i;
	}
	return (dst);
}
