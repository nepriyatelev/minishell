/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:57:53 by modysseu          #+#    #+#             */
/*   Updated: 2022/02/27 19:22:40 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// int	ft_strncmp(char *str, char *to, int n)
// {
// 	int	i;

// 	i = 0;
// 	if (str == NULL || to == NULL)
// 		return (-1);
// 	if ((int)ft_strlen(str) < n || (int)ft_strlen(to) < n)
// 		return (-1);
// 	while (i < n)
// 	{
// 		if (!str[i] || !to[i] || str[i] != to[i])
// 			return (str[i] - to[i]);
// 		i++;
// 	}
// 	return (0);
// }
