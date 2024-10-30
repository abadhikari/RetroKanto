#include <GLFW/glfw3.h>
#include <iostream>

int main() {
  if(!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWwindow* window = glfwCreateWindow(800, 600, "RetroKanto", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window); 

  // Set the clear color to sky blue
  glClearColor(0.5f, 0.8f, 1.0f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}