/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:45:56 by modysseu          #+#    #+#             */
/*   Updated: 2022/03/02 15:31:18 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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

// #include "../include/library_function.h"

#define NONE 0			// defaut set
#define ARG 1			// word
#define FILE_IN 2		// word == '<'
#define HERE_DOC 3		// word == '<<'
#define FILE_OUT 4		// word == '>'
#define FILE_OUT_SUR 5	// word == '>>'
#define OPEN_FILE 6		// word following '<'
#define LIMITOR 7		// word following '<<'
#define EXIT_FILE 8		// word following '>'
#define EXIT_FILE_RET 9 // word following '>>'
#define PIPE 10			// word == '|'
#define BUILTIN 11		// word == command

extern	int	g_exit_status;

typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
}					t_list;

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

typedef struct s_shell
{
	t_list		*cmd_separated_by_pipes;
	t_list		*tokens;
	t_list		*list_env;
}				t_shell;

/*library*/
int	ft_lstsize(t_list *lst);
int	ft_isalnum(int c);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
t_list	*ft_lstnew(char *content);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strncpy(char *dst, char *src, int n);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char	*big, const char *little, size_t len);



int		parsing(char *cmd, t_list **cmd_separated_by_pipes, t_list **tokens, t_list **list_env);
int		tokenizer(t_list **list, t_list **tokens);
int 	token_processing(t_list	**tokens);
void	quote_status(char ch, int *quote);
int		word_modif(t_list **tokens, t_list **list_env);
// int org_argv(t_list *tokens);
char *if_env(char *str, int *j, t_list **list_env);
int	init_env(t_list **list_env, char **env);
void	ms_set_env(char **env, char *value, t_cmd *cmd);

void connection_of_parts(t_cmd **ex_cmd, t_list *tokens, t_list *env);


int	ft_isalnum(int c);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
// int	ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strncpy(char *dst, char *src, int n);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstadd_back(t_list **lst, t_list *new);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strncpy(char *dst, char *src, int n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int 	ft_isspace(int c);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
int	ft_isllong(char *str);
int	ft_isdigit(int c);
long long	ft_atoll(const char *nptr);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char	*big, const char *little, size_t len);
char	**copy_envp(char **env);







int		parsing(char *cmd, t_list **cmd_separated_by_pipes, t_list **tokens, t_list **list_env);
int		tokenizer(t_list **list, t_list **tokens);
int 	token_processing(t_list	**tokens);
void	quote_status(char ch, int *quote);
int		word_modif(t_list **tokens, t_list **list_env);
char *if_env(char *str, int *j, t_list **list_env);
int	init_env(t_list **list_env, char **env);

int org_argv(t_list *tokens);
int	ft_built_in_echo_fd(char **str, int fd);
int	ft_check_n(char **str);
int	ms_echo(char **arg);
int	ms_newline(char *arg);
int	ms_builtins(char **arg, int i, t_cmd *job);
int	ms_pwd(void);
char	*find_path(char *cmd, t_cmd *job);
t_cmd	*head_list(t_cmd *cmd);
void ft_exec(t_cmd *cmd);
int	ms_pwd(void);
int	ms_echo(char **arg);
void	ft_free_tab(char **tabs);
int	ms_env(t_cmd *cmd);
char	*ms_get_env(char **env, char *arg);
int ms_cd(char *argv, t_cmd *cmd);
void	ms_set_env(char **env, char *value, t_cmd *cmd);
int ms_unset(t_cmd *cmd, char **argv);
void	ms_init_env(char **env, t_cmd *cmd);

#endif