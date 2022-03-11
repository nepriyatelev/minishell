/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:27:48 by modysseu          #+#    #+#             */
/*   Updated: 2021/10/15 18:32:45 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*f_element;

	f_element = lst;
	if (f != NULL)
	{
		while (f_element != NULL)
		{
			f(f_element->content);
			f_element = f_element->next;
		}
	}
}
