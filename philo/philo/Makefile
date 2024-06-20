# **************************************************************************** #
#                                   Color                                      #
# **************************************************************************** #

GREEN			= \033[0;32m
RED				= \033[0;31m
YELLOW			= \033[0;33m
CYAN			= \033[1;36m
MAGENTA			= \033[0;35m
ORANGE			= \033[38;5;216m
NC				= \033[0m

# **************************************************************************** #
#                                   Flag                                       #
# **************************************************************************** #

CC				= cc
CFLAGS			= -Wall -Werror -Wextra -g3
RM				= rm -rf

# **************************************************************************** #
#                                   Project                                    #
# **************************************************************************** #

NAME			= philo
HEADER_DIR		= ./
OBJ_DIR			= .objects/
SRC_DIR			= ./src/

SRC				= ./src/main.c \
				  ./src/init.c \
				  ./src/monitors.c \
				  ./src/routine.c \
				  ./src/threads.c \
				  ./src/utils.c \
				  ./src/parsing.c \


OBJS			= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# **************************************************************************** #
#                                   Rules                                      #
# **************************************************************************** #

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@
	@echo "$(CYAN)Compiled $<$(NC)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I $(HEADER_DIR) $(OBJS) -o $@ && \
	echo "$(MAGENTA)$@ $(GREEN)Compiled successfully$(NC)" || \
	echo "$(RED)Failed to compile $(CYAN)$@$(NC)"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)clean .o$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)clean binary$(NC)"

re: fclean all

run: $(NAME)
	@./$(NAME) 10 1200 200 200 15

helgrind: $(NAME) 
	@valgrind --tool=helgrind -s --history-level=approx ./$(NAME)  5 100 200 200

valgrind: $(NAME) 
	@valgrind ./$(NAME)  4 800 200 200 2

drd: $(NAME) 
	@valgrind --tool=drd ./$(NAME)  200 1200 200 200 15

.PHONY: all clean fclean re run helgrind valgrind drd