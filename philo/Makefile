NAME = philo

SRC = philo.c init.c ph.c utils.c utils1.c safe.c safe1.c 

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) -pthread $^ -o $@

%.o: %.c
	cc $(CFLAGS) -pthread -c $< -o $@

re: fclean all clean
	clear

clean:
	rm -fr $(OBJ)

fclean: clean
	rm -rf $(NAME)
