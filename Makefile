NAME = pipex
GCC = gcc
FLAGS = -Wall -Wextra -Werror
HEADER = include/pipex.h

SRC = src/pipex.c src/utils.c libft/libft_utils.c libft/split.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(GCC) $(FLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re