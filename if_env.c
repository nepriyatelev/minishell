/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 22:01:27 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/03 17:09:43 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char *get_env(char *str, t_list **list_env)
{
	t_list *tmp;
	int		i = 0;
	int		j = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = *list_env;
	while (tmp)
	{
		while (tmp->content[j] && tmp->content[j] != '=')
			j++;
		if (i == j && ft_strncmp(tmp->content, str, i) == 0)
			return (ft_strdup(tmp->content + (j + 1)));
		j = 0;
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

void get_len_var_env(char *str, int *dollar, int *question_mark, int *len_var)
{
	int	i;

	i = 0;
	if (str[*dollar] == '$')
	{
		while (str[*dollar] && str[*dollar] == '$')
			(*dollar)++;
		if (str[*dollar] == '?')
		{
			(*question_mark)++;
			return ;
		}
	}
	str += (*dollar);
	while (str[*len_var] && ((ft_isalnum(str[*len_var]) == 1) || str[*len_var] == '_'))
		(*len_var)++;
}

char *if_env(char *str, int *j, t_list **list_env)
{
	char *env;
	int	len_var;
	int	dollar;
	int	question_mark;
	char *new_str;
	new_str = ft_strdup(""); //проверка 0
	
	len_var = 0;
	dollar = 0;
	question_mark = 0;
	get_len_var_env(str, &dollar, &question_mark, &len_var);
	if (dollar != 0 && question_mark == 0 && len_var == 0)
	{
		(*j) += dollar;
		while (dollar)
		{
			new_str = ft_strjoin(new_str, "$");
			dollar--;
		}
	}
	else if (dollar != 0 && question_mark == 1 && len_var == 0)
	{
		(*j) += dollar + question_mark;
		if (dollar % 2 == 0)
		{
			while (dollar)
			{
				new_str = ft_strjoin(new_str, "$");
				dollar--;
			}
			new_str = ft_strjoin(new_str, "?");
		}
		else
		{
			while (dollar - 1)
			{
				new_str = ft_strjoin(new_str, "$");
				dollar--;
			}
			new_str = ft_strjoin(new_str, ft_itoa(g_exit_status));
		}
	}
	else if (dollar != 0 && question_mark == 0 && len_var != 0)
	{
		*j += len_var + dollar;
		if (dollar % 2 == 0)
		{
			while (dollar)
			{
				new_str = ft_strjoin(new_str, "$");
				dollar--;
			}
			new_str = ft_strjoin(new_str, ft_substr(str, (int)ft_strlen(new_str), len_var));
		}
		else
		{
			while (dollar - 1)
			{
				new_str = ft_strjoin(new_str, "$");
				dollar--;
			}
			// printf("ft_strlen(new_str) - dollar = %d\n", (int)ft_strlen(new_str) + dollar);
			new_str = ft_strjoin(new_str, get_env(ft_substr(str, (int)ft_strlen(new_str) + dollar, len_var), list_env));
		}
	}
	return (new_str);
}