/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:04:48 by medeana           #+#    #+#             */
/*   Updated: 2022/03/14 21:17:14 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process(t_cmd *cmd, t_cmd *first, t_shell *shell)
{
	signal(SIGINT, nothing);
	cmd->pid = fork();
	if (cmd->pid == -1)
		printf("error");
	if (cmd->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (cmd->prev != NULL)
			dup2(cmd->prev->fd[0], STDIN_FILENO);
		if (cmd->next != NULL)
			dup2(cmd->fd[1], STDOUT_FILENO);
		check_redirection(cmd, 0);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		free_fd(first);
		if (cmd->argv && ms_builtins(cmd->argv, 1, first, shell) == 1)
			executor(cmd->argv, first, shell);
	}
	if (cmd->prev != NULL)
		close(cmd->prev->fd[0]);
	close(cmd->fd[1]);
}

void	ft_exec(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*first;
	int		status;

	status = 0;
	first = cmd;
	init_pipe(first);
	if (make_heredocs(cmd, shell) == 1 || ft_builtin(cmd, shell) == 1)
		return ;
	if (cmd && cmd->argv)
	{
		while (cmd)
		{
			process(cmd, first, shell);
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			cmd = cmd->next;
		}
	}
	signal(SIGINT, ctrl_c);
}
