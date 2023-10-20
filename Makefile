NAME		=	ExpensiveEngine
CC			=	clang
CFLAGS	=	-m64 -lglfw -lm -I./includes/
LIB_STB						=	./src/libs/stb.c
SOURCES_BUFFERS		=	./src/buffers/VAO.c	\
										./src/buffers/VBO.c	\
										./src/buffers/EBO.c
SOURCES_FUNCTIONS	=	./src/functions/get_file_contents.c
SOURCES_SHADERS		=	./src/shaders/shader.c
SOURCES_TEXTURES	=	./src/textures/texture.c

all: $(NAME)

$(NAME):
	$(CC) src/main.c src/libs/glad.c -o $(NAME) $(SOURCES_SHADERS) $(SOURCES_FUNCTIONS) $(SOURCES_BUFFERS) $(SOURCES_TEXTURES) $(LIB_STB) $(CFLAGS)

fclean:
	rm -rf $(NAME)

re: fclean all
