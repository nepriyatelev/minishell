/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:15:21 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/06 20:16:27 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

int	new_lst_back(char *cmd, t_list **cmd_list)
{
	t_list	*new;

	new = ft_lstnew(cmd);
	if (new == NULL || new->content == NULL)
		return (-1);
	ft_lstadd_back(cmd_list, new);
	return (0);
}
