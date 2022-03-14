/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:42:05 by medeana           #+#    #+#             */
/*   Updated: 2022/03/14 21:17:22 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_check_export_arg(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
	{
		printf("export: '%s': not a valid identifier\n", arg);
		return (1);
	}
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			printf("export: '%s': not a valid identifier\n", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ms_export_sort(t_shell *shell)
{
	int	i;

	i = 0;
	ft_sort_tab(shell->export);
	while (shell->export[i])
		printf("%s\n", shell->export[i++]);
}

void	ms_export_valid_arg(char *arg, char *strings, t_shell *shell)
{
	char	*string;

	if (ft_strchr(arg, '=') == NULL)
	{
		if (ms_get_env(shell->export, strings) == NULL)
			shell->export = ms_matrix_add_line(shell->export, arg);
	}
	else
	{
		string = ms_make_string(arg);
		if (ms_get_env(shell->export, strings) != NULL)
		{
			arg = ft_strdup(arg);
			ms_set_env(shell->env, arg, shell);
			ms_set_env(shell->export, string, shell);
			free(arg);
		}
		else
		{	
			shell->env = ms_matrix_add_line(shell->env, arg);
			shell->export = ms_matrix_add_line(shell->export, string);
		}
		free(string);
	}
}

int	ms_export(char **arg, t_shell *shell)
{
	char	**strings;
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (arg[i])
	{
		if (ms_check_export_arg(arg[i]) != 0)
		{
			i++;
			continue ;
			ret = 1;
		}
		strings = ft_split(arg[i], '=');
		ms_export_valid_arg(arg[i], strings[0], shell);
		ft_free_tab(strings);
		i++;
	}
	if (arg[0] == NULL)
		ms_export_sort(shell);
	return (ret);
}
