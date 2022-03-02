/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:24:26 by modysseu          #+#    #+#             */
/*   Updated: 2022/02/27 18:17:49 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*f_element;

	f_element = lst;
	count = 0;
	while (f_element != NULL)
	{
		f_element = f_element->next;
		count++;
	}
	return (count);
}
