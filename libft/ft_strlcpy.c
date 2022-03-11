/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:16:39 by modysseu          #+#    #+#             */
/*   Updated: 2021/10/10 15:34:09 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_size;

	i = 0;
	j = 0;
	src_size = 0;
	while (src[src_size])
		src_size++;
	if (dstsize == 0)
		return (src_size);
	while (src[i] != '\0')
	{
		if (i < (dstsize - 1))
		{	
			dst[i] = src[j];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	return (i);
}
