/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 22:01:27 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/13 18:13:37 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	else_a_dollar_and_without_a_question_mark(int *dollar,
		char **new_str)
{
	while (*dollar - 1)
	{
		*new_str = ft_strjoin(*new_str, "$");
		(*dollar)--;
	}
}

static void	if_a_dollar_and_without_a_question_mark(int dollar,
		char **new_str, char **str, int len_var)
{
	if (dollar % 2 == 0)
	{
		while (dollar)
		{
			*new_str = ft_strjoin(*new_str, "$");
			dollar--;
		}
		*new_str = ft_strjoin(*new_str, ft_substr(*str,
					ft_strlen(*new_str), len_var));
	}
}

static void	if_a_dollar_and_a_question_mark(int *j,
		int question_mark, int dollar, char **new_str)
{
	(*j) += dollar + question_mark;
	if (dollar % 2 == 0)
	{
		while (dollar)
		{
			*new_str = ft_strjoin(*new_str, "$");
			dollar--;
		}
		*new_str = ft_strjoin(*new_str, "?");
	}
	else
	{
		while (dollar - 1)
		{
			*new_str = ft_strjoin(*new_str, "$");
			dollar--;
		}
		*new_str = ft_strjoin(*new_str, ft_itoa(g_exit_status));
	}
}

static void	if_only_a_dollar(int *j, int dollar, char **new_str)
{
	(*j) += dollar;
	while (dollar)
	{
		*new_str = ft_strjoin(*new_str, "$");
		dollar--;
	}
}

char	*if_env(char *str, int *j, t_list **list_env, int dollar)
{
	int		len_var;
	int		question_mark;
	char	*new_str;

	new_str = ft_strdup("");
	get_len_var_env(str, &dollar, &question_mark, &len_var);
	if (dollar != 0 && question_mark == 0 && len_var == 0)
		if_only_a_dollar(j, dollar, &new_str);
	else if (dollar != 0 && question_mark == 1 && len_var == 0)
		if_a_dollar_and_a_question_mark(j, question_mark, dollar, &new_str);
	else if (dollar != 0 && question_mark == 0 && len_var != 0)
	{
		*j += len_var + dollar;
		if_a_dollar_and_without_a_question_mark(dollar,
			&new_str, &str, len_var);
		if (dollar % 2 != 0)
		{
			else_a_dollar_and_without_a_question_mark(&dollar, &new_str);
			new_str = ft_strjoin(new_str, get_env(ft_substr(str, \
				(int)ft_strlen(new_str) + dollar, len_var), list_env));
		}
	}
	return (new_str);
}
