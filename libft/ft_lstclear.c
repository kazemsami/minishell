/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabusitt <kabusitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:35:50 by kabusitt          #+#    #+#             */
/*   Updated: 2021/12/21 15:45:06 by kabusitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*uselst;

	if (lst)
	{
		if (*lst)
		{
			uselst = *lst;
			while (uselst)
			{
				tmp = uselst->next;
				ft_lstdelone(uselst, del);
				uselst = tmp;
			}
			*lst = NULL;
		}
	}
}
