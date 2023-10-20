#pragma once

#include "glad/glad.h"

typedef struct {
	GLuint	ID;
}	t_vbo;

void	vbo(t_vbo *VBO, GLfloat *vertices, GLsizeiptr size);
void	bind_vbo(t_vbo *VBO);
void	unbind_vbo(t_vbo *VBO);
void	delete_vbo(t_vbo *VBO);
