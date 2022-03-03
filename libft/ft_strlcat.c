/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:00:28 by kabusitt          #+#    #+#             */
/*   Updated: 2022/01/07 13:59:55 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	z;

	i = 0;
	z = 0;
	while (dst[i])
		++i;
	if (dstsize < i)
	{
		while (src[z])
			++z;
		return (dstsize + z);
	}
	while (dstsize > 0 && src[z] && i < dstsize - 1)
	{
		dst[i++] = src[z++];
	}
	dst[i] = '\0';
	while (src[z++])
		++i;
	return (i);
}

char	*ft_strcat(char *dest, const char *src)
{
	int			len;
	int			i;

	i = 0;
	len = ft_strlen(dest);
	while (src[i])
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[len + i] = '\0';
	return (dest);
}
