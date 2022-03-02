/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 22:01:27 by modysseu          #+#    #+#             */
/*   Updated: 2022/02/25 04:40:31 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// char *get_env(char *cpy, t_list **list_env)
// {
// 	t_list *tmp;
// 	int		i = 0;
// 	int		j = 0;
// 	while (cpy[i] != '\0' && cpy[i] != '=')
// 		i++;
// 	tmp = *list_env;
// 	while (tmp)
// 	{
// 		while (tmp->content[j] != '\0' && tmp->content[j] != '=')
// 			j++;
// 		if (i == j && ft_strncmp(tmp->content, cpy, i) == 0)
// 			return (ft_strdup(tmp->content + (i + 1)));
// 		j = 0;
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// int get_len_var_env(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[0] == '$')
// 			str++;
// 		else if (str[0] =='?')
// 			return (1);
// 		else if (((ft_isalnum(str[i]) == 1) || str[i] == '_'))
// 			i++;
// 		else
// 			break ;
// 	}
// 	return (i);
// }

// char *if_env(char *str, int *j, t_list **list_env)
// {
// 	char *cpy;
// 	char *env;
// 	int len_str;

// 	len_str = get_len_var_env(str);
// 	printf("str = %s\n", str);
// 	// printf("%d\n", *j);
// 	if (len_str == 0)
// 	{
// 		++(*j);
// 		return (ft_strdup("$"));
// 	}
// 	if (len_str == 1 && str[1] == '?')
// 	{
// 		*j += 2;
// 		return (ft_strdup(ft_itoa(g_exit_status)));
// 	}
// 	cpy = ft_substr(str, 1, len_str); //возможно не работает
// 	// printf("cpy = %s\n", cpy);
// 	env = get_env(cpy, list_env);
// 	// printf("env = %s\n", env);
// 	free(cpy);
// 	if (env == NULL)
// 	{
// 		*j += len_str + 1;
// 		// cpy = (char *)malloc(sizeof(char)); //проверка на NULL
// 		// cpy[0] = '\0';
// 		return (ft_strdup(""));
// 	}
// 	*j += len_str + 1;
// 	// printf("\n%c\n", str[*j]);
// 	return (env);
// }

char *get_env(char *str, t_list **list_env)
{
	t_list *tmp;
	int		i = 0;
	int		j = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = *list_env;
	while (tmp)
	{
		while (tmp->content[j] && tmp->content[j] != '=')
			j++;
		if (i == j && ft_strncmp(tmp->content, str, i) == 0)
			return (ft_strdup(tmp->content + (j + 1)));
		j = 0;
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

void get_len_var_env(char *str, int *dollar, int *question_mark, int *len_var)
{
	int	i;

	i = 0;
	if (str[*dollar] == '$')
	{
		while (str[*dollar] && str[*dollar] == '$')
			(*dollar)++;
		if (str[*dollar] == '?')
		{
			(*question_mark)++;
			return ;
		}
	}
	str += (*dollar);
	while (str[*len_var] && ((ft_isalnum(str[*len_var]) == 1) || str[*len_var] == '_'))
		(*len_var)++;
}

char *if_env(char *str, int *j, t_list **list_env)
{
	char *env;
	int	len_var;
	int	dollar;
	int	question_mark;
	char *new_str;
	new_str = ft_strdup(""); //проверка 0
	
	len_var = 0;
	dollar = 0;
	question_mark = 0;
	get_len_var_env(str, &dollar, &question_mark, &len_var);
	// printf("str = %s\n", str);
	// printf("len_var = %d\n", len_var);
	// printf("dollar = %d\n", dollar);
	// printf("question_mark = %d\n", question_mark);
	if (dollar != 0 && question_mark == 0 && len_var == 0)
	{
		(*j) += dollar;
		while (dollar)
		{
			new_str = ft_strjoin(new_str, "$");
			dollar--;
		}
	}
	else if (dollar != 0 && question_mark == 1 && len_var == 0)
	{
		(*j) += dollar + question_mark;
		if (dollar % 2 == 0)
		{
			while (dollar)
			{
				new_str = ft_strjoin(new_str, "$");
				dollar--;
			}
			new_str = ft_strjoin(new_str, "?");
		}
		else
		{
			while (dollar - 1)
			{
				new_str = ft_strjoin(new_str, "$");
				dollar--;
			}
			new_str = ft_strjoin(new_str, ft_itoa(g_exit_status));
		}
	}
	else if (dollar != 0 && question_mark == 0 && len_var != 0)
	{
		*j += len_var + dollar;
		if (dollar % 2 == 0)
		{
			while (dollar)
			{
				new_str = ft_strjoin(new_str, "$");
				dollar--;
			}
			new_str = ft_strjoin(new_str, ft_substr(str, (int)ft_strlen(new_str), len_var));
		}
		else
		{
			while (dollar - 1)
			{
				new_str = ft_strjoin(new_str, "$");
				dollar--;
			}
			// printf("ft_strlen(new_str) - dollar = %d\n", (int)ft_strlen(new_str) + dollar);
			new_str = ft_strjoin(new_str, get_env(ft_substr(str, (int)ft_strlen(new_str) + dollar, len_var), list_env));
		}
	}
	return (new_str);
}