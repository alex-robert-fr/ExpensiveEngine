#include "functions.h"
#include "globals.h"
#include "shaders.h"
#include <stdio.h>
#include <stdlib.h>

void	shader(t_shader *shader, const char *vertex_file, const char *fragement_file) {
	const char	*vertex_source = get_file_contents(vertex_file);
	const char	*fragement_source = get_file_contents(fragement_file);

	// Cree le vertex shader
	GLuint	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_source, NULL);
	glCompileShader(vertexShader);
	shader_compile_errors(vertexShader, VERTEX, "VERTEX");

	// Cree le fragement shader
	GLuint	fragementShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragementShader, 1, &fragement_source, NULL);
	glCompileShader(fragementShader);
	shader_compile_errors(fragementShader, FRAGMEMENT, "FRAGMEMENT");

	// "Assemble" les differents shader ensemble
	shader->ID = glCreateProgram();
	glAttachShader(shader->ID, vertexShader);
	glAttachShader(shader->ID, fragementShader);
	glLinkProgram(shader->ID);
	shader_compile_errors(shader->ID, PROGRAM, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragementShader);
}

void	activate_shader(t_shader *shader) {
	glUseProgram(shader->ID);
}

void	delete_shader(t_shader *shader) {
	glDeleteProgram(shader->ID);
}

void	shader_compile_errors(unsigned int shader, int num_type, const char *type) {
	GLint	hasCompiled;
	char	infoLog[1024];

	
	if (num_type != PROGRAM) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			fprintf(stderr, "SHADER_COMPILATION_ERROR for: %s\n %s\n", type, infoLog);
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			fprintf(stderr, "SHADER_LINKING_ERROR for: %s\n %s\n", type, infoLog);
		}
	}
}
