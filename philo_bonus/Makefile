NAME = philo_bonus

SRC = main_bonus.c philo_bonus.c init_bonus.c utils_bonus.c utils1_bonus.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) -pthread $^ -o $@

%.o: %.c
	cc $(CFLAGS) -pthread -c $< -o $@

re: fclean all

clean:
	rm -fr $(OBJ)

fclean: clean
	rm -rf $(NAME)