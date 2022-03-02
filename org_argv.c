/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   org_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:43:31 by modysseu          #+#    #+#             */
/*   Updated: 2022/02/19 15:20:26 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int len_arg(t_list *tokens)
// {
// 	int i = 0;
// 	t_list *tmp;

// 	tmp = tokens;
// 	while (tmp)
// 	{
// 		if (tmp->type == ARG || tmp->type == BUILTIN)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// int org_argv(t_list *tokens)
// {
// 	t_list *tmp;
// 	int i = 0;

// 	tmp = tokens;
// 	g_minishell.argv = (char **)malloc(sizeof(char *) * len_arg(tokens) + 1); //проверку на NULL
// 	while (tmp)
// 	{
// 		if (tmp->type == ARG || tmp->type == BUILTIN)
// 		{
// 			g_minishell.argv[i] = ft_strdup(tmp->content); // проверку на  NULL
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// 	g_minishell.argv[i] = NULL;
// 	return 0;
// }