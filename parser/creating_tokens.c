/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:56:51 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/06 20:33:02 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

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

void	if_the_length_is_one(char *content, int *type)
{
	if (!(ft_strcmp(content, "<")))
		*type = FILE_IN;
	else if (!(ft_strcmp(content, ">")))
		*type = FILE_OUT;
	else if (!(ft_strcmp(content, "|")))
		*type = PIPE;
}

void	if_the_length_is_two(char *content, int *type)
{
	if (!(ft_strcmp(content, "<<")))
		*type = HERE_DOC;
	else if (!(ft_strcmp(content, ">>")))
		*type = FILE_OUT_SUR;
}

void	create_type(t_list **tokens)
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

void	if_the_arrow(char *str, int *j)
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

void	if_not_the_arrow(char *str, int *j, int *quote)
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

int	create_tokens(char *str, t_list **tokens)
{
	int		i;
	int		j;
	int		quote;
	int		return_value;
	t_list	*new;

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
	create_type(tokens);
	return (return_value);
}

int	creating_tokens(t_list **cmd_separated_by_pipes, t_list **tokens)
{
	t_list	*step;

	step = *cmd_separated_by_pipes;
	while (step)
	{
		if (create_tokens(step->content, tokens))
			return (1);
		step = step->next;
	}
	if (tokens_type_error(tokens))
		return (1);
	create_file_type(tokens);
	return (0);
}
