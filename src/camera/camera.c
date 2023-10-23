#include "camera.h"
#include <cglm/cam.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <cglm/util.h>
#include <cglm/vec3.h>
#include <stdio.h>

void	camera(t_camera *camera, int width, int height, vec3 position) {
	camera->width = width;
	camera->height = height;
	glm_vec3_copy(position, camera->position);
}

void	matrix_camera(t_camera *camera, float FOVdeg, float nearPlane, float farPlane, t_shader *shader, const char *uniform) {
	mat4	view;
	mat4	projection;
	glm_mat4_copy(GLM_MAT4_IDENTITY, view);
	glm_mat4_copy(GLM_MAT4_IDENTITY, projection);
	vec3	center;
	mat4	value;

	glm_vec3_add(camera->position, camera->orientation, center);
	glm_lookat(camera->position, center, camera->up, view);
	glm_perspective(glm_rad(FOVdeg), (float)camera->width/(float)camera->height, nearPlane, farPlane, projection);

	glm_mat4_mul(projection, view, value);

	glUniformMatrix4fv(glGetUniformLocation(shader->ID, uniform), 1, GL_FALSE, (const GLfloat*)value);
	GLenum error = glGetError();
if (error != GL_NO_ERROR) {
    fprintf(stderr, "OpenGL error: %d\n", error);
    // Handle error...
}
}
