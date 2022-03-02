/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:55:26 by modysseu          #+#    #+#             */
/*   Updated: 2022/02/25 17:15:56 by modysseu         ###   ########.fr       */
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

void	create_type(t_list **tokens)
{
	t_list	*step;

	step = *tokens;
	while (step)
	{
		if (ft_strlen(step->content) == 1
			&& (ft_strcmp(step->content, "<") == 0))
				step->type = FILE_IN;
		else if (ft_strlen(step->content) == 1
			&& (ft_strcmp(step->content, ">") == 0))
			step->type = FILE_OUT;
		else if (ft_strlen(step->content) == 1
			&& (ft_strcmp("|", step->content) == 0))
			step->type = PIPE;
		else if (ft_strlen(step->content) == 2
			&& (ft_strcmp(step->content, "<<") == 0))
			step->type = HERE_DOC;
		else if (ft_strlen(step->content) == 2
			&& (ft_strcmp(step->content, ">>") == 0))
			step->type = FILE_OUT_SUR;
		else if (is_builtin(step->content) == 1)
			step->type = BUILTIN;
		else if (ft_strlen(step->content) != 0 && step->type == NONE)
			step->type = ARG;
		step = step->next;
	}
}

int create_tokens(char *str, t_list **tokens)
{
	int	i;
	int	j;
	char sep;
	int quote;
	int	br;
	
	j = 0;
	quote = 0;
	br = 0;
	if (!str)
		return (1);
	while (str[j])
	{
		while (ft_isspace(str[j]) && str[j])
			j++;
		i = j;
		if (str[j] && (str[j] == '>' || str[j] == '<'))
		{
			sep = str[j];
			while (str[j] && str[j] == sep)
			{
				j++;
				br++;
				if (str[j] == ' ')
					br = 0;
				if (br == 2)
				{
					br = 0;
					break ;
				}
			}
		}
		else
		{
			while (str[j])
			{
				quote_status(str[j], &quote);
				if ((ft_isspace(str[j]) || str[j] == '>' || str[j] == '<') && !quote)
					break ;
				j++;
			}
		}
		if (i != j)
				ft_lstadd_back(tokens, ft_lstnew(ft_substr(str, i, j - i))); // проверить на NULL
	}
		create_type(tokens);
	return (0);
}

int	ret_file_without_obj(int type) //вывел ошибку
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

void create_file_type(t_list **tokens) //расставил типы после << < >> >
{
	int		flag;
	t_list	*step;

	flag = 0;
	step = *tokens;
	while (step)
	{
		if (flag == 0)
		{
			if (step->type == FILE_IN)
				flag = OPEN_FILE;
			else if (step->type == HERE_DOC)
				flag = LIMITOR;
			else if (step->type == FILE_OUT)
				flag = EXIT_FILE;
			else if (step->type == FILE_OUT_SUR)
				flag = EXIT_FILE_RET;
		}
		else if (flag != 0 && step->content)
		{
			if (flag == OPEN_FILE)
				step->type = OPEN_FILE;
			else if (flag == LIMITOR)
				step->type = LIMITOR;
			else if (flag == EXIT_FILE)
				step->type = EXIT_FILE;
			else if (flag == EXIT_FILE_RET)
				step->type = EXIT_FILE_RET;
			flag = 0;
		}
		step = step->next;
	}
}

int tokens_type_error(t_list **tokens) // проверка что после < << > >> | идет аргумент
{
	t_list *tmp;
	int		flag;
	tmp = *tokens;
	flag = 0;
	while (tmp)
	{
		if ((tmp->type == FILE_IN || tmp->type == HERE_DOC			\
			|| tmp->type == FILE_OUT || tmp->type == FILE_OUT_SUR	\
			|| tmp->type == PIPE || tmp->type == NONE) && flag == 0)
			flag = 1;
		else if (flag == 1 && tmp->content)
		{
			if (tmp->type == FILE_IN || tmp->type == HERE_DOC			\
				|| tmp->type == FILE_OUT || tmp->type == FILE_OUT_SUR	\
				|| tmp->type == PIPE || tmp->type == NONE)
				return (ret_file_without_obj(tmp->type));
			flag = 0;
		}
		tmp = tmp->next;
	}
		if (flag == 1)
			return (ret_file_without_obj(NONE));
	return (0);
}

int tokenizer(t_list **cmd_list, t_list **tokens)
{
	t_list	*step;

	step = *cmd_list;
	while (step)
	{
		if (create_tokens(step->content, tokens))
			return (1);
		step = step->next;
	}
	if (tokens_type_error(tokens))
		return 1;
	create_file_type(tokens);
	return (0);
}