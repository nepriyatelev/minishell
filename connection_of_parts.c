/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_of_parts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:18:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/02 17:14:05 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	type_check(int type)
{
	if (type == BUILTIN || type == ARG)
		return (1);
	if  (type == FILE_IN || type == HERE_DOC
		|| type == FILE_OUT || type == FILE_OUT_SUR
		|| type == OPEN_FILE || type == LIMITOR
		|| type == EXIT_FILE || type == EXIT_FILE_RET)
		return (2);
	if (type == PIPE)
		return (3);
	return (0);
}

void	ft_count(t_list *tokens, int *count_argv, int *count_file)
{
	t_list	*step;

	step = tokens;
	while (step && step->type != PIPE)
	{
		if (step->type == BUILTIN || step->type == ARG)
			(*count_argv)++;
		if (step->type == FILE_IN || step->type == HERE_DOC
			|| step->type == FILE_OUT || step->type == FILE_OUT_SUR
			|| step->type == OPEN_FILE || step->type == LIMITOR
			|| step->type == EXIT_FILE || step->type == EXIT_FILE_RET)
			(*count_file)++;
		step = step->next;
	}
}

void ft_copy_argv(char **argv, char *tokens, int type)
{
	static int i = 0;
	if (type != 3)
	{
		argv[i] = ft_strdup(tokens);
		i++;
	}
	else
	{
		argv[i] = NULL;
		i = 0;
	}
}

void ft_copy_file(char **argv, char *tokens, int type)
{
	static int i = 0;
	if (type != 3)
	{
		argv[i] = ft_strdup(tokens);
		i++;
	}
	else
	{
		argv[i] = NULL;
		i = 0;
	}
}

char	**ft_matrix_copy(char **args)
{
	char	**copy;
	int		i;

	while (args[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (args[i])
	{
		copy[i] = ft_strdup(args[i]);
		i++;
	}
	copy[i] = NULL;
	return copy;
}

char	**ft_list_copy_in_matrix(t_list *env)
{
	t_list	*step;
	char	**copy;
	int		i;

	i = ft_lstsize(env);
	copy = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	step = env;
	while (step)
	{
		copy[i] = ft_strdup(step->content);
		i++;
		step = step->next;
	}
	copy[i] = NULL;
	return copy;
}

t_cmd	*new_ex_cmd(char **argv, char **file, t_list *env)
{
	t_cmd	*ex_cmd;
	ex_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!ex_cmd)
		return (NULL);
	ex_cmd->pid = 0;
	ex_cmd->argv = ft_matrix_copy(argv);
	ex_cmd->file = ft_matrix_copy(file);
	ex_cmd->env = ft_list_copy_in_matrix(env);
	ex_cmd->fd[0] = 0;
	ex_cmd->fd[1] = 0;
	ex_cmd->next = NULL;
	ex_cmd->prev = NULL;
	return (ex_cmd);
}

void ex_cmd_add_back(t_cmd **ex_cmd, t_cmd *new)
{
	t_cmd	*step;
	
	if (*ex_cmd != NULL)
	{
		step = *ex_cmd;
		while (step->next != NULL)
		{
			if (step->next->next == NULL)
				step->prev = step;
			step = step->next;
		}
		step->next = new;
	}
	else
		*ex_cmd = new;
}
void	ft_matrix_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{	
		free(str[i]);
		i++;
	}
	free(str);
}

void	connection_of_parts(t_cmd **ex_cmd, t_list *tokens, t_list *env)
{

	t_list	*step;
	char	**argv;
	char	**file;
	int		count_argv;
	int		count_file;
	
	count_argv = 0;
	count_file = 0;
	step = tokens;
	ft_count(step, &count_argv, &count_file);
	// printf("1\tcount_file = %d\tcount_argv = %d\n", count_file, count_argv);
	argv = (char **)malloc(sizeof(char *) * (count_argv + 1));
	file = (char **)malloc(sizeof(char *) * (count_file + 1));
	while(step)
	{
		if (type_check(step->type) == 1)
			ft_copy_argv(argv, step->content, 1);
		if (type_check(step->type) == 2)
			ft_copy_file(file, step->content, 2);
		if (type_check(step->type) == 3)
		{
			ft_copy_argv(argv, NULL, 3);
			ft_copy_file(file, NULL, 3);
			ex_cmd_add_back(ex_cmd, new_ex_cmd(argv, file, env));
			step = step->next;
			ft_matrix_free(argv);
			ft_matrix_free(file);
			count_argv = 0;
			count_file = 0;
			ft_count(step, &count_argv, &count_file);
			// printf("2\tcount_file = %d\tcount_argv = %d\n", count_file, count_argv);
			argv = (char **)malloc(sizeof(char *) * (count_argv + 1));
			file = (char **)malloc(sizeof(char *) * (count_file + 1));
			// printf("step->content = %s\n", step->content);
			continue ;
		}
			step = step->next;
	}
	ft_copy_argv(argv, NULL, 3);
	ft_copy_file(file, NULL, 3);
	ex_cmd_add_back(ex_cmd, new_ex_cmd(argv, file, env));
	ft_matrix_free(argv);
	ft_matrix_free(file);
	// for(int i = 0; argv[i]; i++)
	// {
	// 	printf("argv = %s\n", argv[i]);
	// }
	// for(int i = 0; file[i]; i++)
	// {
	// 	printf("file = %s\n", file[i]);
	// }
}
