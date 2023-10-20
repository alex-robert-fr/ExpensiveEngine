#pragma once
#include "VBO.h"
#include "glad/glad.h"

typedef struct {
	GLuint	ID;
} t_vao;

void	vao(t_vao *VAO);
void	link_vbo(t_vao *VAO, t_vbo *VBO, GLuint layout);
void	bind_vao(t_vao *VAO);
void	unbind_vao(t_vao *VAO);
void	delete_vao(t_vao *VAO);
