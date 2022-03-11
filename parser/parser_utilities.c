/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:48:45 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/10 19:39:45 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_status(char ch, int *quote)
{
	if (ch == '\"')
	{
		if (*quote == 0)
			*quote = 2;
		else if (*quote == 2)
			*quote = 0;
	}
	else if (ch == '\'')
	{
		if (*quote == 0)
			*quote = 1;
		else if (*quote == 1)
			*quote = 0;
	}
}

int	new_lst_back(char *cmd, t_list **cmd_list)
{
	t_list	*new;

	new = ft_lstnew(cmd);
	if (new == NULL || new->content == NULL)
		return (-1);
	ft_lstadd_back(cmd_list, new);
	return (0);
}
