/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_env_utilities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:47:07 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/12 20:47:48 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env(char *str, t_list **list_env)
{
	t_list	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
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

void	get_len_var_env(char *str, int *dollar,
				int *question_mark, int *len_var)
{
	int	i;

	*len_var = 0;
	*question_mark = 0;
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
	while (str[*len_var]
		&& ((ft_isalnum(str[*len_var]) == 1) || str[*len_var] == '_'))
		(*len_var)++;
}
