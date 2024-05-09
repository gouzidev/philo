NAME = philo

SRC = philo.c init.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra

# THREADFLAG = -fsanitize=thread

all: $(NAME)


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