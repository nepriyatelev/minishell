/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:26:59 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/10 19:41:12 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;

	if (*lst != NULL && del != NULL)
	{
		node = *lst;
		while (node)
		{
			ft_lstdelone(node, del);
			node = node->next;
		}
		*lst = NULL;
	}
}
