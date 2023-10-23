#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cglm/cam.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <cglm/util.h>
#include <cglm/vec4.h>
#include <stdio.h>
#include <stdlib.h>
#include <stb/stb_image.h>
#include <cglm/cglm.h>
#include "shaders.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"
#include "camera.h"

void	set_transform(t_shader *shader, const char *uniform, mat4 transform) {
	GLuint transformLoc = glGetUniformLocation(shader->ID, uniform);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (const GLfloat*) transform);
}

int	main(void) {
	const unsigned int	width = 800;
	const unsigned int	height = 800;

	// Initialisation GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Initialisation position vertices
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f,  0.5f,  0.0f,     1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, 	0.5f,  0.0f,     0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.0f,     0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.0f,     1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -1.0f,     1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, 	0.5f, -1.0f,     0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -1.0f,     0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -1.0f,     1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3,
		1, 6, 2,
		1, 6, 5,
		0, 7, 3,
		0, 7, 4,
		4, 7, 6,
		4, 6, 5,
		7, 3, 2,
		7, 2, 6,
		0, 1, 4,
		1, 4, 5
	};

	// Create window
	GLFWwindow	*window = glfwCreateWindow(width, height, "ExpensiveEngine", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to create GLFW window.");
		glfwTerminate();
		return (-1);
	}

	// Ajoute window au context OpenGL
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	t_shader	*shader_struct = calloc(sizeof(t_shader), 1);
	shader(shader_struct, "./shaders/default.vert", "./shaders/default.frag");

	t_vao	*VAO1 = calloc(sizeof(t_vao), 1);
	vao(VAO1);
	bind_vao(VAO1);

	t_vbo	*VBO1 = calloc(sizeof(t_vbo), 1);
	vbo(VBO1, vertices, sizeof(vertices));

	t_ebo	*EBO1 = calloc(sizeof(t_ebo), 1);
	ebo(EBO1, indices, sizeof(indices));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	link_attrib(VAO1, VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	link_attrib(VAO1, VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	link_attrib(VAO1, VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	unbind_vao(VAO1);
	unbind_vbo(VBO1);
	unbind_ebo(EBO1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	t_texture	*nyanCat = calloc(sizeof(t_texture), 1);
	texture(nyanCat, "./textures/nyan.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	tex_unit(shader_struct, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	t_camera camera_struct = {
		.orientation = {0.0f, 0.0f, -1.0f},
		.up = {0.0f, 1.0f, 0.0f},
		.speed = 0.01f,
		.sensitivity = 100.0f,
		.first_click = 1,
	};
	vec3	camera_position = {0.0f, 0.0f, 2.0f};

	camera(&camera_struct, width, height, camera_position);

	// Boucle de rendu
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		activate_shader(shader_struct);

		inputs_camera(&camera_struct, window);
		matrix_camera(&camera_struct, 45.0f, 0.1f, 100.0f, shader_struct, "camMatrix");

		bind_texture(nyanCat);
		bind_vao(VAO1);
		mat4 transform1;
		glm_mat4_identity(transform1);
		glm_translate(transform1, (vec3){0.0f, 0.0f, 0.0f});
		set_transform(shader_struct, "transform", transform1);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		mat4 transform2;
		glm_mat4_identity(transform2);
		glm_translate(transform2, (vec3){1.5f, 0.0f, 0.0f});
		set_transform(shader_struct, "transform", transform2);
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	delete_vao(VAO1);
	delete_vbo(VBO1);
	delete_ebo(EBO1);
	delete_texture(nyanCat);
	delete_shader(shader_struct);

	glfwDestroyWindow(window);
	glfwTerminate();

	return (0);
}
