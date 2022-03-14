/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:45:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/14 21:20:44 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char **env)
{
	t_shell *shell;
	t_list	*list_env;
	t_cmd	*ex_cmd;
	char	*cmd;

	shell = (t_shell *)malloc(sizeof(t_shell));
	ms_init_env(env, shell);
	ms_init_export(shell);
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
		add_history(cmd);
		if (!cmd)
			ctrl_d(cmd, shell);
		if (parsing_main(cmd, &list_env, &ex_cmd))
			return (-1);
		ft_exec(ex_cmd, shell);
	}
	ft_lstclear(&list_env, free);
	return (0);
}
