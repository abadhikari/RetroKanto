/**
 * @file Renderer.h
 * @brief Declares the Renderer class, which manages rendering operations for OpenGL objects.
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>
#include "../camera/Camera.h"
#include "../mesh/Mesh.h"
#include "../shader/ShaderProgram.h"

/**
 * @class Renderer
 * @brief Handles rendering of meshes in OpenGL.
 *
 * The Renderer class applies transformations and shaders, providing a
 * way to render 3D objects with model, view, and projection matrices.
 */
class Renderer {
public:
  /**
   * @brief Constructs a Renderer object with the specified camera and shader program.
   * @param camera Pointer to a Camera object that provides view and projection matrices.
   * @param shaderProgram Pointer to a ShaderProgram object for handling shaders during rendering.
   */
  Renderer(Camera* camera, ShaderProgram* shaderProgram);

  /**
   * @brief Renders a given mesh with a specified model matrix.
   * @param mesh The mesh to render.
   * @param modelMatrix The model transformation matrix for the mesh.
   */
  void render(Mesh& mesh, const glm::mat4& modelMatrix);

private:
  /**
   * Pointer to the Camera object, used to retrieve view and projection matrices.
   */
  Camera* camera;

  /**
   * Pointer to the ShaderProgram object, which manages shader compilation, linking, and usage.
   */
  ShaderProgram* shaderProgram;
};

#endif