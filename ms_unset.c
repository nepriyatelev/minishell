/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:25:18 by medeana           #+#    #+#             */
/*   Updated: 2022/02/27 18:31:52 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("unset: '%s': invalid parameter name\n", arg);
		return (1);
	}
	i++;
	while (arg[i])
	{	
		if ((ft_isalnum(arg[i]) == 0 && arg[i] != '_') || arg[i] == '=')
		{
			printf("unset: '%s': invalid parameter name\n", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**remove_line(char **matrix, char *line)
{
	int		i;
	int		j;
	char	**new_matrix;

	i = 0;
	j = 0;
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i));
	i = 0;
	while (matrix[i])
	{
		if (ft_strcmp(matrix[i], line) == 0)
			i++;
		if (matrix[i])
		{
			new_matrix[j] = ft_strdup(matrix[i]);
			j++;
			i++;
		}
	}
	new_matrix[j] = NULL;
	ft_free_tab(matrix);
	return (new_matrix);
}

char	**ms_unset_remove(char **env, char *arg)
{
	char	*line;

	line = NULL;
	line = ms_get_env(env, arg);
	if (line != NULL)
		env = remove_line(env, line);
	return (env);
}

int ms_unset(t_cmd *cmd, char **argv)
{
	int		i;
	int		ret;
	char	**str;

	i = 0;
	ret = 0;
	// if (g_shell.env)
	// 	ft_free_tab(g_shell.env);
	while (argv[i])
	{
		if (ms_check_unset_arg(argv[i]) != 0)
		{
			i++;
			continue ;
		}
		str = ft_split(argv[i], '=');
		cmd->env = ms_unset_remove(cmd->env, str[0]);
		ft_free_tab(str);
		i++;
	}
	// for (int i = 0; cmd->env[i]; i++)
	// 	printf("%s\n", g_shell.env[i]);
	// i = 0;
	// int k = 0;
	// while (cmd->env[i])
	// 	i++;
	// g_shell.env = malloc(sizeof(char *) * (i + 1));
	// i = 0;
	// while (cmd->env[i])
	// {
	// 	g_shell.env[k] = ft_strdup(cmd->env[i]);
	// 	i++;
	// 	k++;
	// }
	// g_shell.env[k] = NULL;
	// for (int i = 0; g_shell.env[i]; i++)
	// 	printf("%s\n", g_shell.env[i]);
	return (0);
}