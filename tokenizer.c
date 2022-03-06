/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:55:26 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/06 20:19:56 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
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

int	new_lst_back(char *cmd, t_list **cmd_list)
{
	t_list	*new;

	new = ft_lstnew(cmd);
	if (new == NULL || new->content == NULL)
		return (-1);
	ft_lstadd_back(cmd_list, new);
	return (0);
}

int	ret_file_without_obj(int type)
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

void	if_the_flag_is_zero(int type, int *flag)
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

void	if_the_flag_is_not_zero(int *type, int *flag)
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

void	create_file_type(t_list **tokens)
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

int	tokens_type_error(t_list **tokens)
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
				return (ret_file_without_obj(step->type));
			flag = 0;
		}
		step = step->next;
	}
	if (flag == 1)
		return (ret_file_without_obj(NONE));
	return (0);
}
