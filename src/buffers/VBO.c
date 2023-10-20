#include "VBO.h"

void	vbo(t_vbo *VBO, GLfloat *vertices, GLsizeiptr size) {
	glGenBuffers(1, &VBO->ID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO->ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void	bind_vbo(t_vbo *VBO) {
	glBindBuffer(GL_ARRAY_BUFFER, VBO->ID);
}

void	unbind_vbo(t_vbo *VBO) {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	delete_vbo(t_vbo *VBO) {
	glDeleteBuffers(1, &VBO->ID);
}
