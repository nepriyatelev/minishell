/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:45:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/11 15:58:01 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char **env)
{
	t_list	*list_env;
	t_cmd	*ex_cmd;
	char	*cmd;

	if (argc != 1)
		return (1);
	list_env = NULL;
	ex_cmd = NULL;
	(void)argv;
	g_exit_status = 0;
	if (init_env(&list_env, env))
	{
		ft_lstclear(&list_env, free);
		return (1);
	}
	while (1)
	{
		cmd = readline("minishell-1.0$ ");
		if (!cmd)
			return (0);
		if (parsing_main(cmd, &list_env, &ex_cmd))
		{
			puts("проблема в парсере");
			return (1);
		}
		add_history(cmd);
		free(cmd);
		// ms_init_env(env, ex_cmd);
		// ft_lstclear(&minishell.tokens, free);
		// ft_lstclear(&minishell.list_env, free);
		// ft_lstclear(&minishell.cmd_separated_by_pipes, free);
		// ex_cmd = init_list(ex_cmd, env, cmd);
		// ft_exec(ex_cmd);
		// while (minishell.list_env)/*удалить*/
		// {
		// 	printf("TOKEN = %s\n", minishell.list_env->content);
		// 	minishell.list_env = minishell.list_env->next;
		// }
		// if (cmd)
		// 	free(cmd);
		// while (minishell.tokens)/*удалить*/
		// {
		// 	printf("TOKEN = %s\t TYPE = %d\n", minishell.tokens->content, minishell.tokens->type);
		// 	minishell.tokens = minishell.tokens->next;
		// }
		// printf("TOKEN = %s\t TYPE = %d\n", minishell.tokens->content, minishell.tokens->type);
		// while (cmd_separated_by_pipes)/*удалить*/
		// {
		// 	printf("TOKEN = %s\n", cmd_separated_by_pipes->content);
		// 	cmd_separated_by_pipes = cmd_separated_by_pipes->next;
		// }
		// int k = 1;
		// while (ex_cmd)/*удалить*/
		// {
		// 	printf("LIST = %d\n", k);
		// 	for(int i = 0; ex_cmd->argv[i]; i++)
		// 		printf("argv = %s\n", ex_cmd->argv[i]);
		// 	for(int i = 0; ex_cmd->file[i]; i++)
		// 		printf("file = %s\n", ex_cmd->file[i]);
		// 	// for(int i = 0; ex_cmd->env[i]; i++)
		// 	// 	printf("%s\n", ex_cmd->env[i]);
		// 	ex_cmd = ex_cmd->next;
		// 	k++;
		// 	puts("\n");
		// }
	}
	return (0);
}
