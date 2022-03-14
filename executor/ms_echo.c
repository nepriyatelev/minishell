/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 15:51:52 by medeana           #+#    #+#             */
/*   Updated: 2022/03/14 21:18:46 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ms_newline(char *arg)
{
	int	i;

	i = 0;
	if (arg && arg[i++] == '-')
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				break ;
			if (arg[i + 1] == '\0')
				return (true);
			i++;
		}
	}	
	return (false);
}

int	ms_echo(char **arg)
{
	int	n;
	int	i;

	n = false;
	i = -1;
	while (ms_newline(arg[++i]))
		n = true;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n == false)
		printf("\n");
	return (0);
}
