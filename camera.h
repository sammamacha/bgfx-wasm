#pragma once
#define GLM_FORCE_PURE
#include <glm/glm.hpp>

#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

extern struct Camera {
  glm::vec3 pos;
  glm::vec3 look;
  glm::vec3 up;

  float yaw, pitch, roll;
} camera;

void camera_init(Camera &cam);
void camera_update(Camera &cam);
