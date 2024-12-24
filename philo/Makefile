# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -g
HEADERS = -I./inc

# Directories for source files and object files
SRC_DIR = src/
OBJ_DIR = obj/

# Source files (you can update this list to reflect your project's structure)
SRC = main.c \
	common_fts/ft_atoi.c \
	initializer/init_enteties.c \
	routine_fts/routine.c \
	simulation_tracker/simulation_tracker.c \
	utils/debuger.c \
	utils/print_master.c \
	utils/time_master.c \
	utils/utils.c \
	validation_helpers.c

# Full path to source files
SRCS = $(addprefix ${SRC_DIR}, ${SRC})

# Object files
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Project name (output executable)
NAME = philo

# Default target (all)
all: $(NAME)

# Rule to compile .c files into .o files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< with $(CFLAGS) $(HEADERS)"
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

# Rule to build the target program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Clean up object files (but keep the executable)
clean:
	rm -f $(OBJ_DIR)/**/*.o

# Clean up all files including the executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything (clean + all)
re: fclean all

# Ensure that 'all', 'clean', 'fclean', 're' are not interpreted as file names
.PHONY: all clean fclean re
