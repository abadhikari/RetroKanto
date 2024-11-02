/**
 * @file Window.cpp
 * @brief Implements the Window class, which manages an OpenGL window.
 */

#include <string>
#include <iostream>
#include "Window.h"

Window::Window(int width, int height, const std::string& title)
  : width(width), height(height), title(title), window(nullptr) {}

bool Window::init() {
  if(!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return false;
  }

  // Set major and minor version of OpenGL. Version 4.1 is the last officially supported version of OpenGL on Mac
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

  // Set the OpenGL profile to core, indicating that only modern OpenGL functions will be available
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Enable forward compatibility since forward compatibility is required for OpenGL 3.0+ on Mac
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return false;
  }

  // Make the OpenGL context of the created window current. This context will be used for all OpenGL calls
  glfwMakeContextCurrent(window); 
  return true;
}

bool Window::shouldClose() {
  return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
  glfwSwapBuffers(window);
}

void Window::pollEvents() {
  glfwPollEvents();
}

int Window::getWidth() {
  return width;
}

int Window::getHeight() {
  return height;
}

Window::~Window() {
  if(window) {
    glfwDestroyWindow(window);
  }
  glfwTerminate();
}