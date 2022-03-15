/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:45:56 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/15 17:56:45 by medeana          ###   ########.fr       */
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
# include "/Users/medeana/.brew/Cellar/\
readline/8.1.2/include/readline/readline.h"
# include "/Users/medeana/.brew/Cellar/\
readline/8.1.2/include/readline/history.h"
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

extern int	g_exit_status;

typedef struct s_cmd
{
	pid_t			pid;
	char			**argv;
	char			**file;
	int				fd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

typedef struct s_shell
{
	char	**env;
	char	**export;
}				t_shell;

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
/*
** parser/editing_tokens/editing_tokens.c
*/
int		editing_tokens(t_list **tokens, t_list **list_env);
/*
** parser/editing_tokens/editing_tokens_utilities.c
*/
int		modification_of_tokens(t_list *tokens, t_list **list_env);
/*
** parser/editing_tokens/if_env_utilities.c
*/
char	*get_env(char *str, t_list **list_env);
void	get_len_var_env(char *str, int *dollar,
			int *question_mark, int *len_var);
/*
** parser/editing_tokens/if_env.c
*/
char	*if_env(char *str, int *j, t_list **list_env, int dollar);
/*
** parser/editing_tokens/init_env.c
*/
int		init_env(t_list **list_env, char **env);
/*
** parser/connection_of_parts/connection_of_parts.c
*/
void	ft_copy_argv(char **argv, char *tokens, int type);
void	ft_copy_file(char **file, char *tokens, int type);
void	connection_of_parts(t_cmd **ex_cmd, t_list *tokens,
			char **argv, char **file);
/*
** parser/connection_of_parts/connection_of_parts_utilities.c
*/
int		type_check(int type);
t_cmd	*new_ex_cmd(char **argv, char **file);
void	ex_cmd_add_back(t_cmd **ex_cmd, t_cmd *new);
void	copy_end(char **argv, char **file, t_cmd **ex_cmd);

//executor
void	ft_exec(t_cmd *cmd, t_shell *shell);
int		ms_check_export_arg(char *arg);
void	ms_export_sort(t_shell *shell);
void	ms_export_valid_arg(char *arg, char *strings, t_shell *shell);
int		ms_export(char **arg, t_shell *shell);
int		find_path_env(t_shell *shell);
char	*find_path(char *cmd, t_cmd *cmdl, t_shell *shell);
void	ft_free_tab(char **tabs);
void	executor(char **argv, t_cmd *cmd, t_shell *shell);
t_cmd	*head_list(t_cmd *cmd);
int		ft_builtin(t_cmd *cmd, t_shell *shell);
int		check_builtins(char **arg);
int		check_redirection(t_cmd *job, int quit);
int		ms_builtins(char **arg, int i, t_cmd *first, t_shell *shell);
void	restore_fd(int saved_stdin, int saved_stdout);
void	init_pipe(t_cmd *cmd);
int		make_heredocs(t_cmd *cmd, t_shell *shell);
int		check_heredoc(char **redir, int stdin_fd, t_cmd *cmd, t_shell *shell);
int		redir_heredoc(char *limiter, int fd, t_cmd *cmd, t_shell *shell);
void	heredoc(char *limiter, int *fd, t_cmd *cmd, t_shell *shell);
char	*ms_make_string(char *arg);
void	ms_init_export(t_shell *shell);
int		ms_cd(char *arg, t_shell *shell);
int		ms_echo(char **arg);
int		env_compare(char **env, char **arg, int i);
int		ms_env(t_shell *shell);
int		ms_check_exit_arg(char *arg);
void	ms_exit(char **arg, t_cmd *job, t_shell *shell);
void	free_exit(t_cmd *job, t_shell *shell);
char	**ms_matrix_add_line(char **matrix, char *new_line);
void	ms_set_env(char **env, char *value, t_shell *shell);
char	*ms_get_env(char **env, char *arg);
void	check_shlvl(t_shell *shell);
void	ms_init_env(char **env, t_shell *shell);
int		ms_pwd(void);
int		ft_isalpha(int c);
int		ms_check_unset_arg(char *arg);
char	**ms_matrix_remove_line(char **matrix, char *line);
char	**ms_unset_remove(char *arg, t_shell *shell);
int		ms_unset(char **arg, t_shell *shell);
int		open_file(char *argv, int i, int quit);
void	free_fd(t_cmd *first);
void	free_job_lst(t_cmd *job);
void	error(char *arg, int i, t_cmd *cmd, t_shell *shell);
void	stop_heredoc(int signal);
void	nothing(int signal);
void	ft_newline(int signal);
void	ctrl_c(int signal);
void	ctrl_d(char *line, t_shell *shell, t_list *list);
void	ft_sort_tab(char **arr);

#endif