/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:34:01 by modysseu          #+#    #+#             */
/*   Updated: 2021/10/13 12:28:40 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	s_len;
	char	*result_str;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	i = 0;
	result_str = (char *)malloc(sizeof(char) * s_len + 1);
	if (!result_str)
		return (NULL);
	while (s[i] != '\0')
	{
		result_str[i] = (*f)(i, s[i]);
		i++;
	}
	result_str[i] = '\0';
	return (result_str);
}
