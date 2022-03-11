/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:24:54 by modysseu          #+#    #+#             */
/*   Updated: 2021/10/15 18:33:03 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*f_element;

	if (lst == NULL)
		return (NULL);
	f_element = lst;
	while (f_element->next != NULL)
		f_element = f_element->next;
	return (f_element);
}
