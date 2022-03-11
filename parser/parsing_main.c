/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:08:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/11 19:00:23 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	separation_by_pipes(char *cmd, t_list **cmd_list)
{
	int		i;
	int		j;
	int		quote;
	int		return_value;

	i = 0;
	j = 0;
	quote = 0;
	return_value = 0;
	while (cmd[j])
	{
		quote_status(cmd[j], &quote);
		if ((cmd[j] == '|' && !quote))
		{
			if (i != j)
				return_value = new_lst_back(ft_substr(cmd, i, j - i), cmd_list);
			return_value = new_lst_back(ft_strdup("|"), cmd_list);
			i = j + 1;
		}
		if (cmd[j + 1] == '\0' && cmd[j] != '|')
			return_value = new_lst_back(ft_substr(cmd, i, j + 1 - i), cmd_list);
		j++;
	}
	return (return_value);
}

int	parsing_main(char *cmd, t_list **list_env, t_cmd **ex_cmd)
{
	t_list	*cmd_separated_by_pipes;
	t_list	*tokens;

	cmd_separated_by_pipes = NULL;
	tokens = NULL;
	(void)ex_cmd;
	if ((unclose_quote(cmd, 0, 0)) || (error_pipe(cmd)))
		return (0);
	if (separation_by_pipes(cmd, &cmd_separated_by_pipes))
	{
		ft_lstclear(&cmd_separated_by_pipes, free);
		return (-1);
	}
	if (creating_tokens(&cmd_separated_by_pipes, &tokens))
	{
		ft_lstclear(&cmd_separated_by_pipes, free);
		ft_lstclear(&tokens, free);
		return (1);
	}
	if (editing_tokens(&tokens, list_env))
	{
		ft_lstclear(&tokens, free);
		return (1);
	}
	// connection_of_parts(ex_cmd, tokens, *list_env);
	// ft_lstclear(&tokens, free);
	// ft_lstclear(list_env, free);
	// ft_lstclear(&cmd_separated_by_pipes, free);
	// while (cmd_separated_by_pipes)
	// {
	// 	printf("TOKEN = %s\n", cmd_separated_by_pipes->content);
	// 	cmd_separated_by_pipes = cmd_separated_by_pipes->next;
	// }
	while (tokens)/*удалить*/
	{
		printf("TOKEN = %s\t TYPE = %d\n", tokens->content, tokens->type);
		tokens = tokens->next;
	}
	ft_lstclear(&cmd_separated_by_pipes, free);
	ft_lstclear(&tokens, free);
	// ft_lstclear(list_env, free);
	return (0);
}
