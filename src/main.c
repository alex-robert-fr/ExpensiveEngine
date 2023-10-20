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
		-0.5f, 	0.0f,  0.5f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
		-0.5f, 	0.0f, -0.5f,     0.0f, 1.0f, 0.0f,	5.0f, 1.0f, // Upper left corner
		 0.5f,  0.0f, -0.5f,     0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // Upper right corner
		 0.5f,  0.0f,  0.5f,     1.0f, 1.0f, 1.0f,	5.0f, 0.0f,  // Lower right corner
		 0.0f,  0.8f,  0.0f,     1.0f, 1.0f, 1.0f,	2.5f, 5.0f  // Lower right corner
	};

	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4,
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

	link_attrib(VAO1, VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	link_attrib(VAO1, VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	link_attrib(VAO1, VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	unbind_vao(VAO1);
	unbind_vbo(VBO1);
	unbind_ebo(EBO1);


	GLuint	uniID = glGetUniformLocation(shader_struct->ID, "scale");
	
	t_texture	*nyanCat = calloc(sizeof(t_texture), 1);
	texture(nyanCat, "./textures/nyan.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	tex_unit(shader_struct, "tex0", 0);

	float		rotation = 0.0f;
	double	prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	// Boucle de rendu
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		activate_shader(shader_struct);

		double	crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60) {
			rotation += 0.5f;
			prevTime = crntTime;
		}

		mat4	model = GLM_MAT4_IDENTITY_INIT;
		mat4	view = GLM_MAT4_IDENTITY_INIT;
		mat4	proj = GLM_MAT4_IDENTITY_INIT;

		vec3	vec_rotation = {0.0f, 1.0f, 0.0f};
		glm_rotate(model, glm_rad(rotation), vec_rotation);
		vec3	vec_translate = {0.0f, -0.5f, -2.0f};
		glm_translate(view, vec_translate);
		glm_perspective(glm_rad(45.0f), (float)width/(float)height, 0.1f, 100.0f, proj);

		int	modelLoc = glGetUniformLocation(shader_struct->ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const GLfloat*)model);
		int	viewLoc = glGetUniformLocation(shader_struct->ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const GLfloat*)view);
		int	projLoc = glGetUniformLocation(shader_struct->ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const GLfloat*)proj);

		glUniform1f(uniID, 0.0f); // size
		bind_texture(nyanCat);
		bind_vao(VAO1);
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
