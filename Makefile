# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/08 19:16:05 by modysseu          #+#    #+#              #
#    Updated: 2022/03/11 16:00:52 by modysseu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

SRC			=	main.c\
				parser/creating_tokens/checking_the_token_type_error.c\
				parser/creating_tokens/creating_a_token_type.c\
				parser/creating_tokens/creating_tokens.c\
				parser/creating_tokens/file_type_assignment.c\
				parser/editing_tokens.c\
				parser/if_env.c\
				parser/init_env.c\
				parser/error_cmd.c\
				parser/parser_utilities.c\
				parser/parsing_main.c\

HEADER		=	minishell.h

CC			=	cc

FLAGS		= -Wall -Werror -Wextra -I$(HEADER)

RM			=	rm -f

OBJ			= $(SRC:.c=.o)

all : libft $(NAME)

$(NAME) : $(OBJ) 
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline -L./libft -lft
#-L/Users/$(USER)/.brew/Cellar/readline/8.1.2

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