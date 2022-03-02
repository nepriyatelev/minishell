/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:44:09 by modysseu          #+#    #+#             */
/*   Updated: 2022/02/25 03:45:38 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*modif_single_qoute(char *str, int *j, int *quote)
// {
// 	int		i;
// 	i = *j;
// 	while (str[*j] && str[*j] != '\'')
// 		(*j)++;
// 	quote_status(str[*j], quote);
// 	return (ft_substr(str, i, (*j - i)));
// }

// char	*modif_double_qoute(char *str, int *j,  t_list **list_env, int *quote)
// {
// 	int		i;
// 	i = *j;
// 	if (str[*j] == '$')
// 	{
// 		return (if_env_for_unquote(str + (*j), j, list_env));
// 	}
// 	else
// 	{
// 		while (str[*j] && str[*j] != '\"' && str[*j] != '$')
// 			(*j)++;
// 		quote_status(str[*j], quote);
// 		return (ft_substr(str, i, *j - i));
// 	}
// 	return (NULL);
// }


// char *modif_unqoute(char *str, int *j, t_list **list_env, int *quote)
// {
// 	int	i = *j;
// 	if (str[*j] == '$')
// 		return (if_env_for_unquote(str + (*j), j, list_env));
// 	else
// 	{
// 		while (str[*j] && str[*j] != '\'' && str[*j] != '\"' && str[*j] != '$')
// 			(*j)++;
// 		quote_status(str[*j], quote);
// 		return (ft_substr(str, i, *j - i));
// 	}
// 	return (NULL);
// }

// int modif1(t_list *tokens, t_list **list_env)
// {
// 	char	*new_str;
// 	int		j;
// 	char	*tmp_str;
// 	int		quote;

// 	tmp_str = ft_strdup("");
// 	j = 0;
// 	quote = 0;
// 	while (tokens->content[j])
// 	{
// 		quote_status(tokens->content[j], &quote);
// 		printf("start = %c\t index == %d\n", tokens->content[j], j);
// 		if (quote == 0)
// 			new_str = modif_unqoute(tokens->content, &j, list_env, &quote); //проверку на  NULL
// 		else if (quote == 1)
// 		{
// 			if (tokens->content[j] == '\'')
// 				j++;
// 			new_str = modif_single_qoute(tokens->content, &j, &quote); //проверку на  NULL
// 		}
// 		else if (quote == 2)
// 		{
// 			if (tokens->content[j] == '\"')
// 				j++;
// 			new_str = modif_double_qoute(tokens->content, &j, list_env, &quote); //проверку на  NULL
// 		}
// 		tmp_str = ft_strjoin(tmp_str, new_str);
// 		// printf("tmp_str ==  %s\n", tmp_str);
// 		// quote_status(tokens->content[j], &quote);
// 		printf("  end = %c\t index == %d\n", tokens->content[j], j);
// 		// printf("tokens->content[j] = %c\n", tokens->content[j]);
// 		// printf("tmp_str = %s\n", tmp_str);
// 		if (tokens->content[j] == '$')
// 			continue ;
// 		j++;
// 	}
// 	free(tokens->content);
// 	tokens->content = tmp_str;
// 	return (0);
// }

int modif1(t_list *tokens, t_list **list_env)
{
	char	*new_str;
	int		j;
	int		i;

	new_str = ft_strdup("");
	j = 0;
	i = 0;
	// printf("strlen = %zu\n", ft_strlen(tokens->content));
	while (tokens->content[j])
	{
		if (tokens->content[j] != '\'' && tokens->content[j] != '\"')
		{
			i = j;
			while (tokens->content[j] && tokens->content[j] != '\'' && tokens->content[j] != '\"')
			{
				if (tokens->content[j] == '$')
				{
					if (i < j)
						new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
					// printf("tokens->content = %s\t j = %d\n", tokens->content + j, j);
					new_str = ft_strjoin(new_str, if_env(tokens->content + j, &j, list_env));
					// printf("j = %d\n", j);
					// printf("tokens->content[j] = %c\n", tokens->content[j]);
					i = j;
				}
				if ((tokens->content[j] == '\"' || tokens->content[j] == '\''))
					break ;
				else if (tokens->content[j] == '$')
					continue ;
				j++;
			}
			// printf("i = %d\t j = %d\n", i, j);
			if (i < j) 
				new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
			else
				new_str = ft_strjoin(new_str, ft_strdup(""));
		}
		if (tokens->content[j] == '\'')
		{
			i = ++j;
			while (tokens->content[j] && tokens->content[j] != '\'')
				j++;
			// printf("one i = %d\t j = %d\n", i, j);
			if (i < j)
				new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
			else
				new_str = ft_strjoin(new_str, ft_strdup(""));
		}
		if (tokens->content[j] == '\"')
		{
			i = ++j;
			while (tokens->content[j] && tokens->content[j] != '\"')
			{
				if (tokens->content[j] == '$')
				{
					if (i < j)
						new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
					new_str = ft_strjoin(new_str, if_env(tokens->content + j, &j, list_env));
					// printf("tokens->content[j] = %c\n", tokens->content[j]);
					i = j;
				}
				if (tokens->content[j] == '\"')
					break ;
				else if (tokens->content[j] == '$')
					continue ;
				j++;
			}
			// printf("i = %d\t j = %d\n", i, j);
			if (i < j && tokens->content[i] != '\"')
				new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
			else
				new_str = ft_strjoin(new_str, ft_strdup(""));
			// printf("tokens->content[j] = %c\t j = %d\n", tokens->content[j], j);	
		}
			j++;
	}
	// printf("strlen = %zu\n", ft_strlen(new_str));
	free(tokens->content);
	tokens->content = new_str;
	return (0);
}

int	word_modif(t_list **tokens, t_list **list_env)
{
	t_list *step;

	step = *tokens;
	while (step)
	{
		if (step->content != NULL)
		{
			if (modif1(step, list_env))
				return (1);
		}
		step = step->next;
	}
	return 0;
}