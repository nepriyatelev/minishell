/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:45:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/02/27 18:23:30 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char **env)
{
	t_shell	minishell;
	t_cmd	*ex_cmd;
	char	*cmd;

	(void)argv;
	g_exit_status = 0;
	if (argc != 1)
		return (1);
	if (init_env(&minishell.list_env, env))
	{
		ft_lstclear(&minishell.list_env, free);
		return (1);
	}
	while (1)
	{
		cmd = readline("minishell-1.0$ ");
		if (!cmd)
			return (0);
		if (parsing(cmd, &minishell.cmd_separated_by_pipes,
				&minishell.tokens, &minishell.list_env))
		{
			puts("хуйня в парсере");
			return (1);
		}
		connection_of_parts(&ex_cmd, minishell.tokens, minishell.list_env);
		add_history(cmd);
		if (cmd)
			free(cmd);
		// ft_lstclear(&minishell.cmd_separated_by_pipes, free);
		// ft_lstclear(&minishell.tokens, free);
		// ft_lstclear(&minishell.list_env, free);
		// while (minishell.list_env)/*удалить*/
		// {
		// 	printf("TOKEN = %s\n", minishell.list_env->content);
		// 	minishell.list_env = minishell.list_env->next;
		// }
		// while (minishell.tokens)/*удалить*/
		// {
		// 	printf("TOKEN = %s\t TYPE = %d\n", minishell.tokens->content, minishell.tokens->type);
		// 	minishell.tokens = minishell.tokens->next;
		// }
		// printf("TOKEN = %s\t TYPE = %d\n", minishell.tokens->content, minishell.tokens->type);
		// while (minishell.cmd_separated_by_pipes)/*удалить*/
		// {
		// 	printf("TOKEN = %s\n", minishell.cmd_separated_by_pipes->content);
		// 	minishell.cmd_separated_by_pipes = minishell.cmd_separated_by_pipes->next;
		// }
		int k = 1;
		while (ex_cmd)/*удалить*/
		{
			printf("LIST = %d\n", k);
			// for(int i = 0; ex_cmd->argv[i]; i++)
			// 	printf("argv = %s\n", ex_cmd->argv[i]);
			// for(int i = 0; ex_cmd->file[i]; i++)
			// 	printf("file = %s\n", ex_cmd->file[i]);
			for(int i = 0; ex_cmd->env[i]; i++)
				printf("%s\n", ex_cmd->env[i]);
			ex_cmd = ex_cmd->next;
			k++;
			puts("\n");
		}
	}
	return (0);
}
