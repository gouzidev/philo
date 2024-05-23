NAME = philo_bonus

SRC = philo.c init.c utils.c utils1.c safe.c safe1.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -pthread 

all: $(NAME) clean
	clear

$(NAME): $(OBJ)
	cc $(CFLAGS) -fsanitize=thread $^ -o $@

%.o: %.c
	cc $(CFLAGS) -fsanitize=thread  -c $< -o $@

re: fclean all clean
	clear

clean:
	rm -fr $(OBJ)

fclean: clean
	rm -rf $(NAME)