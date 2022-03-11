/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_a_token_type.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:23:48 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/11 15:10:51 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_builtin(char *str)
{
	if ((ft_strcmp("cd", str) == 0)
		|| (ft_strcmp("exit", str) == 0)
		|| (ft_strcmp("echo", str) == 0)
		|| (ft_strcmp("env", str) == 0)
		|| (ft_strcmp("pwd", str) == 0)
		|| (ft_strcmp("export", str) == 0)
		|| ft_strcmp("unset", str) == 0)
		return (1);
	return (0);
}

static void	if_the_length_is_one(char *content, int *type)
{
	if (!(ft_strcmp(content, "<")))
		*type = FILE_IN;
	else if (!(ft_strcmp(content, ">")))
		*type = FILE_OUT;
	else if (!(ft_strcmp(content, "|")))
		*type = PIPE;
	else
		*type = ARG;
}

static void	if_the_length_is_two(char *content, int *type)
{
	if (!(ft_strcmp(content, "<<")))
		*type = HERE_DOC;
	else if (!(ft_strcmp(content, ">>")))
		*type = FILE_OUT_SUR;
	else
		*type = ARG;
}

void	creating_a_token_type(t_list **tokens)
{
	t_list	*step;

	step = *tokens;
	while (step)
	{
		if (ft_strlen(step->content) == 1)
			if_the_length_is_one(step->content, &step->type);
		else if (ft_strlen(step->content) == 2)
			if_the_length_is_two(step->content, &step->type);
		else if (is_builtin(step->content) == 1)
			step->type = BUILTIN;
		else if (ft_strlen(step->content) != 0 && step->type == NONE)
			step->type = ARG;
		step = step->next;
	}
}
