#pragma once
#include <glad/glad.h>
#include "shaders.h"

typedef struct {
	GLuint	ID;
	GLenum	type;
} t_texture;

void	texture(t_texture *texture, const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
void	tex_unit(t_shader *shader,const char *uniform, GLuint unit);
void	bind_texture(t_texture *texture);
void	unbind_texture(t_texture *texture);
void	delete_texture(t_texture *texture);
