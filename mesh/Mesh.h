/**
 * @file Mesh.h
 * @brief Defines the Mesh class for managing vertex data in OpenGL.
 */

#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

/**
 * @class Mesh
 * @brief Represents a basic mesh object that encapsulates Vertex Array Object (VAO), Vertex Buffer Object (VBO), and Color Buffer Object (CBO).
 *
 * The Mesh class handles VAO, VBO, and CBO setup and binding.
 */
class Mesh {
public:
  /**
   * @brief Constructs a Mesh object with given vertices.
   * @param vertices Pointer to the vertex data array.
   * @param colors Pointer to the color data array.
   * @param size Size of the vertex (and color) data array in bytes.
   */
  Mesh(const float* vertices, const float* colors, size_t size);

  /**
   * @brief Destructor to clean up allocated OpenGL resources.
   */
  ~Mesh();

  /**
   * @brief Binds the VAO for the mesh.
   */
  void bind();

  /**
   * @brief Unbinds any VAO, restoring the previous state.
   */
  void unbind();

  /**
   * @brief Draws the mesh using stored VAO, VBO, and CBO configurations.
   */
  void draw();

private:
  /**
   * Vertex Array Object ID.
   *
   * A VAO stores the configuration of vertex attributes and references
   * to vertex buffer objects (VBOs), allowing OpenGL to remember how to
   * draw a set of vertices.
   */
  GLuint vertexArrayObjectId;

  /**
   * Vertex Buffer Object ID.
   *
   * Stores vertex position data on the GPU,
   * allowing for efficient rendering by minimizing data
   * transfer between the CPU and GPU.
   */
  GLuint vertexBufferObjectId;

  /**
   * Color Buffer Object ID.
   *
   * Stores the color data for each vertex on the GPU,
   * allowing for efficient rendering by minimizing data
   * transfer between the CPU and GPU.
   */
  GLuint colorBufferObjectId;

  /**
   * The number of vertices passed to the Mesh class.
   */
  int vertexCount;
};

#endif