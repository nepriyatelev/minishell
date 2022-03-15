/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:45:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/15 18:08:39 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

void	init_env_for_exec(char **env, t_shell **shell)
{
	*shell = (t_shell *)malloc(sizeof(t_shell));
	ms_init_env(env, *shell);
	ms_init_export(*shell);
}

int	loop(t_shell *shell, char *cmd, t_list *list_env, t_cmd *ex_cmd)
{
	while (1)
	{
		cmd = readline("minishell-1.0$ ");
		add_history(cmd);
		if (!cmd)
			ctrl_d(cmd, shell, list_env);
		if (parsing_main(cmd, &list_env, &ex_cmd))
			return (-1);
		ft_exec(ex_cmd, shell);
	}
	free_job_lst(ex_cmd);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	t_list	*list_env;
	t_cmd	*ex_cmd;
	char	*cmd;

	(void)argv;
	if (argc != 1)
		return (1);
	list_env = NULL;
	shell = NULL;
	ex_cmd = NULL;
	g_exit_status = 0;
	cmd = NULL;
	init_env_for_exec(env, &shell);
	if (init_env(&list_env, env))
	{
		ft_lstclear(&list_env, free);
		return (1);
	}
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	if (loop(shell, cmd, list_env, ex_cmd))
		return (-1);
	ft_lstclear(&list_env, free);
	return (0);
}
