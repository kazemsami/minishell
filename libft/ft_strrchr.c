/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:44:38 by kabusitt          #+#    #+#             */
/*   Updated: 2021/12/23 11:26:35 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*sv;

	c = c % 256;
	i = 0;
	sv = 0;
	while (s[i])
	{
		if (s[i] == c)
			sv = (char *)(s + i);
		++i;
	}
	if (s[i] == c)
		sv = (char *)(s + i);
	return (sv);
}