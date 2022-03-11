/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:24:45 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/09 14:27:19 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *destination, const char *source, size_t n)
{
	size_t	lsrc;
	size_t	i;

	i = 0;
	lsrc = ft_strlen(source);
	while (i < n)
	{
		if (i < lsrc)
		{
			destination[i] = source[i];
			i++;
		}
		else
		{
			destination[i] = '\0';
			i++;
		}
	}
	return (destination);
}
