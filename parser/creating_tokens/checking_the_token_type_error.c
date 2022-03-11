/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_the_token_type_error.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:15:26 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/10 20:40:29 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	return_error(int type)
{
	write(2, "minishell: syntax error near unexpected token", 46);
	if (type == NONE)
		write(2, " `newline\'\n", 12);
	else if (type == FILE_OUT)
		write(2, " `>\'\n", 6);
	else if (type == FILE_OUT_SUR)
		write(2, " `>>\'\n", 7);
	else if (type == FILE_IN)
		write(2, " `<\'\n", 6);
	else if (type == HERE_DOC)
		write(2, " `<<\'\n", 7);
	else if (type == PIPE)
		write(2, " `|\'\n", 6);
	return (1);
}

int	checking_the_token_type_error(t_list **tokens)
{
	t_list	*step;
	int		flag;

	step = *tokens;
	flag = 0;
	while (step)
	{
		if ((step->type == FILE_IN || step->type == HERE_DOC
				|| step->type == FILE_OUT || step->type == FILE_OUT_SUR
				|| step->type == NONE) && flag == 0)
			flag = 1;
		else if (flag == 1 && step->content)
		{
			if (step->type == FILE_IN || step->type == HERE_DOC
				|| step->type == FILE_OUT || step->type == FILE_OUT_SUR
				|| step->type == PIPE || step->type == NONE)
				return (return_error(step->type));
			flag = 0;
		}
		step = step->next;
	}
	if (flag == 1)
		return (return_error(NONE));
	return (0);
}
