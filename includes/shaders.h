#pragma once
#include "glad/glad.h"

typedef struct {
	GLuint ID; 
}	t_shader;

void	shader(t_shader *shader, const char *vertex_file, const char *fragement_file);
void	activate_shader(t_shader *shader);
void	delete_shader(t_shader *shader);
