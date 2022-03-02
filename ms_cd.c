/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:19:28 by medeana           #+#    #+#             */
/*   Updated: 2022/02/26 17:59:44 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(char *arg, char	*c, t_cmd *cmd)
{
	char	*string;

	string = ft_strjoin(arg, c);
	ms_set_env(cmd->env, string, cmd);
	free (string);
}

int ms_cd(char *argv, t_cmd *cmd)
{
	char	c[PATH_MAX];

	if (argv == NULL)
	{
		argv = ms_get_env(cmd->env, "HOME") + 5;
		if (argv - 5 == NULL)
		{
			printf("not HOME\n");
			return (1);
		}
	}
	getcwd(c, sizeof(c));
	if (chdir(argv) == -1)
	{
		if (argv[0] == '\0')
			return (1);
		printf("cd: %s No such file or directory\n", argv);
		return (1);
	}
	set_pwd("OLDPWD=", c, cmd);
	getcwd(c, sizeof(c));
	set_pwd("PWD=", c, cmd);
	return (0);
}