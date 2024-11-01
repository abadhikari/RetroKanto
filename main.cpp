#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader/ShaderProgram.h"
#include "window/Window.h"
#include "mesh/Mesh.h"

int main() {
  // Create the window
  Window window(800, 600, "RetroKanto");
  if (!window.init()) {
    return -1;
  }

  // Set up shaders
  ShaderProgram basicShaderProgram("shader/vertex_shader.glsl", "shader/fragment_shader.glsl");
  if (!basicShaderProgram.init()) {
    return -1;
  }

  // Triangle vertices to be rendered to screen
  float vertices[] = {
    0.0f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
  };

  Mesh triangle(vertices, sizeof(vertices));

  while (!window.shouldClose()) {
    // Clear the screen, preparing it for new frame rendering
    glClear(GL_COLOR_BUFFER_BIT);

    // Apply the shaders from basicShaderProgram when rendering objects to the screen
    basicShaderProgram.useProgram();

    // Render to the screen
    triangle.draw();

    // Swap the front and back buffers, displaying the newly rendered frame
    window.swapBuffers();

    // Process any pending events, such as keyboard and mouse input
    window.pollEvents();
  }

  return 0;
}