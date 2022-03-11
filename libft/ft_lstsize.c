/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:24:26 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/08 18:07:38 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*node;

	count = 0;
	if (lst != NULL)
	{
		node = lst;
		while (node != NULL)
		{
			node = node->next;
			count++;
		}
	}
	return (count);
}
