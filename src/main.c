#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stb/stb_image.h>
#include "shaders.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

const char	*vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char	*fragementShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int	main(void) {
	// Initialisation GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Initialisation position vertices
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
	};

	GLuint indices[] = {
		0, 2, 1,
		0, 3, 2,
	};

	// Create window
	GLFWwindow	*window = glfwCreateWindow(800, 800, "ExpensiveEngine", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to create GLFW window.");
		glfwTerminate();
		return (-1);
	}

	// Ajoute window au context OpenGL
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	t_shader	*shader_struct = calloc(sizeof(t_shader), 1);
	shader(shader_struct, "./shaders/default.vert", "./shaders/default.frag");

	t_vao	*VAO1 = calloc(sizeof(t_vao), 1);
	vao(VAO1);
	bind_vao(VAO1);

	t_vbo	*VBO1 = calloc(sizeof(t_vbo), 1);
	vbo(VBO1, vertices, sizeof(vertices));

	t_ebo	*EBO1 = calloc(sizeof(t_ebo), 1);
	ebo(EBO1, indices, sizeof(indices));

	link_attrib(VAO1, VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	link_attrib(VAO1, VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	link_attrib(VAO1, VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	unbind_vao(VAO1);
	unbind_vbo(VBO1);
	unbind_ebo(EBO1);

	GLuint	uniID = glGetUniformLocation(shader_struct->ID, "scale");

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(1);
	unsigned char	*bytes = stbi_load("./textures/nyan.png", &widthImg, &heightImg, &numColCh, 0);

	GLuint	texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shader_struct->ID, "tex0");
	activate_shader(shader_struct);
	glUniform1i(tex0Uni, 0);

	// Boucle de rendu
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_struct->ID);
		glUniform1f(uniID, 0.5f);
		glBindTexture(GL_TEXTURE_2D, texture);
		bind_vao(VAO1);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	delete_vao(VAO1);
	delete_vbo(VBO1);
	delete_ebo(EBO1);
	glDeleteTextures(1, &texture);
	glDeleteProgram(shader_struct->ID);

	glfwDestroyWindow(window);
	glfwTerminate();

	return (0);
}
