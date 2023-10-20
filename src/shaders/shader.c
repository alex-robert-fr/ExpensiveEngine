#include "functions.h"
#include "shaders.h"
#include <stdlib.h>

void	shader(t_shader *shader, const char *vertex_file, const char *fragement_file) {
	const char	*vertex_source = get_file_contents(vertex_file);
	const char	*fragement_source = get_file_contents(fragement_file);

	// Cree le vertex shader
	GLuint	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_source, NULL);
	glCompileShader(vertexShader);

	// Cree le fragement shader
	GLuint	fragementShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragementShader, 1, &fragement_source, NULL);
	glCompileShader(fragementShader);

	// "Assemble" les differents shader ensemble
	shader->ID = glCreateProgram();
	glAttachShader(shader->ID, vertexShader);
	glAttachShader(shader->ID, fragementShader);
	glLinkProgram(shader->ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragementShader);
}

void	activate_shader(t_shader *shader) {
	glUseProgram(shader->ID);
}

void	delete_shader(t_shader *shader) {
	glDeleteProgram(shader->ID);
}
