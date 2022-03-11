/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:47:16 by modysseu          #+#    #+#             */
/*   Updated: 2021/10/08 15:59:39 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*buf;

	buf = 0;
	while (*s)
	{
		if (*s == (char)c)
			buf = (char *)s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (buf);
}
