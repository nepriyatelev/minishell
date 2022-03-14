/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 19:02:34 by medeana           #+#    #+#             */
/*   Updated: 2022/03/14 21:19:45 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(char *argv, int i, int quit)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
	{
		if (access(argv, F_OK) == 0)
			printf("minishell: %s Is a directory\n", argv);
		else
			printf("minishell: no such file or directory: %s\n", argv);
		if (quit == 0)
			exit(1);
	}
	return (file);
}

void	free_fd(t_cmd *first)
{
	while (first)
	{
		close(first->fd[0]);
		close(first->fd[1]);
		first = first->next;
	}
}

void	free_job_lst(t_cmd *job)
{
	t_cmd	*temp;

	temp = NULL;
	while (job)
	{
		temp = job->next;
		if (job->argv)
			ft_free_tab(job->argv);
		if (job->file)
			ft_free_tab(job->file);
		free(job);
		job = temp;
	}
	job = NULL;
}

void	error(char *arg, int i, t_cmd *cmd, t_shell *shell)
{
	if (i == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (i == 1)
		printf("minishell: %s: No such file or directory\n", arg);
	else if (i == 2)
	{
		printf("minishell: %s: is a directory\n", arg);
		free_exit(cmd, shell);
		exit(126);
	}
	free_exit(cmd, shell);
	exit (127);
}
