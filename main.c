/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:45:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/14 18:36:13 by modysseu         ###   ########.fr       */
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
			return (-1);
		add_history(cmd);
		free(cmd);
	}
	ft_lstclear(&list_env, free);
	return (0);
}
