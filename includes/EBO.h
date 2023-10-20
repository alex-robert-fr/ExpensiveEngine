#pragma once

#include "glad/glad.h"

typedef struct {
	GLuint	ID;
}	t_ebo;

void	ebo(t_ebo *EBO, GLuint *indices, GLsizeiptr size);
void	bind_ebo(t_ebo *EBO);
void	unbind_ebo(t_ebo *EBO);
void	delete_ebo(t_ebo *EBO);
