/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:18:44 by kabusitt          #+#    #+#             */
/*   Updated: 2021/12/23 13:00:03 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	str_l;
	char	*str;

	if (!s)
		return (NULL);
	str_l = ft_strlen(s);
	i = 0;
	if ((size_t)(start) > str_l)
		return (ft_strdup(""));
	if ((size_t)start < str_l)
		i = str_l - start;
	if (i > len)
		i = len;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, i + 1);
	return (str);
}
