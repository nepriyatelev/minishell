/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:34:01 by medeana           #+#    #+#             */
/*   Updated: 2022/03/14 21:19:25 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ms_matrix_add_line(char **matrix, char *new_line)
{
	int		i;
	char	**new_matrix;

	i = 0;
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (matrix[i])
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = ft_strdup(new_line);
	i++;
	new_matrix[i] = NULL;
	ft_free_tab(matrix);
	return (new_matrix);
}

void	ms_set_env(char **env, char *value, t_shell *shell)
{
	int		i;
	char	**arg;

	i = 0;
	arg = ft_split(value, '=');
	i = env_compare(env, arg, i);
	if (env[i] == NULL)
	{
		shell->env = ms_matrix_add_line(env, value);
		ft_free_tab(arg);
		return ;
	}
	free(env[i]);
	value = ft_strdup(value);
	env[i] = value;
	ft_free_tab(arg);
}

char	*ms_get_env(char **env, char *arg)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], arg) == 0)
		{
			ft_free_tab(split);
			break ;
		}
		else
			i++;
		ft_free_tab(split);
	}
	if (env[i] == NULL)
		return (NULL);
	return (env[i]);
}

void	check_shlvl(t_shell *shell)
{
	char	*var;
	char	*var1;
	int		num;
	char	**arg;

	var = ms_get_env(shell->env, "SHLVL");
	if (var == NULL)
	{
		shell->env = ms_matrix_add_line(shell->env, "SHLVL=1");
		return ;
	}
	arg = ft_split(var, '=');
	num = ft_atoi(arg[1]);
	num++;
	var = ft_itoa(num);
	var1 = ft_strjoin("SHLVL=", var);
	ms_set_env(shell->env, var1, shell);
	free (var);
	free (var1);
	ft_free_tab(arg);
	return ;
}

void	ms_init_env(char **env, t_shell *shell)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	shell->env = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (env[++i])
		shell->env[i] = ft_strdup(env[i]);
	shell->env[i] = NULL;
	check_shlvl(shell);
	return ;
}
