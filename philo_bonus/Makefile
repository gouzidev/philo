NAME = philo_bonus

SRC = main_bonus.c philo_bonus.c init_bonus.c utils_bonus.c utils1_bonus.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -pthread 

all: $(NAME) clean
	clear

$(NAME): $(OBJ)
	cc $(CFLAGS) $^ -o $@

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

re: fclean all clean
	clear

clean:
	rm -fr $(OBJ)

fclean: clean
	rm -rf $(NAME)