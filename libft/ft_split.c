/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:15:10 by kabusitt          #+#    #+#             */
/*   Updated: 2021/12/23 14:28:29 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*copy_string(char const *str, int cnt, int len)
{
	int		i;
	char	*cpy;

	cpy = malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (len > 0)
	{
		cpy[i] = str[cnt - len];
		++i;
		len--;
	}
	cpy[i] = '\0';
	return (cpy);
}

static int	malloc_size(char const *str, char c)
{
	int	i;
	int	done;
	int	cnt;

	cnt = 0;
	i = 0;
	done = 1;
	while (str[i])
	{
		if (str[i] == c && !done)
			done = 1;
		else if (str[i] != c && done)
		{
			++cnt;
			done = 0;
		}
		++i;
	}
	return (cnt);
}

static char	**split_words(char const *s, char c, char **s2, int strsize)
{
	int	i;
	int	word;
	int	str_l;

	i = 0;
	word = 0;
	str_l = 0;
	while (word < strsize)
	{
		while (s[i] && s[i] == c)
			++i;
		while (s[i] && s[i] != c)
		{
			++i;
			++str_l;
		}
		s2[word] = copy_string(s, i, str_l);
		str_l = 0;
		word++;
	}
	s2[word] = 0;
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		m_sz;

	if (!s)
		return (NULL);
	m_sz = malloc_size(s, c);
	strs = malloc(sizeof(char *) * (m_sz + 1));
	if (!strs)
		return (NULL);
	split_words(s, c, strs, m_sz);
	return (strs);
}
