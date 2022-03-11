/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:33:29 by modysseu          #+#    #+#             */
/*   Updated: 2021/10/09 12:29:22 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*tmp_dst;
	const char	*tmp_src;

	tmp_dst = (char *)dst;
	tmp_src = (const char *)src;
	if (dst == 0 && src == 0)
		return (0);
	while (n--)
		*tmp_dst++ = *tmp_src++;
	return (dst);
}
