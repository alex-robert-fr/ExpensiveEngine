#include "VAO.h"

void vao(t_vao *VAO) {
	glGenVertexArrays(1, &VAO->ID);
}

void	link_attrib(t_vao *VAO, t_vbo *VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset) {
	bind_vao(VAO);
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
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
