/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:25:18 by medeana           #+#    #+#             */
/*   Updated: 2022/03/14 21:19:38 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ms_check_unset_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
	{
		printf("unset: '%s': not a valid identifier\n", arg);
		return (1);
	}
	i++;
	while (arg[i])
	{	
		if ((ft_isalnum(arg[i]) == 0 && arg[i] != '_') || arg[i] == '=')
		{
			printf("unset: '%s': not a valid identifier\n", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**ms_matrix_remove_line(char **matrix, char *line)
{
	int		i;
	int		j;
	char	**new_matrix;

	i = 0;
	j = 0;
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (matrix[i])
	{
		if (ft_strcmp(matrix[i], line) == 0)
			i++;
		if (matrix[i])
		{
			new_matrix[j++] = ft_strdup(matrix[i]);
			i++;
		}
	}
	new_matrix[j] = NULL;
	ft_free_tab(matrix);
	return (new_matrix);
}

char	**ms_unset_remove(char *arg, t_shell *shell)
{
	char	*line;

	line = NULL;
	line = ms_get_env(shell->env, arg);
	if (line != NULL)
		shell->env = ms_matrix_remove_line(shell->env, line);
	return (shell->env);
}

int	ms_unset(char **arg, t_shell *shell)
{
	int		i;
	char	**strings;
	int		ret;

	ret = 0;
	i = 0;
	while (arg[i])
	{
		if (ms_check_unset_arg(arg[i]) != 0)
		{
			i++;
			ret = 1;
			continue ;
		}
		strings = ft_split(arg[i], '=');
		shell->env = ms_unset_remove(strings[0], shell);
		shell->export = ms_unset_remove(strings[0], shell);
		ft_free_tab(strings);
		i++;
	}
	return (ret);
}
