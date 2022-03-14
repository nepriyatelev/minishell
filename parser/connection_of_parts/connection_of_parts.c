/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_of_parts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:18:24 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/14 21:05:06 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_count_argv(t_list *tokens)
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

static int	ft_count_file(t_list *tokens)
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
	static int	i = 0;

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
	static int	i = 0;

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

void	connection_of_parts(t_cmd **ex_cmd, t_list *tokens,
		char **argv, char **file)
{
	t_list	*step;

	step = tokens;
	argv = (char **)malloc(sizeof(char *) * (ft_count_argv(step) + 1));
	file = (char **)malloc(sizeof(char *) * (ft_count_file(step) + 1));
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
			argv = (char **)malloc(sizeof(char *) * (ft_count_argv(step) + 1));
			file = (char **)malloc(sizeof(char *) * (ft_count_file(step) + 1));
			continue ;
		}
			step = step->next;
	}
	copy_end(argv, file, ex_cmd);
}
