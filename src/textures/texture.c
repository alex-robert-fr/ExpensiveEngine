#include <stb/stb_image.h>
#include "texture.h"

void	texture(t_texture *texture, const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	texture->type = texType;

	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(1);
	unsigned char	*bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &texture->ID);
	glActiveTexture(slot);
	glBindTexture(texType, texture->ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGB, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void	tex_unit(t_shader *shader, const char *uniform, GLuint unit) {
	GLuint texUni = glGetUniformLocation(shader->ID, uniform);
	activate_shader(shader);
	glUniform1i(texUni, 0);
}

void bind_texture(t_texture *texture) {
	glBindTexture(texture->type, texture->ID);
}

void unbind_texture(t_texture *texture) {
	glBindTexture(texture->type, 0);
}

void delete_texture(t_texture *texture) {
	glDeleteTextures(1, &texture->ID);
}
