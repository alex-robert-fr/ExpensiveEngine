#include "VAO.h"

void vao(t_vao *VAO) {
	glGenVertexArrays(1, &VAO->ID);
}

void	link_vbo(t_vao *VAO, t_vbo *VBO, GLuint layout) {
	bind_vao(VAO);
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	unbind_vao(VAO);
}

void	bind_vao(t_vao *VAO) {
	glBindVertexArray(VAO->ID);
}

void	unbind_vao(t_vao *VAO) {
	glBindVertexArray(0);
}

void	delete_vao(t_vao *VAO) {
	glDeleteVertexArrays(1, &VAO->ID);
}
