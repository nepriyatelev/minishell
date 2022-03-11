/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:50:45 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/07 20:49:59 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static size_t	ft_nblen(int n)
{
	size_t	size_n;
	int		nb;

	nb = n;
	size_n = 0;
	if (nb <= 0)
		size_n++;
	while (nb)
	{
		size_n++;
		nb /= 10;
	}
	return (size_n);
}

char	*ft_itoa(int n)
{
	size_t	size_n;
	char	*result_str;

	size_n = ft_nblen(n);
	result_str = (char *)malloc(sizeof(char) * size_n + 1);
	if (!result_str)
		return (NULL);
	if (n == -2147483648)
		return (ft_strcpy(result_str, "-2147483648"));
	if (n < 0)
	{	
		result_str[0] = '-';
		n = -n;
	}
	if (n == 0)
		result_str[0] = '0';
	result_str[size_n] = '\0';
	while (n)
	{
		result_str[size_n - 1] = n % 10 + '0';
		size_n--;
		n /= 10;
	}
	return (result_str);
}
