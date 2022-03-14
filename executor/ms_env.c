/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:35:03 by medeana           #+#    #+#             */
/*   Updated: 2022/03/14 21:18:53 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
		printf("%s\n", shell->env[i++]);
	return (0);
}

int	env_compare(char **env, char **arg, int i)
{
	char	**split;

	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], arg[0]) == 0)
		{
			ft_free_tab(split);
			break ;
		}
		i++;
		ft_free_tab(split);
	}
	return (i);
}
