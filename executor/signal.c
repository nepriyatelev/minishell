/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:11:07 by medeana           #+#    #+#             */
/*   Updated: 2022/03/15 18:09:48 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	stop_heredoc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(130);
}

void	nothing(int signal)
{
	(void)signal;
}

void	ft_newline(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_status = 130;
}

void	ctrl_c(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_d(char *line, t_shell *shell, t_list *list)
{
	printf("exit\n");
	free(line);
	ft_lstclear(&list, free);
	ft_free_tab(shell->env);
	ft_free_tab(shell->export);
	free(shell);
	exit(0);
}
