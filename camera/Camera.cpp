/**
 * @file Camera.cpp
 * @brief Implements the Camera class, which handles the view and projection transformations in OpenGL.
 */

#include "Camera.h"

Camera::Camera(GLfloat fov, GLfloat aspectRatio, GLfloat nearClip, GLfloat farClip)
  : position(glm::vec3(4,3,3)),
    target(glm::vec3(0,0,0)),
    up(glm::vec3(0,1,0)) {
  projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}

glm::mat4 Camera::getProjectionMatrix() const {
  return projectionMatrix;
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(
    glm::vec3(position),
    glm::vec3(target),
    glm::vec3(up)
  );
}