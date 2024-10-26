# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 22:38:45 by lede-gui          #+#    #+#              #
#    Updated: 2024/10/26 18:05:35 by lede-gui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

OBJ_DIR= obj
SRC_DIR= src
INC_DIR= inc
INC= -I./inc

CC= cc
CFLAGS= -g -Wall -Werror -Wextra
RL_FLAGS = -lreadline -lncurses -ltermcap
FLAGS= $(CFLAGS) $(INC)
VAL= --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes --suppressions=.readline.supp

## FDS functions directory and build
FDS_DIR= src/fd
FDS_FILES= put_fd.c
SRC_FDS= $(addprefix $(FDS_DIR)/, $(FDS_FILES))

## Memory functions directory and build
MEM_DIR= src/mem_alloc
MEM_FILES= alloc.c
SRC_MEM= $(addprefix $(MEM_DIR)/, $(MEM_FILES))

## Strings functions directory and build
STR_DIR= src/str_utils
STR_FILES= str_basic.c dup_split.c
SRC_STR= $(addprefix $(STR_DIR)/, $(STR_FILES))

## Lexer functions directory and build
LEX_DIR= src/lexer
LEX_FILES= lexer.c
SRC_LEX= $(addprefix $(LEX_DIR)/, $(LEX_FILES))

SRC_FILES= main.c

SRC= $(SRC_FILES) $(SRC_MEM) $(SRC_STR) $(SRC_LEX)

OBJ= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(RL_FLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(FDS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(STR_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MEM_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LEX_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

san: CFLAGS += -fsanitize=address
san: re

val: $(NAME)
	valgrind $(VAL) ./$(NAME)

valfd: VAL += --track-fds=all
valfd: val

.PHONY: all clean fclean re val valfd

