#include "VAO.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "shaders.h"

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
	GLfloat vertices[] = {
   	-0.5f, -0.5f * sqrtf(3) / 3, 0.0f,
     0.5f, -0.5f * sqrtf(3) / 3, 0.0f,
     0.0f,  0.5f * sqrtf(3) * 2 / 3, 0.0f,
		 -0.5f / 2, 0.5f * sqrtf(3) / 6, 0.0f,
		 0.5 / 2, 0.5f * sqrtf(3) / 6, 0.0f,
		 0.0f, -0.5f * sqrtf(3) / 3, 0.0f
	};

	GLuint indices[] = {
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};

	// Create window
	GLFWwindow	*window = glfwCreateWindow(800, 600, "ExpensiveEngine", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to create GLFW window.");
		glfwTerminate();
		return (-1);
	}

	// Ajoute window au context OpenGL
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 600);

	t_shader	*shader_struct = calloc(sizeof(t_shader), 1);
	shader(shader_struct, "./shaders/default.vert", "./shaders/default.frag");

	t_vao	*VAO1 = calloc(sizeof(t_vao), 1);

	GLuint VBO, EBO;

	vao(VAO1);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	bind_vao(VAO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unbind_vao(VAO1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	// Boucle de rendu
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_struct->ID);
		bind_vao(VAO1);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	delete_vao(VAO1);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader_struct->ID);

	glfwDestroyWindow(window);
	glfwTerminate();

	return (0);
}
