## Name of Project

NAME = corrector_lem_in

## Color for compilating (pink)

COLOR = \0033[1;35m

## List of Directories

INC_DIR = include
OBJ_DIR = obj
SRC_DIR = src
LIB_DIR = libft

## Compilating Utilities

FLAGS = -g -Wall -Wextra -Werror
INC = $(INC_DIR:%=-I ./%)
LIB = -fsanitize=address -L $(LIB_DIR) -lft
CC = clang $(FLAGS) $(INC)

## List of Functions

SRC_FT =	corrector 				\
					parser_corrector	\

## List of Utilities

OBJ = $(SRC_FT:%=$(OBJ_DIR)/%.o)
SRC = $(SRC_FT:%=$(SRC_DIR)/%.c)

## Rules of Makefile

all: $(NAME)
	@echo "$(COLOR)$(NAME)\t\t\0033[1;30m[All OK]\0033[0m"

$(OBJ_DIR):
	@mkdir -p $@
	@echo "$(COLOR)Creating    : \0033[0;32m$@\0033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/corrector.h
	@$(CC) -c $< -o $@
	@echo "$(COLOR)Compilating : \0033[0;32m$(@:$(OBJ_DIR)/%=%)\0033[0m"

$(NAME): $(OBJ_DIR) $(SRC) $(INC_DIR)/corrector.h
	@$(MAKE) $(OBJ)
	@echo "$(COLOR)Objects\t\t\0033[0;32m[Created]\0033[0m"
	@make -j -s -C $(LIB_DIR)
	@$(CC) $(LIB) $(OBJ) $(MLX) -o $@
	@echo "$(COLOR)$(NAME)\t\t\0033[0;32m[Created]\0033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR)
	@echo "$(COLOR)Objects\t\t\0033[0;31m[Deleted]\0033[0m"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_DIR)
	@echo "$(COLOR)$(NAME)\t\t\0033[0;31m[Deleted]\0033[0m"

re: fclean all

norme:
	@norminette $(SRC) $(INC_DIR)/
	@make norme -C $(LIB_DIR)

.PHONY: all clean fclean re norme
