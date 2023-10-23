#include "camera.h"
#include <GLFW/glfw3.h>
#include <cglm/cam.h>
#include <cglm/mat4.h>
#include <cglm/types.h>
#include <cglm/util.h>
#include <cglm/vec3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
}

void	inputs_camera(t_camera *camera, GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		vec3 result;
		glm_vec3_scale_as(camera->orientation, camera->speed, result);
		glm_vec3_add(camera->position, result, camera->position);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		vec3 result;
		vec3 result_cross;
		vec3 result_norm;
		glm_vec3_cross(camera->orientation, camera->up, result_cross);
		glm_vec3_normalize_to(result_cross, result_norm);
		glm_vec3_scale_as(result_norm, -camera->speed, result);
		glm_vec3_add(camera->position, result, camera->position);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		vec3 result;
		glm_vec3_scale_as(camera->orientation, -camera->speed, result);
		glm_vec3_add(camera->position, result, camera->position);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		vec3 result;
		vec3 result_cross;
		vec3 result_norm;
		glm_vec3_cross(camera->orientation, camera->up, result_cross);
		glm_vec3_normalize_to(result_cross, result_norm);
		glm_vec3_scale_as(result_norm, camera->speed, result);
		glm_vec3_add(camera->position, result, camera->position);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		vec3 result;
		
		glm_vec3_scale_as(camera->up, camera->speed, result);
		glm_vec3_add(camera->position, result, camera->position);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		vec3 result;
		
		glm_vec3_scale_as(camera->up, -camera->speed, result);
		glm_vec3_add(camera->position, result, camera->position);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera->speed = 0.1f;
	} else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		camera->speed = 0.01f;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (camera->first_click) {
			glfwSetCursorPos(window, ((float)camera->width / 2), ((float)camera->height / 2));
			camera->first_click = 0;
		}

		double	mouseX;
		double	mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float	rotx = camera->sensitivity * (mouseY - ((float)camera->height / 2)) / camera->height;
		float	roty = camera->sensitivity * (mouseX - ((float)camera->width / 2)) / camera->width;

		vec3	new_orientation;
		vec3	result_cross;
		vec3	result_norm;
		vec3	result_neg;

		glm_vec3_copy(camera->orientation, new_orientation);
		glm_vec3_cross(camera->orientation, camera->up, result_cross);
		glm_vec3_normalize_to(result_cross, result_norm);
		glm_vec3_rotate(new_orientation, glm_rad(-rotx), result_norm);

//		glm_vec3_negate_to(camera->up, result_neg);
	//	if (!((glm_vec3_angle(new_orientation, camera->up) <= glm_rad(5.0f)) || (glm_vec3_angle(new_orientation, result_neg) <= glm_rad(5.0f)))) {
		if (fabsf(glm_vec3_angle(new_orientation, camera->up) - glm_rad(90.0f)) <= glm_rad(85.0f)) {
			glm_vec3_copy(new_orientation, camera->orientation);
		}

		glm_vec3_rotate(camera->orientation, glm_rad(-roty), camera->up);
		glfwSetCursorPos(window, ((float)camera->width / 2), ((float)camera->height / 2));

	} else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		camera->first_click = 1;
	}
}
