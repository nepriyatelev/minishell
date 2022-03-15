/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editing_tokens_utilities.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 17:04:44 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/15 17:34:42 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	connecting_strings(int i, int j, char **new_str, char *content)
{
	if (i < j && content[i] != '\"')
		*new_str = ft_strjoin(*new_str, ft_substr(content, i, j - i));
	else
		*new_str = ft_strjoin(*new_str, ft_strdup(""));
	if (*new_str == NULL)
		return (-1);
	return (0);
}

static int	if_two_quotation_marks(int *j, char **new_str,
			char *content, t_list **list_env)
{
	int	i;

	i = ++(*j);
	while (content[*j] && content[*j] != '\"')
	{
		if (content[*j] == '$')
		{
			if (i < *j)
				*new_str = ft_strjoin(*new_str,
						ft_substr(content, i, (*j - i)));
			*new_str = ft_strjoin(*new_str, if_env(content + *j, j,
						list_env, 0));
			if (*new_str == NULL)
				return (-1);
			i = *j;
		}
		if (content[*j] == '\"')
			break ;
		else if (content[*j] == '$')
			continue ;
		(*j)++;
	}
	if (connecting_strings(i, *j, new_str, content))
		return (-1);
	return (0);
}

static int	if_one_quotation_mark(int *j, char **new_str, char *content)
{
	int	i;

	i = ++(*j);
	while (content[*j] && content[*j] != '\'')
		(*j)++;
	if (i < *j)
		*new_str = ft_strjoin(*new_str, ft_substr(content, i, (*j - i)));
	else
		*new_str = ft_strjoin(*new_str, ft_strdup(""));
	if (*new_str == NULL)
		return (-1);
	return (0);
}

static int	if_there_are_no_quotes(int *j, char **new_str,
			char *content, t_list **list_env)
{
	int	i;

	i = *j;
	while (content[*j] && content[*j] != '\'' && content[*j] != '\"')
	{
		if (content[*j] == '$')
		{
			if (i < *j)
				*new_str = ft_strjoin(*new_str, ft_substr(content, i, *j - i));
			*new_str = ft_strjoin(*new_str, if_env(content + *j, j,
						list_env, 0));
			if (*new_str == NULL)
				return (-1);
			i = *j;
		}
		if ((content[*j] == '\"' || content[*j] == '\''))
			break ;
		else if (content[*j] == '$')
			continue ;
		(*j)++;
	}
	if (connecting_strings(i, *j, new_str, content))
		return (-1);
	return (0);
}

int	modification_of_tokens(t_list *tokens, t_list **list_env)
{
	char	*new_str;
	int		j;

	new_str = ft_strdup("");
	if (new_str == NULL)
		return (-1);
	j = 0;
	while (tokens->content[j])
	{
		if (tokens->content[j] != '\'' && tokens->content[j] != '\"')
			if (if_there_are_no_quotes(&j, &new_str, tokens->content, list_env))
				return (-1);
		if (tokens->content[j] == '\'')
			if (if_one_quotation_mark(&j, &new_str, tokens->content))
				return (-1);
		if (tokens->content[j] == '\"')
			if (if_two_quotation_marks(&j, &new_str, tokens->content, list_env))
				return (-1);
		j++;
	}
	free(tokens->content);
	tokens->content = new_str;
	return (0);
}
