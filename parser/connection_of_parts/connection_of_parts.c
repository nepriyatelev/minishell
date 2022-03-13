/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_of_parts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:18:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/13 20:19:16 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	type_check(int type)
{
	if (type == BUILTIN || type == ARG)
		return (1);
	if (type == FILE_IN || type == HERE_DOC
		|| type == FILE_OUT || type == FILE_OUT_SUR
		|| type == OPEN_FILE || type == LIMITOR
		|| type == EXIT_FILE || type == EXIT_FILE_RET)
		return (2);
	if (type == PIPE)
		return (3);
	return (0);
}

int	ft_count_argv(t_list *tokens)
{
	t_list	*step;
	int		count_argv;

	count_argv = 0;
	step = tokens;
	while (step && step->type != PIPE)
	{
		if (step->type == BUILTIN || step->type == ARG)
			count_argv++;
		step = step->next;
	}
	return (count_argv);
}

int	ft_count_file(t_list *tokens)
{
	t_list	*step;
	int		count_file;

	count_file = 0;
	step = tokens;
	while (step && step->type != PIPE)
	{
		if (step->type == FILE_IN || step->type == HERE_DOC
			|| step->type == FILE_OUT || step->type == FILE_OUT_SUR
			|| step->type == OPEN_FILE || step->type == LIMITOR
			|| step->type == EXIT_FILE || step->type == EXIT_FILE_RET)
			count_file++;
		step = step->next;
	}
	return (count_file);
}

void	ft_copy_argv(char **argv, char *tokens, int type)
{
	static int	i;

	i = 0;
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

void	ft_copy_file(char **file, char *tokens, int type)
{
	static int	i;

	i = 0;
	if (type != 3)
	{
		file[i] = ft_strdup(tokens);
		i++;
	}
	else
	{
		file[i] = NULL;
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
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (args[i])
	{
		copy[i] = ft_strdup(args[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}


t_cmd	*new_ex_cmd(char **argv, char **file)
{
	t_cmd	*ex_cmd;

	ex_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!ex_cmd)
		return (NULL);
	ex_cmd->argv = ft_matrix_copy(argv);
	ex_cmd->file = ft_matrix_copy(file);
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
			step = step->next;
		new->prev = step;
		step->next = new;
	}
	else
		*ex_cmd = new;
}

void	copy_end(char **argv, char **file, t_cmd **ex_cmd)
{
	ft_copy_argv(argv, NULL, 3);
	ft_copy_file(file, NULL, 3);
	ex_cmd_add_back(ex_cmd, new_ex_cmd(argv, file));
	ft_matrix_free(argv);
	ft_matrix_free(file);
}

int	connection_of_parts(t_cmd **ex_cmd, t_list *tokens, char **argv, char **file)
{
	t_list	*step;

	step = tokens;
	argv = (char **)malloc(sizeof(char *) * (ft_count_argv(step) + 1));
	file = (char **)malloc(sizeof(char *) * (ft_count_file(step) + 1));
	printf("1 %d\t\t%d\n", ft_count_argv(step), ft_count_file(step));
	while (step)
	{
		if (type_check(step->type) == 1)
			ft_copy_argv(argv, step->content, 1);
		if (type_check(step->type) == 2)
			ft_copy_file(file, step->content, 2);
		if (type_check(step->type) == 3)
		{
			copy_end(argv, file, ex_cmd);
			step = step->next;
			printf("2 %d\t\t%d\n", ft_count_argv(step), ft_count_file(step));
			argv = (char **)malloc(sizeof(char *) * (ft_count_argv(step) + 1));
			file = (char **)malloc(sizeof(char *) * (ft_count_file(step) + 1));
			continue ;
		}
			step = step->next;
	}
	copy_end(argv, file, ex_cmd);
	return (0);
}
