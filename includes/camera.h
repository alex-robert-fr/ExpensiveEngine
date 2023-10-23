#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/types.h>
#include "shaders.h"

typedef struct {
	vec3	position;
	vec3	orientation;
	vec3	up;
	int		width;
	int		height;
	float	speed;
	float	sensitivity;
	int		first_click;
} t_camera;

void	camera(t_camera *camera, int width, int height, vec3 position);
void	matrix_camera(t_camera *camera, float FOVdeg, float nearPlane, float farPlane, t_shader *shader, const char *uniform);
void	inputs_camera(t_camera *camera, GLFWwindow *window);
