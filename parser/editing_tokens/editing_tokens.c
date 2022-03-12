/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editing_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:50:37 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/12 17:07:09 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	editing_tokens(t_list **tokens, t_list **list_env)
{
	t_list	*step;

	step = *tokens;
	while (step)
	{
		if (step->content != NULL)
		{
			if (modification_of_tokens(step, list_env))
				return (-1);
		}
		step = step->next;
	}
	return (0);
}
