/**
 * @file Camera.h
 * @brief Declares the Camera class, which handles the view and projection transformations in OpenGL.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @class Camera
 * @brief Manages the view and projection matrices for 3D rendering in OpenGL.
 *
 * The Camera class provides methods to retrieve the projection and view matrices
 * based on the camera's position, orientation, and field of view (FOV).
 */
class Camera {
public:
  /**
   * @brief Constructs a Camera object with the given field of view, aspect ratio, and clipping planes.
   * @param fov Field of view in degrees.
   * @param aspectRatio Aspect ratio of the window (width/height).
   * @param nearClip Distance to the near clipping plane.
   * @param farClip Distance to the far clipping plane.
   */
  Camera(GLfloat fov, GLfloat aspectRatio, GLfloat nearClip, GLfloat farClip);

  /**
   * @brief Retrieves the projection matrix of the camera.
   * @return The projection matrix (perspective transformation).
   *
   * This matrix transforms world coordinates into clip space for 3D perspective projection.
   */
  glm::mat4 getProjectionMatrix() const;

  /**
   * @brief Retrieves the view matrix of the camera.
   * @return The view matrix, which represents the camera's position and orientation in world space.
   *
   * The view matrix is used to transform objects in the scene relative to the camera's position and direction.
   */
  glm::mat4 getViewMatrix() const;

private:
  /**
   * Represents the perspective transformation.
   */
  glm::mat4 projectionMatrix;

  /**
   * The position of the camera in world space.
   */
  glm::vec3 position;

  /**
   * The target point the camera is looking at.
   */
  glm::vec3 target;

  /**
   * The up direction of the camera, defining its orientation.
   * (0,1,0) is normal, while (0,-1,0) is to look upside-down.
   */
  glm::vec3 up;
};

#endif