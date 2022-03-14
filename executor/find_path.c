/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 19:04:46 by medeana           #+#    #+#             */
/*   Updated: 2022/03/14 21:17:42 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_path_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i] && ft_strnstr(shell->env[i], "PATH", 4) == 0)
		i++;
	return (i);
}

char	*find_path(char *cmd, t_cmd *cmdl, t_shell *shell)
{
	char	**paths;
	char	*path;
	int		i;

	path = NULL;
	i = find_path_env(shell);
	if (shell->env[i] == NULL)
		error(cmd, 1, cmdl, shell);
	paths = ft_split(shell->env[i] + 5, ':');
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

void	executor(char **argv, t_cmd *cmd, t_shell *shell)
{
	char	*path;

	execve(argv[0], argv, shell->env);
	if (ft_strchr(argv[0], '/') != NULL)
	{
		if (access(argv[0], F_OK) == 0)
			error(argv[0], 2, cmd, shell);
		error(argv[0], 1, cmd, shell);
	}
	path = find_path(argv[0], cmd, shell);
	if (path && (execve(path, argv, shell->env) == -1))
		error(argv[0], 0, cmd, shell);
	error(argv[0], 0, cmd, shell);
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
