/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:08:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/06 20:01:29 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_only_pipe(char *cmd)
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

int	unclose_quote(char	*cmd)
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

void	quote_status(char ch, int *quote)
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

int	parsing(char *cmd, t_list **list_env, t_cmd **ex_cmd)
{
	t_list	*cmd_separated_by_pipes;
	t_list	*tokens;

	cmd_separated_by_pipes = NULL;
	tokens = NULL;
	if (unclose_quote(cmd))
	{
		write(2, "minishell: miss quote\n", 23);
		free(cmd);
		return (0);
	}
	if (check_only_pipe(cmd))
	{
		free(cmd);
		return (0);
	}
	if (separation_by_pipes(cmd, &cmd_separated_by_pipes))
	{
		ft_lstclear(&cmd_separated_by_pipes, free);
		free(cmd);
		return (-1);
	}
	if (tokenizer(&cmd_separated_by_pipes, &tokens))
	{
		ft_lstclear(&cmd_separated_by_pipes, free);
		ft_lstclear(&tokens, free);
		free(cmd);
		return (1);
	}
	// if (word_modif(&tokens, list_env))
	// {
	// 	ft_lstclear(&tokens, free);
	// 	return (1);
	// }
	// connection_of_parts(ex_cmd, tokens, *list_env);
	// ft_lstclear(&cmd_separated_by_pipes, free);
	// ft_lstclear(&tokens, free);
	// ft_lstclear(list_env, free);
	// ft_lstclear(&cmd_separated_by_pipes, free);
	// 	while (cmd_separated_by_pipes)/*удалить*/
	// {
	// 	printf("TOKEN = %s\n", cmd_separated_by_pipes->content);
	// 	cmd_separated_by_pipes = cmd_separated_by_pipes->next;
	// }
	// while (tokens)/*удалить*/
	// {
	// 	printf("TOKEN = %s\t TYPE = %d\n", tokens->content, tokens->type);
	// 	tokens = tokens->next;
	// }
	return (0);
}
