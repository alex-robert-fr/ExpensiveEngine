NAME		=	ExpensiveEngine
CC			=	clang
CFLAGS	=	-m64 -I./includes/

all: $(NAME)

$(NAME):
	$(CC) src/main.c src/libs/glad.c -o $(NAME) $(CFLAGS)

fclean:
	rm -rf $(NAME)

re: fclean all
