/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:19:59 by modysseu          #+#    #+#             */
/*   Updated: 2021/10/08 13:05:09 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tmp_dst;
	const char	*tmp_src;

	tmp_dst = (char *)dst;
	tmp_src = (const char *)src;
	if (dst == 0 && src == 0)
		return (0);
	if (tmp_dst < tmp_src)
		while (len--)
			*tmp_dst++ = *tmp_src++;
	else
	{
		while (len--)
		{
			tmp_dst[len] = tmp_src[len];
		}
	}
	return (dst);
}
