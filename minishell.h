/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:45:56 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/11 16:00:34 by modysseu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "./libft/libft.h"

# define NONE 0				// defaut set
# define ARG 1				// word
# define FILE_IN 2			// word == '<'
# define HERE_DOC 3			// word == '<<'
# define FILE_OUT 4			// word == '>'
# define FILE_OUT_SUR 5		// word == '>>'
# define OPEN_FILE 6		// word following '<'
# define LIMITOR 7			// word following '<<'
# define EXIT_FILE 8		// word following '>'
# define EXIT_FILE_RET 9	// word following '>>'
# define PIPE 10			// word == '|'
# define BUILTIN 11			// word == command

extern	int	g_exit_status;

typedef struct s_cmd
{
	pid_t			pid;
	char			**argv;
	char			**file;
	char			**env;
	int				fd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

int		main(int argc, char **argv, char **env);
/*
** parser/parsing_main.c
*/
int		parsing_main(char *cmd, t_list **list_env, t_cmd **ex_cmd);
/*
** parser/error_cmd.c
*/
int		error_pipe(char *cmd);
int		unclose_quote(char	*cmd, int i, int quotes);
/*
** parser/parser_utilities.c
*/
void	quote_status(char ch, int *quote);
int		new_lst_back(char *cmd, t_list **cmd_list);
/*
** parser/creating_tokens/creating_tokens.c
*/
int		creating_tokens(t_list **cmd_separated_by_pipes, t_list **tokens);
/*
** parser/creating_tokens/creating_a_token_type.c
*/
void	creating_a_token_type(t_list **tokens);
/*
** parser/creating_tokens/checking_the_token_type_error.c
*/
int		checking_the_token_type_error(t_list **tokens);
/*
** parser/creating_tokens/file_type_assignment.c
*/
void	file_type_assignment(t_list **tokens);


int		editing_tokens(t_list **tokens, t_list **list_env);
char	*if_env(char *str, int *j, t_list **list_env);
int		init_env(t_list **list_env, char **env);
#endif