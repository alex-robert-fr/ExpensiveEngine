NAME	=	ExpensiveEngine
CC		=	clang

all: $(NAME)

$(NAME):
	$(CC) main.c -o $(NAME)

fclean:
	rm -rf $(NAME)

re: fclean all
