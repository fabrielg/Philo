# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 16:30:31 by gfrancoi          #+#    #+#              #
#    Updated: 2025/07/02 15:56:40 by gfrancoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				philo
CFLAGS =			-Wall -Wextra -Werror
LIBFT =				./libft/libft.a

SRCS = \
	main.c\
	dinner.c\
	getters.c\
	mutex_utils.c\
	parsing.c\
	philo_utils.c\
	print_state.c\
	setters.c\
	synchro.c\
	thread_utils.c

OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	
$(LIBFT):
	make -C ./libft/

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -c -o $@ $^

clean:
	make clean -C ./libft/
	rm -fr $(OBJ_DIR)

fclean: clean
	make fclean -C ./libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re bonus