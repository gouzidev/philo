NAME = philo

SRC = philo.c

OBJ = $(SRC:.c=.o)

all: $(NAME) clean


$(NAME): $(OBJ)
	cc $(CFLAGS) $^ -o $@

.o.c:
	cc $(CFLAGS) $< -o $@

re: fclean all

clean:
	rm -fr $(OBJ)

fclean: clean all
	clear
