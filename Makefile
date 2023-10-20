NAME		=	ExpensiveEngine
CC			=	clang
CFLAGS	=	-m64 -lglfw -lm -I./includes/
SOURCES_BUFFERS		=	./src/buffers/VAO.c	\
										./src/buffers/VBO.c
SOURCES_FUNCTIONS	=	./src/functions/get_file_contents.c
SOURCES_SHADERS		=	./src/shaders/shader.c

all: $(NAME)

$(NAME):
	$(CC) src/main.c src/libs/glad.c -o $(NAME) $(SOURCES_SHADERS) $(SOURCES_FUNCTIONS) $(SOURCES_BUFFERS) $(CFLAGS)

fclean:
	rm -rf $(NAME)

re: fclean all
