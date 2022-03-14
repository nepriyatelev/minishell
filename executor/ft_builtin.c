/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:56:29 by medeana           #+#    #+#             */
/*   Updated: 2022/03/14 21:17:58 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(0);
	saved_stdout = dup(1);
	if (cmd && cmd->next == NULL && cmd->argv[0] != NULL)
	{
		if (cmd->argv && check_builtins(cmd->argv) == 1)
			return (0);
		if (check_redirection(cmd, 1) == 1)
			return (1);
		if (ms_builtins(cmd->argv, 0, cmd, shell) == 0)
		{
			restore_fd(saved_stdin, saved_stdout);
			return (1);
		}
	}
	return (0);
}

int	check_builtins(char **arg)
{
	if (ft_strcmp(arg[0], "echo") == 0
		||ft_strcmp(arg[0], "cd") == 0
		||ft_strcmp(arg[0], "pwd") == 0
		||ft_strcmp(arg[0], "export") == 0
		||ft_strcmp(arg[0], "unset") == 0
		||ft_strcmp(arg[0], "env") == 0
		||ft_strcmp(arg[0], "exit") == 0)
		return (0);
	else
		return (1);
}

int	check_redirection(t_cmd *job, int quit)
{
	int	fd[2];
	int	i;

	i = 0;
	fd[0] = 0;
	fd[1] = 0;
	while (job->file && job->file[i])
	{
		if (ft_strcmp(job->file[i], "<") == 0)
			fd[0] = open_file(job->file[++i], 2, quit);
		else if (ft_strcmp(job->file[i], ">") == 0)
			fd[1] = open_file(job->file[++i], 1, quit);
		else if (ft_strcmp(job->file[i], ">>") == 0)
			fd[1] = open_file(job->file[++i], 0, quit);
		else if (ft_strcmp(job->file[i], "<<") == 0)
			dup2(job->fd[0], STDIN_FILENO);
		i++;
	}
	if (fd[0] == -1 || fd[1] == -1)
		return (1);
	if (fd[0])
		dup2(fd[0], STDIN_FILENO);
	if (fd[1])
		dup2(fd[1], STDOUT_FILENO);
	return (0);
}

int	ms_builtins(char **arg, int i, t_cmd *first, t_shell *shell)
{
	if (arg)
	{
		if (ft_strcmp(arg[0], "echo") == 0)
			g_exit_status = ms_echo(arg + 1);
		else if (ft_strcmp(arg[0], "cd") == 0)
			g_exit_status = ms_cd(arg[1], shell);
		else if (ft_strcmp(arg[0], "pwd") == 0)
			g_exit_status = ms_pwd();
		else if (ft_strcmp(arg[0], "export") == 0)
			g_exit_status = ms_export(arg + 1, shell);
		else if (ft_strcmp(arg[0], "unset") == 0)
			g_exit_status = ms_unset(arg + 1, shell);
		else if (ft_strcmp(arg[0], "env") == 0)
			g_exit_status = ms_env(shell);
		else if (ft_strcmp(arg[0], "exit") == 0)
			ms_exit(arg + 1, first, shell);
		else
			return (1);
	}
	if (i == 0)
		return (0);
	free_exit(first, shell);
	exit(0);
}

void	restore_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, 0);
	close(saved_stdin);
	dup2(saved_stdout, 1);
	close(saved_stdout);
}
