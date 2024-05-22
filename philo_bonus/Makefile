NAME = philo_bonus

SRC = philo.c init.c ph.c utils.c utils1.c safe.c safe1.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -pthread 

#  THREADFLAG = -fsanitize=thread

all: $(NAME) clean


$(NAME): $(OBJ)
	gcc $(THREADFLAG) $(CFLAGS) $^ -o $@

%.o: %.c
	gcc $(THREADFLAG) $(CFLAGS) -c $< -o $@

re: fclean all clean
	clear

clean:
	rm -fr $(OBJ)

fclean: clean
	rm -rf $(NAME)