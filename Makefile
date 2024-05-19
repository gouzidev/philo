NAME = philo

SRC = philo.c init.c ph.c utils.c utils1.c safe.c safe1.c 

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=thread

# THREADFLAG = -fsanitize=thread

all: $(NAME) clean


$(NAME): $(OBJ)
	gcc $(CFLAGS) $(THREADFLAG) $^ -o $@

%o: %c
	gcc $(CFLAGS) $(THREADFLAG) $< -o $@

re: fclean all clean
	clear

clean:
	rm -fr $(OBJ)

fclean: clean
	rm -rf $(NAME)