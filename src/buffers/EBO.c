#include "EBO.h"

void	ebo(t_ebo *EBO, GLuint *indices, GLsizeiptr size) {
	glGenBuffers(1, &EBO->ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO->ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void	bind_ebo(t_ebo *EBO) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO->ID);
}

void	unbind_ebo(t_ebo *EBO) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void	delete_ebo(t_ebo *EBO) {
	glDeleteBuffers(1, &EBO->ID);
}
