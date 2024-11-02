/**
 * @file Mesh.cpp
 * @brief Implements the Mesh class for managing vertex data in OpenGL.
 */

#include "Mesh.h"

Mesh::Mesh(const float* vertices, const float* colors, size_t size) {
  // Create a new Vertex Array Object (VAO) and assign it a unique ID, which is stored in the referenced variable 
  glGenVertexArrays(1, &vertexArrayObjectId);

  // Bind the VAO, making it the active VAO
  glBindVertexArray(vertexArrayObjectId);

  // Create a new Vertex Buffer Object (VBO) and assign it a unique ID, which is stored in the referenced variable
  glGenBuffers(1, &vertexBufferObjectId);

  // Bind the VBO to the GL_ARRAY_BUFFER target, which is the buffer type used for vertex data
  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectId);

  // Upload the vertex data to the bound GL_ARRAY_BUFFER
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

  // Enable the vertex attribute at location 0 (typically the first attribute) in the shader. 
  glEnableVertexAttribArray(0);

  // Define how OpenGL should interpret the vertex data in the bound VBO for the specified attribute location
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  // Set up color buffer object mirroring position VBO above
  glGenBuffers(1, &colorBufferObjectId);
  glBindBuffer(GL_ARRAY_BUFFER, colorBufferObjectId);
  glBufferData(GL_ARRAY_BUFFER, size, colors, GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  vertexCount = size / sizeof(float) / 3;
}

Mesh::~Mesh() {
  glDeleteBuffers(1, &vertexBufferObjectId);
  glDeleteBuffers(1, &colorBufferObjectId);
  glDeleteVertexArrays(1, &vertexArrayObjectId);
}

void Mesh::bind() {
  glBindVertexArray(vertexArrayObjectId);
}

void Mesh::unbind() {
  // In OpenGL, the ID 0 is a special reserved value, meaning "no object" or "unbound."
  glBindVertexArray(0);
}

void Mesh::draw() {
  bind();
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
  unbind();
}