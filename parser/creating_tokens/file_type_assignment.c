/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_type_assignment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:20:47 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/10 20:43:29 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	if_the_flag_is_zero(int type, int *flag)
{
	if (type == FILE_IN)
		*flag = OPEN_FILE;
	else if (type == HERE_DOC)
		*flag = LIMITOR;
	else if (type == FILE_OUT)
		*flag = EXIT_FILE;
	else if (type == FILE_OUT_SUR)
		*flag = EXIT_FILE_RET;
}

static void	if_the_flag_is_not_zero(int *type, int *flag)
{
	if (*flag == OPEN_FILE)
		*type = OPEN_FILE;
	else if (*flag == LIMITOR)
		*type = LIMITOR;
	else if (*flag == EXIT_FILE)
		*type = EXIT_FILE;
	else if (*flag == EXIT_FILE_RET)
		*type = EXIT_FILE_RET;
	*flag = 0;
}

void	file_type_assignment(t_list **tokens)
{
	int		flag;
	t_list	*step;

	flag = 0;
	step = *tokens;
	while (step)
	{
		if (flag == 0)
			if_the_flag_is_zero(step->type, &flag);
		else if (flag != 0 && step->content)
			if_the_flag_is_not_zero(&step->type, &flag);
		step = step->next;
	}
}
