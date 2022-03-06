/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separation_by_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:51:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/06 20:16:22 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	separation_by_pipes(char *cmd, t_list **cmd_list)
{
	int		i;
	int		j;
	int		quote;
	int		return_value;

	i = 0;
	j = 0;
	quote = 0;
	return_value = 0;
	while (cmd[j])
	{
		quote_status(cmd[j], &quote);
		if ((cmd[j] == '|' && !quote))
		{
			if (i != j)
				return_value = new_lst_back(ft_substr(cmd, i, j - i), cmd_list);
			return_value = new_lst_back(ft_strdup("|"), cmd_list);
			i = j + 1;
		}
		if (cmd[j + 1] == '\0' && cmd[j] != '|')
			return_value = new_lst_back(ft_substr(cmd, i, j + 1 - i), cmd_list);
		j++;
	}
	return (return_value);
}
