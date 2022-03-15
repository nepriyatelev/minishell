# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: medeana <medeana@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 19:16:05 by modysseu          #+#    #+#              #
#    Updated: 2022/03/15 18:07:35 by medeana          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			=	main.c\
				parser/connection_of_parts/connection_of_parts_utilities.c\
				parser/connection_of_parts/connection_of_parts.c\
				parser/creating_tokens/checking_the_token_type_error.c\
				parser/creating_tokens/creating_a_token_type.c\
				parser/creating_tokens/creating_tokens.c\
				parser/creating_tokens/file_type_assignment.c\
				parser/editing_tokens/editing_tokens_utilities.c\
				parser/editing_tokens/editing_tokens.c\
				parser/editing_tokens/if_env_utilities.c\
				parser/editing_tokens/if_env.c\
				parser/editing_tokens/init_env.c\
				parser/error_cmd.c\
				parser/parser_utilities.c\
				parser/parsing_main.c\
				executor/exec.c\
				executor/export.c\
				executor/find_path.c\
				executor/ft_builtin.c\
				executor/heredoc.c\
				executor/init_export.c\
				executor/ms_cd.c\
				executor/ms_echo.c\
				executor/ms_env.c\
				executor/ms_exit.c\
				executor/ms_init_env.c\
				executor/ms_pwd.c\
				executor/ms_unset.c\
				executor/open_file.c\
				executor/signal.c\
				executor/sort.c\

HEADER		=	minishell.h

CC			=	cc

FLAGS		= -Wall -Werror -Wextra -I$(HEADER) -I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include

RM			=	rm -f

OBJ			= $(SRC:.c=.o)

all : libft $(NAME)
	stty -ctlecho
$(NAME) : $(OBJ) 
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib/ -lreadline -L./libft -lft

%.o: %.c $(HEADER) Makefile
	$(CC) $(FLAGS) -c $< -o $@

libft :
	make -C libft

clean :
	make -C libft clean
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)
	$(RM) libft/libft.a

re : fclean all

.PHONY: all clean fclean re libft