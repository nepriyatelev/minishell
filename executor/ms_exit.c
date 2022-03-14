/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:59:47 by medeana           #+#    #+#             */
/*   Updated: 2022/03/14 21:19:12 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_check_exit_arg(char *arg)
{
	int			i;
	long long	exit_code;

	i = 0;
	while (arg[i] == ' ')
		i++;
	if (arg[i] && (arg[i] == '+' || arg[i] == '-'))
		i++;
	if (ft_isdigit(arg[i]) == 0 || ft_isllong(arg) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", arg);
		g_exit_status = 255;
		return (1);
	}
	exit_code = ft_atoll(arg);
	g_exit_status = exit_code % 256;
	if (g_exit_status < 0 || g_exit_status > 255)
		g_exit_status = 255;
	return (0);
}

void	ms_exit(char **arg, t_cmd *job, t_shell *shell)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (arg[0])
	{
		i = ms_check_exit_arg(arg[0]);
		if (arg[1] && i == 0)
		{
			printf("minishell: exit: too many arguments\n");
			g_exit_status = 1;
			return ;
		}
	}
	free_exit(job, shell);
	exit(g_exit_status);
}

void	free_exit(t_cmd *job, t_shell *shell)
{
	ft_free_tab(shell->env);
	free_job_lst(job);
	rl_clear_history();
}
