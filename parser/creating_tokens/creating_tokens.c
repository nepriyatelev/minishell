/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:56:51 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/11 15:21:34 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	if_the_arrow(char *str, int *j)
{
	char	sep;
	int		br;

	br = 0;
	sep = str[*j];
	while (str[*j] && str[*j] == sep)
	{
		(*j)++;
		br++;
		if (br == 2)
			break ;
	}
}

static void	if_not_the_arrow(char *str, int *j, int *quote)
{
	while (str[*j])
	{
		quote_status(str[*j], quote);
		if ((ft_isspace(str[*j]) || str[*j] == '>' || str[*j] == '<')
			&& !(*quote))
			break ;
		(*j)++;
	}
}

static int	init_tokens(char *str, t_list **tokens)
{
	int		i;
	int		j;
	int		quote;
	int		return_value;

	j = 0;
	quote = 0;
	return_value = 0;
	while (str[j])
	{
		while (ft_isspace(str[j]) && str[j])
			j++;
		i = j;
		if (str[j] && (str[j] == '>' || str[j] == '<'))
			if_the_arrow(str, &j);
		else
			if_not_the_arrow(str, &j, &quote);
		if (i != j)
			return_value = new_lst_back(ft_substr(str, i, j - i), tokens);
	}
	creating_a_token_type(tokens);
	return (return_value);
}

int	creating_tokens(t_list **cmd_separated_by_pipes, t_list **tokens)
{
	t_list	*step;

	step = *cmd_separated_by_pipes;
	while (step)
	{
		if (init_tokens(step->content, tokens))
			return (-1);
		step = step->next;
	}
	if (checking_the_token_type_error(tokens))
		return (1);
	file_type_assignment(tokens);
	return (0);
}
