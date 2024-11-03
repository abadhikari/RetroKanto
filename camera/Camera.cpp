/**
 * @file Camera.cpp
 * @brief Implements the Camera class, which handles the view and projection transformations in OpenGL.
 */

#include "Camera.h"

Camera::Camera(GLfloat fov, GLfloat aspectRatio, GLfloat nearClip, GLfloat farClip)
  : position(glm::vec3(2,2,10)),
    target(glm::vec3(0,0,0)),
    up(glm::vec3(0,1,0)),
    horizontalAngle(3.14f),
    verticalAngle(0.0f),
    initialFov(fov),
    cameraSpeed(3.0f),
    mouseSpeed(0.005f) {
  
  viewDirection = glm::vec3 (
      cos(verticalAngle) * sin(horizontalAngle),
      sin(verticalAngle),
      cos(verticalAngle) * cos(horizontalAngle)
  );

  sideVector = glm::vec3(
    sin(horizontalAngle - 3.14f/2.0f),
    0,
    cos(horizontalAngle - 3.14f/2.0f)
  );

  updateTarget();
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

void Camera::moveBackward(double deltaTime) {
  position -= viewDirection * cameraSpeed * static_cast<GLfloat>(deltaTime);
  updateTarget();
}

void Camera::moveForward(double deltaTime) {
  position += viewDirection * cameraSpeed * static_cast<GLfloat>(deltaTime);
  updateTarget();
}

void Camera::moveLeft(double deltaTime) {
  position -= sideVector * cameraSpeed * static_cast<GLfloat>(deltaTime);
  updateTarget();
}

void Camera::moveRight(double deltaTime) {
  position += sideVector * cameraSpeed * static_cast<GLfloat>(deltaTime);
  updateTarget();
}

void Camera::updateTarget() {
  target = position + viewDirection;
}