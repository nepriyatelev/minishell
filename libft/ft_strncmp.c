/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:57:53 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/08 18:24:15 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	result;

	result = 0;
	while (result == 0 && n-- && (*s1 || *s2))
	{
		result = *((unsigned char *)s1++) - *((unsigned char *)s2++);
	}
	return (result);
}
