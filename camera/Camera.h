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

  /**
   * @brief Moves the camera backward along its view direction.
   * @param deltaTime The time elapsed since the last frame, used to calculate consistent movement speed.
   */
  void moveBackward(double deltaTime);

  /**
   * @brief Moves the camera forward along its view direction.
   * @param deltaTime The time elapsed since the last frame, used to calculate consistent movement speed.
   */
  void moveForward(double deltaTime);

  /**
   * @brief Moves the camera to the left, perpendicular to its view direction.
   * @param deltaTime The time elapsed since the last frame, used to calculate consistent movement speed.
   */
  void moveLeft(double deltaTime);

  /**
   * @brief Moves the camera to the right, perpendicular to its view direction.
   * @param deltaTime The time elapsed since the last frame, used to calculate consistent movement speed.
   */
  void moveRight(double deltaTime);

  /**
   * @brief Updates the camera's orientation based on mouse movement.
   *
   * This function adjusts the camera's horizontal and vertical angles according to the mouse's position
   * on the screen, which affects the camera's view direction and creates a first-person camera effect.
   *
   * @param deltaTime Time elapsed since the last frame, used to scale the orientation change for smooth movement.
   * @param xPosition Current x-coordinate of the mouse cursor within the window.
   * @param yPosition Current y-coordinate of the mouse cursor within the window.
   * @param screenWidth Width of the window, used to calculate the mouse offset.
   * @param screenHeight Height of the window, used to calculate the mouse offset.
   */
  void updateOrientation(double deltaTime, double xPosition, double yPosition, int screenWidth, int screenHeight);

private:
  /**
   * @brief Updates the target point the camera is looking at based on its position and view direction.
   *
   * Ensures the target point remains aligned with the camera's orientation.
   */
  void updateTarget();

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

  /**
   * The horizontal angle of the camera's orientation, measured in radians.
   */
  GLfloat horizontalAngle;

  /**
   * The vertical angle of the camera's orientation, measured in radians.
   */
  GLfloat verticalAngle;

  /**
   * The initial field of view (FOV) of the camera in degrees.
   */
  GLfloat initialFov;

  /**
   * The speed at which the camera moves through the world.
   */
  GLfloat cameraSpeed;

  /**
   * The speed at which the camera responds to mouse movements.
   */
  GLfloat mouseSpeed;

  /**
   * The direction the camera is currently facing.
   */
  glm::vec3 viewDirection;

  /**
   * The vector pointing to the right of the camera, perpendicular to the view direction.
   */
  glm::vec3 sideVector;
};

#endif