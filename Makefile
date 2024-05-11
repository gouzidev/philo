NAME = philo

SRC = philo.c init.c utils.c utils1.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g

THREADFLAG = -fsanitize=thread

all: $(NAME) clean
	clear


$(NAME): $(OBJ)
	cc $(CFLAGS) $(THREADFLAG) $^ -o $@

%o: %c
	cc $(CFLAGS) $(THREADFLAG) $< -o $@

re: fclean all clean
	clear

clean:
	rm -fr $(OBJ)

fclean: clean
	rm -rf $(NAME)