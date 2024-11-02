/**
 * @file Renderer.cpp
 * @brief Implements the Renderer class, which manages rendering operations for OpenGL objects.
 */

#include "Renderer.h"

Renderer::Renderer(Camera* camera, ShaderProgram* shaderProgram)
  : camera(camera), shaderProgram(shaderProgram) {}

void Renderer::render(Mesh& mesh, const glm::mat4& modelMatrix) {
  glm::mat4 projectionMatrix = camera -> getProjectionMatrix();
  glm::mat4 viewMatrix = camera -> getViewMatrix();

  // Calculate the Model-View-Projection (MVP) matrix
  glm::mat4 modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;

  // Apply the shaders when rendering objects to the screen
  shaderProgram -> use();

  // Set the MVP uniform in the shader
  shaderProgram -> setUniform("modelViewProjection", modelViewProjectionMatrix);

  // Draw the mesh with the active shader
  mesh.draw();
}