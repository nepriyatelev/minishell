/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:45:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/06 16:45:32 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	ms_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
		printf("%s\n", cmd->env[i++]);
	return (0);
}

int	env_compare(char **env, char **arg, int i)
{
	char	**split;

	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], arg[0]) == 0)
		{
			ft_free_tab(split);
			break ;
		}
		i++;
		ft_free_tab(split);
	}
	return (i);
}

char	**ms_matrix_add_line(char **matrix, char *new_line)
{
	int		i;
	char	**new_matrix;

	i = 0;
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (matrix[i])
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = ft_strdup(new_line);
	i++;
	new_matrix[i] = NULL;
	ft_free_tab(matrix);
	return (new_matrix);
}

void	ms_set_env(char **env, char *value, t_cmd *cmd)
{
	int		i;
	char	**arg;

	i = 0;
	arg = ft_split(value, '=');
	i = env_compare(env, arg, i);
	if (env[i] == NULL)
	{
		cmd->env = ms_matrix_add_line(env, value);
		ft_free_tab(arg);
		return ;
	}
	free(env[i]);
	value = ft_strdup(value);
	env[i] = value;
	ft_free_tab(arg);
}

char	*ms_get_env(char **env, char *arg)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], arg) == 0)
		{
			ft_free_tab(split);
			break ;
		}
		else
			i++;
		ft_free_tab(split);
	}
	if (env[i] == NULL)
		return (NULL);
	return (env[i]);
}

void	check_shlvl(t_cmd *cmd)
{
	char	*var;
	char	*var1;
	int		num;
	char	**arg;

	var = ms_get_env(cmd->env, "SHLVL");
	if (var == NULL)
	{
		cmd->env = ms_matrix_add_line(cmd->env, "SHLVL=1");
		return ;
	}
	arg = ft_split(var, '=');
	num = ft_atoi(arg[1]);
	num++;
	var = ft_itoa(num);
	var1 = ft_strjoin("SHLVL=", var);
	ms_set_env(cmd->env, var1, cmd);
	free (var);
	free (var1);
	ft_free_tab(arg);
	return ;
}

void	ms_init_env(char **env, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	cmd->env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		cmd->env[i] = ft_strdup(env[i]);
	cmd->env[i] = NULL;
	check_shlvl(cmd);
	return ;
}

t_cmd *init_list(t_cmd *list, char **env, char *cmd)
{
	int i = 0;
	int k = 0;
	
	list = (t_cmd *)malloc(sizeof(t_cmd));
	list->argv = ft_split(cmd, ' ');
	ms_init_env(env, list);
	list->next = NULL;
	list->prev = NULL;
	// list->next = (t_cmd *)malloc(sizeof(t_cmd));
	// list->next->argv = ft_split("wc -l", ' ');
	// ms_init_env(env, list->next);
	// list->next->next = NULL;
	// list->next->prev = list;
	// list->next->next = (t_cmd *)malloc(sizeof(t_cmd));
	// list->next->next->argv = ft_split(">> t.txt", ' ');
	// ms_init_env(env, list->next->next);
	// list->next->next->next = NULL;
	// list->next->next->prev = list->next;
	return (list);
}

int	main(int argc, char **argv, char **env)
{
	// kill(-1, SIGTERM);
	// t_shell	minishell;
	t_list	*list_env;
	t_cmd	*ex_cmd;
	char	*cmd;

	(void)argv;
	g_exit_status = 0;
	if (argc != 1)
		return (1);
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
		if (parsing(cmd, &list_env, &ex_cmd))
		{
			puts("проблема в парсере");
			return (1);
		}
		add_history(cmd);
		free(cmd);
		// ms_init_env(env, ex_cmd);
		// ft_lstclear(&minishell.tokens, free);
		// ft_lstclear(&minishell.list_env, free);
		// ft_lstclear(&minishell.cmd_separated_by_pipes, free);
		// ex_cmd = init_list(ex_cmd, env, cmd);
		// ft_exec(ex_cmd);
		// while (minishell.list_env)/*удалить*/
		// {
		// 	printf("TOKEN = %s\n", minishell.list_env->content);
		// 	minishell.list_env = minishell.list_env->next;
		// }
		// if (cmd)
		// 	free(cmd);
		// while (minishell.tokens)/*удалить*/
		// {
		// 	printf("TOKEN = %s\t TYPE = %d\n", minishell.tokens->content, minishell.tokens->type);
		// 	minishell.tokens = minishell.tokens->next;
		// }
		// printf("TOKEN = %s\t TYPE = %d\n", minishell.tokens->content, minishell.tokens->type);
		// while (cmd_separated_by_pipes)/*удалить*/
		// {
		// 	printf("TOKEN = %s\n", cmd_separated_by_pipes->content);
		// 	cmd_separated_by_pipes = cmd_separated_by_pipes->next;
		// }
		// int k = 1;
		// while (ex_cmd)/*удалить*/
		// {
		// 	printf("LIST = %d\n", k);
		// 	for(int i = 0; ex_cmd->argv[i]; i++)
		// 		printf("argv = %s\n", ex_cmd->argv[i]);
		// 	for(int i = 0; ex_cmd->file[i]; i++)
		// 		printf("file = %s\n", ex_cmd->file[i]);
		// 	// for(int i = 0; ex_cmd->env[i]; i++)
		// 	// 	printf("%s\n", ex_cmd->env[i]);
		// 	ex_cmd = ex_cmd->next;
		// 	k++;
		// 	puts("\n");
		// }
	}
	return (0);
}
