NAME = book_search
CC = cc
CFLAG = -Wall -Wextra -Werror -g
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

SRC =	library.c

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(NAME): $(SRC) $(LIBFT)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAG) $(SRC) $(LIBFT) -Iinclude -o $(NAME)

val: $(NAME)
	@echo "Using Valgrind..."
	@$(VALGRIND) ./$(NAME) $(ARGS)

clean:
	@echo "Removing object files..."
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet

fclean: clean
	@echo "Removing library and executables..."
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet

re: fclean all

.PHONY: all val clean fclean re
.SILENT:
