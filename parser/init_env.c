/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 16:13:11 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/11 16:00:13 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	increment_shlvl(t_list **list_env)
{
	char	*shlvl_value;
	int		shlvl;
	t_list	*step;

	step = *list_env;
	shlvl_value = getenv("SHLVL");
	if (ft_strcmp(shlvl_value, "") == 0)
		return (1);
	shlvl = ft_atoi(shlvl_value) + 1;
	while (step)
	{
		if (ft_strncmp("SHLVL", step->content, 5) == 0)
		{
			free(step->content);
			step->content = ft_strjoin("SHLVL=", ft_itoa(shlvl));
			if (step->content == NULL)
				return (1);
			return (0);
		}
		step = step->next;
	}
	return (0);
}

int	init_env(t_list **list_env, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		ft_lstadd_back(list_env, ft_lstnew(ft_strdup(env[i++]))); //проверку на NULL
	if (increment_shlvl(list_env))
		return (1);
	return (0);
}
