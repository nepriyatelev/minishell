/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:44:09 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/06 15:22:09 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int modif1(t_list *tokens, t_list **list_env)
// {
// 	char	*new_str;
// 	int		j;
// 	int		i;

// 	new_str = ft_strdup("");
// 	j = 0;
// 	i = 0;
// 	while (tokens->content[j])
// 	{
// 		if (tokens->content[j] != '\'' && tokens->content[j] != '\"')
// 		{
// 			i = j;
// 			while (tokens->content[j] && tokens->content[j] != '\'' && tokens->content[j] != '\"')
// 			{
// 				if (tokens->content[j] == '$')
// 				{
// 					if (i < j)
// 						new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
// 					new_str = ft_strjoin(new_str, if_env(tokens->content + j, &j, list_env));
// 					i = j;
// 				}
// 				if ((tokens->content[j] == '\"' || tokens->content[j] == '\''))
// 					break ;
// 				else if (tokens->content[j] == '$')
// 					continue ;
// 				j++;
// 			}
// 			if (i < j) 
// 				new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
// 			else
// 				new_str = ft_strjoin(new_str, ft_strdup(""));
// 		}
// 		if (tokens->content[j] == '\'')
// 		{
// 			i = ++j;
// 			while (tokens->content[j] && tokens->content[j] != '\'')
// 				j++;
// 			if (i < j)
// 				new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
// 			else
// 				new_str = ft_strjoin(new_str, ft_strdup(""));
// 		}
// 		if (tokens->content[j] == '\"')
// 		{
// 			i = ++j;
// 			while (tokens->content[j] && tokens->content[j] != '\"')
// 			{
// 				if (tokens->content[j] == '$')
// 				{
// 					if (i < j)
// 						new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
// 					new_str = ft_strjoin(new_str, if_env(tokens->content + j, &j, list_env));
// 					i = j;
// 				}
// 				if (tokens->content[j] == '\"')
// 					break ;
// 				else if (tokens->content[j] == '$')
// 					continue ;
// 				j++;
// 			}
// 			if (i < j && tokens->content[i] != '\"')
// 				new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
// 			else
// 				new_str = ft_strjoin(new_str, ft_strdup(""));
// 		}
// 			j++;
// 	}
// 	free(tokens->content);
// 	tokens->content = new_str;
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
					{
						new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
						if (new_str == NULL)
							return (1);
					}
					new_str = ft_strjoin(new_str, if_env(tokens->content + j, &j, list_env));
					if (new_str == NULL)
						return (1);
					i = j;
				}
				if ((tokens->content[j] == '\"' || tokens->content[j] == '\''))
					break ;
				else if (tokens->content[j] == '$')
					continue ;
				j++;
			}
			if (i < j) 
			{
				new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
				if (new_str == NULL)
					return (1);
			}
			else
			{
				new_str = ft_strjoin(new_str, ft_strdup(""));
				if (new_str == NULL)
					return (1);
			}
		}
		if (tokens->content[j] == '\'')
		{
			i = ++j;
			while (tokens->content[j] && tokens->content[j] != '\'')
				j++;
			if (i < j)
			{
				new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
				if (new_str == NULL)
					return (1);
			}
			else
			{
				new_str = ft_strjoin(new_str, ft_strdup(""));
				if (new_str == NULL)
					return (1);
			}
		}
		if (tokens->content[j] == '\"')
		{
			i = ++j;
			while (tokens->content[j] && tokens->content[j] != '\"')
			{
				if (tokens->content[j] == '$')
				{
					if (i < j)
					{
						new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
						if (new_str == NULL)
							return (1);
					}
					new_str = ft_strjoin(new_str, if_env(tokens->content + j, &j, list_env));
					if (new_str == NULL)
						return (1);
					i = j;
				}
				if (tokens->content[j] == '\"')
					break ;
				else if (tokens->content[j] == '$')
					continue ;
				j++;
			}
			if (i < j && tokens->content[i] != '\"')
			{
				new_str = ft_strjoin(new_str, ft_substr(tokens->content, i, j - i));
				if (new_str == NULL)
					return (1);
			}
			else
			{
				new_str = ft_strjoin(new_str, ft_strdup(""));
				if (new_str == NULL)
					return (1);
			}
		}
			j++;
	}
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