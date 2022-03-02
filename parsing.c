/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:08:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/02/25 17:03:28 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_only_pipe(char *cmd) //чекнул пустоту перед пайпом
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (cmd[i])
	{
		if (cmd[i] != ' ' && cmd[i] != '|')
			flag = 1;
		if (cmd[i] == '|' && flag == 0)
		{
			write(2, "minishell: syntax error near unexpected token `|\'\n", 51);
			return (1);
		}
		i++;
	}
	return (0);
}

int	unclose_quote(char	*cmd) //чекнул незакртые кавычки
{
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
		{
			if (quotes == 0)
				quotes = 2;
			else if (quotes == 2)
				quotes = 0;
		}
		if (cmd[i] == '\'')
		{
			if (quotes == 0)
				quotes = 1;
			else if (quotes == 1)
				quotes = 0;
		}
		i++;
	}
	return (quotes);
}

void	quote_status(char ch, int *quote) //проверка статуса кавычек
{
	if (ch == '\"')
	{
		if (*quote == 0)
			*quote = 2;
		else if (*quote == 2)
			*quote = 0;
	}
	else if (ch == '\'')
	{
		if (*quote == 0)
			*quote = 1;
		else if (*quote == 1)
			*quote = 0;
	}
}

int	separation_by_pipes(char *cmd, t_list **cmd_list) //разделение по пайпам
{
	int		i;
	int		j;
	int		quote;

	i = 0;
	j = 0;
	quote = 0;
	while (cmd[j])
	{
		quote_status(cmd[j], &quote);
		if ((cmd[j] == '|' && quote == 0))
		{
			if (i != j)
				ft_lstadd_back(cmd_list, ft_lstnew(ft_substr(cmd, i, j - i))); // проверить на NULL
			ft_lstadd_back(cmd_list, ft_lstnew(ft_strdup("|"))); // здесь добавляет пайпы, но возможно это не надо и проверить на NULL
			i = j + 1;
		}
		if (cmd[j + 1] == '\0' && cmd[j] != '|')
			ft_lstadd_back(cmd_list, ft_lstnew(ft_substr(cmd, i, (j + 1 - i)))); // проверить на NULL
		j++;
	}
	return (0);
}

int	parsing(char *cmd, t_list **cmd_separated_by_pipes, t_list **tokens, t_list **list_env)
{
	if (unclose_quote(cmd))
	{
		write(2, "minishell: miss quote\n", 23);
		return (1);
	}
	if (check_only_pipe(cmd))
		return (1);
	if (separation_by_pipes(cmd, cmd_separated_by_pipes))
		printf("%s\n", "какая-то проблема с разделением по пайпам");
		/*free()*/
	if (tokenizer(cmd_separated_by_pipes, tokens))
		printf("%s\n", "какая-то проблема с токенайзером");
		/*free()*/
	if (word_modif(tokens, list_env))
		printf("%s\n", "какая-то проблема с редактированием строки");
		/*free()*/
	// if (org_argv(g_minishell.tokens))			// сохраняет немного не туда
	// 	printf("%s\n", "какая-то проблема с arg");
		/*free()*/
	// for(int i = 0; i < 5; i++)
	// 	printf("ARGV = %s\n", g_minishell.argv[i]);
	return (0);
}
