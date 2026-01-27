# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blamotte <blamotte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 18:42:33 by blamotte          #+#    #+#              #
#    Updated: 2026/01/27 03:22:27 by blamotte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = push_swap
CHECKER     = checker
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
RM          = rm -f

COMMON_SRC  = parsing.c utils_lst.c \
              push.c swap.c rotate.c reverse_rotate.c \
              algo.c sort_up_to_five.c post_process.c \
              post_process_utils.c get_move.c ksorting.c move_back.c \
              free_things.c

PUSH_SWAP_SRC = main.c
CHECKER_SRC   = checker.c

COMMON_OBJ    = $(COMMON_SRC:.c=.o)
PUSH_SWAP_OBJ = $(PUSH_SWAP_SRC:.c=.o)
CHECKER_OBJ   = $(CHECKER_SRC:.c=.o)

LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

all: $(NAME) $(CHECKER)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(COMMON_OBJ) $(PUSH_SWAP_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(COMMON_OBJ) $(PUSH_SWAP_OBJ) $(LIBFT) -o $(NAME)

$(CHECKER): $(COMMON_OBJ) $(CHECKER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(COMMON_OBJ) $(CHECKER_OBJ) $(LIBFT) -o $(CHECKER)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	$(RM) $(COMMON_OBJ) $(PUSH_SWAP_OBJ) $(CHECKER_OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(CHECKER)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
