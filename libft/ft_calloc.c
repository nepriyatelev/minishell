/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:32:50 by modysseu          #+#    #+#             */
/*   Updated: 2021/10/13 14:11:50 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*dst;
	size_t			total;
	unsigned int	i;

	total = size * count;
	dst = malloc(sizeof(char) * total);
	if (!dst)
		return (NULL);
	i = 0;
	while (total--)
	{	
		dst[i] = 0;
		i++;
	}
	return ((void *)dst);
}
