/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:33:04 by medeana           #+#    #+#             */
/*   Updated: 2022/03/14 21:18:26 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ms_make_string(char *arg)
{
	char	**strings;
	char	*string;
	int		i;

	i = 1;
	strings = ft_split(arg, '=');
	string = ft_strjoin(strings[0], "=");
	while (strings[i] && strings[i + 1])
	{
		string = ft_strjoin_free_s1(string, strings[i++]);
		string = ft_strjoin_free_s1(string, "=");
	}
	if (strings[i])
		string = ft_strjoin_free_s1(string, strings[i]);
	string = ft_strjoin_free_s1(string, "");
	ft_free_tab(strings);
	return (string);
}

void	ms_init_export(t_shell *shell)
{
	int		i;
	char	*string;

	i = 0;
	while (shell->env[i])
		i++;
	shell->export = malloc(sizeof(char *) * (i));
	i = 0;
	if (shell->env[i])
	{
		while (shell->env[i + 1])
		{
			string = ms_make_string(shell->env[i]);
			shell->export[i] = ft_strdup(string);
			free(string);
			i++;
		}
	}
	shell->export[i] = NULL;
}
