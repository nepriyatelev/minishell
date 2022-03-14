/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:53:42 by medeana           #+#    #+#             */
/*   Updated: 2022/03/14 21:18:19 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pipe(t_cmd *cmd)
{
	while (cmd)
	{
		pipe(cmd->fd);
		cmd = cmd->next;
	}
}

int	make_heredocs(t_cmd *cmd, t_shell *shell)
{
	while (cmd != NULL)
	{
		if (check_heredoc(cmd->file, cmd->fd[0], cmd, shell) == 1)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	check_heredoc(char **redir, int stdin_fd, t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (redir && redir[i])
	{
		if (ft_strcmp(redir[i], "<<") == 0)
		{
			if (redir_heredoc(redir[i + 1], stdin_fd, cmd, shell) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	redir_heredoc(char *limiter, int fd, t_cmd *cmd, t_shell *shell)
{
	int		new_fd[2];
	pid_t	pid;
	int		wstatus;

	signal(SIGINT, nothing);
	pipe(new_fd);
	pid = fork();
	if (pid == 0)
		heredoc(limiter, new_fd, cmd, shell);
	wait(&wstatus);
	signal(SIGINT, ft_newline);
	if (WIFEXITED(wstatus))
		g_exit_status = WEXITSTATUS(wstatus);
	dup2(new_fd[0], fd);
	close(new_fd[1]);
	close(new_fd[0]);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 130)
		return (1);
	return (0);
}

void	heredoc(char *limiter, int *fd, t_cmd *cmd, t_shell *shell)
{
	char	*line;

	signal(SIGINT, stop_heredoc);
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, limiter) == 0)
		{
			close(fd[0]);
			close(fd[1]);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	free_exit(cmd, shell);
	exit(EXIT_SUCCESS);
}
