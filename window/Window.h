/**
 * @file Window.h
 * @brief Declares the Window class, which manages an OpenGL window.
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

/**
 * @class Window
 * @brief Manages the creation, updating, and destruction of an OpenGL window.
 *
 * The Window class provides methods to initialize an OpenGL context, manage window updates,
 * and handle user interactions.
 */
class Window {
public:
  /**
   * @brief Constructs a Window object with the given dimensions and title.
   * @param width Width of the window in pixels.
   * @param height Height of the window in pixels.
   * @param title Title of the window.
   */
  Window(int width, int height, const std::string& title);

  /**
   * @brief Destructor that cleans up the window.
   */
  ~Window();

  /**
   * @brief Initializes the window and sets up the OpenGL context.
   * @return true if the window is successfully initialized, false otherwise.
   *
   * This method creates the window with the specified settings,
   * and makes the OpenGL context current.
   */
  bool init();

  /**
   * @brief Checks if the window should close.
   * @return true if the window should close (user has requested a close), false otherwise.
   */
  bool shouldClose();

  /**
   * @brief Swaps the front and back buffers, displaying the most recent frame.
   */
  void swapBuffers();

  /**
   * @brief Polls for and processes any pending events, such as keyboard and mouse input.
   */
  void pollEvents();

private:
  /** 
   * Width of the window in pixels.
   */
  int width;

  /** 
   * Height of the window in pixels.
   */
  int height;

  /** 
   * Title of the window.
   */
  std::string title;

  /**
   * Pointer to the GLFW window context.
   */
  GLFWwindow* window;
};

#endif