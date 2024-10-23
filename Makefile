NAME= minishell

OBJ_DIR= obj
SRC_DIR= src
INC_DIR= inc
INC= -I./inc

CC= cc
CFLAGS= -g -Wall -Werror -Wextra
RL_FLAGS = -lreadline -lncurses -ltermcap
FLAGS= $(CFLAGS) $(INC)
VAL= --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes -s

SRC_FILES= open_tty.c

SRC= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(RL_FLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

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

