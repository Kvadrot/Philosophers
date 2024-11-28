# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra #-Werror
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# Project name (output executable)
NAME = philo

# Source files and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default target (all)
all: $(NAME)

# Rule to build the target program
$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

# Rule to compile .c files to .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up object files (but keep the executable)
clean:
	rm -f $(OBJ_DIR)/*.o

# Clean up all files including the executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything (clean + all)
re: fclean all

.PHONY: all clean fclean re
