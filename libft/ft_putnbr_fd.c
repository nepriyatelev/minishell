/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:32:46 by modysseu          #+#    #+#             */
/*   Updated: 2021/10/11 12:48:44 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (fd >= 0)
	{
		if (n == -2147483648)
		{
			write(fd, "-2147483648", 11);
		}
		else
		{
			if (n < 0)
			{
				n = -n;
				write(fd, "-", 1);
			}
			if (n > 9)
			{
				ft_putnbr_fd(n / 10, fd);
				ft_putnbr_fd(n % 10, fd);
			}
			else
			{
				n += 48;
				write(fd, &n, 1);
			}
		}
	}
}
