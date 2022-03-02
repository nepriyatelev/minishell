/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:04:48 by medeana           #+#    #+#             */
/*   Updated: 2022/03/02 17:28:06 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern	int	g_exit_status;

void	restore_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, 0);
	close(saved_stdin);
	dup2(saved_stdout, 1);
	close(saved_stdout);
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

// int	ms_check_exit_arg(char *arg)
// {
// 	int			i;
// 	long long	exit_code;

// 	i = 0;
// 	while (arg[i] == ' ')
// 		i++;
// 	if (arg[i] && (arg[i] == '+' || arg[i] == '-'))
// 		i++;
// 	if (ft_isdigit(arg[i]) == 0 || ft_isllong(arg) != 0)
// 	{
// 		printf("minishell: exit: %s: numeric argument required\n", arg);
// 		// g_msh.ret_exit = 255;
// 		return (1);
// 	}
// 	exit_code = ft_atoll(arg);
// 	// g_msh.ret_exit = exit_code % 256;
// 	// if (g_msh.ret_exit < 0 || g_msh.ret_exit > 255)
// 	// 	g_msh.ret_exit = 255;
// 	return (0);
// }

// void	ms_exit(char **arg, t_cmd *job)
// {
// 	int	i;

// 	i = 0;
// 	printf("exit\n");
// 	if (arg[0])
// 	{
// 		i = ms_check_exit_arg(arg[0]);
// 		if (arg[1] && i == 0)
// 		{
// 			printf("minishell: exit: too many arguments\n");
// 			// g_msh.ret_exit = 1;
// 			return ;
// 		}
// 	}
// 	exit(g_msh.ret_exit);
// }

int	ms_builtins(char **arg, int i, t_cmd *job)
{
	if (arg)
	{
		if (ft_strcmp(arg[0], "echo") == 0)
			g_exit_status = ms_echo(arg + 1);
		// else if (ft_strcmp(arg[0], "cd") == 0)
		// 	g_exit_status = ms_cd(arg[1], job);
		else if (ft_strcmp(arg[0], "pwd") == 0)
			g_exit_status = ms_pwd();
		// // else if (ft_strcmp(arg[0], "export") == 0)
		// // 	g_minishell.ret_exit = ms_export(arg + 1);
		// // else if (ft_strcmp(arg[0], "unset") == 0)
		// // 	g_exit_status = ms_unset(job, arg + 1);
		// else if (ft_strcmp(arg[0], "env") == 0)
		// 	g_exit_status = ms_env(job);
		// else if (ft_strcmp(arg[0], "exit") == 0)
		// 	ms_exit(arg + 1, job);
		else
			return (1);
	}
	if (i == 0)
		return (0);
	exit(0);
}

int	check_builtins(char **arg)
{
	if (ft_strcmp(arg[0], "echo") == 0 
		|| ft_strcmp(arg[0], "pwd") == 0
		|| ft_strcmp(arg[0], "cd") == 0
		||ft_strcmp(arg[0], "unset") == 0
		||ft_strcmp(arg[0], "env") == 0)
		return (0);
		// ||ft_strcmp(arg[0], "export") == 0
		// ||ft_strcmp(arg[0], "exit") == 0
		// ||ft_strcmp(arg[0], "mafortin") == 0)
	else
		return (1);
}

void	init_pipe(t_cmd *cmd)
{
	while (cmd)
	{
		pipe(cmd->fd);
		cmd = cmd->next;
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
}

void	heredoc(char *limiter, int *fd, t_cmd *cmd)
{
	char	*line;

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
	ft_free_tab(cmd->env);
	exit(EXIT_SUCCESS);
}

int	redir_heredoc(char *limiter, int fd, t_cmd *cmd)
{
	int		new_fd[2];
	pid_t	pid;
	int		wstatus;
	
	pipe(new_fd);
	pid = fork();
	if (pid == 0)
		heredoc(limiter, new_fd, cmd);
	waitpid(pid, &wstatus, 0); 
	dup2(new_fd[0], fd);
	close(new_fd[1]);
	close(new_fd[0]);
	return (0);
}

int	check_heredoc(char **redir, int stdin_fd, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (redir && redir[i])
	{
		if (ft_strcmp(redir[i], "<<") == 0)
		{
			if (redir_heredoc(redir[i + 1], stdin_fd, cmd) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int make_heredocs(t_cmd *cmd)
{
	while (cmd)
	{
		if (check_heredoc(cmd->file, cmd->fd[0], cmd) == 1)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	open_file(char *argv, int i, int quit)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

int ft_builtin(t_cmd *cmd)
{
	int stdin;
	int	stdout;

	stdin = dup(0);
	stdout = dup(1);
	if (cmd && cmd->next == NULL)
	{
		if (cmd->argv && check_builtins(cmd->argv) == 1)
			return (0);
		if (check_redirection(cmd, 1) == 1)
			return (1);
		if (ms_builtins(cmd->argv, 0, cmd) == 0)
		{
			restore_fd(stdin, stdout);
			return (1);
		}
	}
	return (0);
}

void	error(char *arg, int i)
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
		exit(126);
	}
	exit (127);
}

void	ft_free_tab(char **tabs)
{
	int	i;

	i = 0;
	while (tabs[i])
	{
		free(tabs[i]);
		i++;
	}
	free(tabs);
}

char	*ft_strjoin_free_s1(char *s1, char const *s2)
{
	char	*tabs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	tabs = (char *)malloc(sizeof(*tabs) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (tabs == 0)
		return (NULL);
	while (s1[i])
	{
		tabs[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tabs[i] = s2[j];
		j++;
		i++;
	}
	tabs[i] = '\0';
	free(s1);
	return (tabs);
}

int	find_path_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i] && ft_strnstr(cmd->env[i], "PATH", 4) == 0)
		i++;
	return (i);
}


char	*find_path(char *cmd, t_cmd *job)
{
	char	**paths;
	char	*path;
	int		i;

	path = NULL;
	i = find_path_env(job);
	if (job->env[i] == NULL)
		error(cmd, 1);
	paths = ft_split(job->env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		if (path)
			free(path);
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_free_s1(path, cmd);
		if (access(path, F_OK) == 0)
		{
			ft_free_tab(paths);
			return (path);
		}
	}
	free(path);
	ft_free_tab(paths);
	return (NULL);
}

void	executor(char **argv, t_cmd *cmd)
{
	char	*path;

	execve(argv[0], argv, cmd->env);
	if (ft_strchr(argv[0], '/') != NULL)
	{
		if (access(argv[0], F_OK) == 0)
			error(argv[0], 2);
		error(argv[0], 1);
	}
	path = find_path(argv[0], cmd);
	if (path && (execve(path, argv, cmd->env) == -1))
		error(argv[0], 0);
	error(argv[0], 0);
}


void process(t_cmd *cmd, t_cmd *first)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		printf("error");
	if (cmd->pid == 0)
	{
		if (cmd->prev != NULL)
			dup2(cmd->prev->fd[0], STDIN_FILENO);
		if (cmd->next != NULL)
			dup2(cmd->fd[1], STDOUT_FILENO);
		check_redirection(cmd, 0);
		close(cmd->fd[0]);
		close(cmd->fd[1]);
		free_fd(first);
		if (cmd->argv && ms_builtins(cmd->argv, 1, first) == 1)
			executor(cmd->argv, first);
	}
	if (cmd->prev != NULL)
		close(cmd->prev->fd[0]);
	close(cmd->fd[1]);
}

t_cmd	*head_list(t_cmd *cmd)
{
	while (cmd)
	{
		if (!cmd->prev)
			return (cmd);
		cmd = cmd->prev;
	}
	return (cmd);
}

void ft_exec(t_cmd *cmd)
{
	t_cmd *first;
	int	status;
	
	first = cmd;
	init_pipe(cmd);
	// for (int i = 0; cmd->env[i]; i++)
	// {
	// 	for (int j = 0; cmd->env[i][j]; j++)
	// 	{
	// 		printf("%c", cmd->env[i][j]);
	// 	}
	// 	puts("\n");
	// }
	if (make_heredocs(cmd) == 1 || ft_builtin(cmd) == 1)
		return ;
	if (cmd && cmd->argv)
	{
		while (cmd)
		{
			process(cmd, first);
			cmd = cmd->next;
		}
			// first = head_list(first);
		while (first)
		{
			waitpid(first->pid, &status, 0);
			// if (WIFEXITED(status))
			// 	g_minishell.ret_exit = WEXITSTATUS(status);
			first = first->next;
		}
	}
}