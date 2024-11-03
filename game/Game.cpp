/**
 * @file Game.cpp
 * @brief Implements the Game class, which manages the core game loop.
 */

#include "Game.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "../mesh/Mesh.h"

Game::Game(int width, int height, std::string title)
  : width(width),
    height(height),
    title(title),
    targetFps(61.0),
    targetFrameTime(1.0 / targetFps),
    fpsCounter(0),
    secondsCounter(0),
    deltaTime(0) {}

bool Game::initialize() {
  // Create the window
  window = new Window(width, height, title);
  if (!window -> init()) {
    return false;
  }

  // Set up shaders
  shaderProgram = new ShaderProgram("shader/vertex_shader.glsl", "shader/fragment_shader.glsl");
  if (!shaderProgram -> init()) {
    return false;
  }

  camera = new Camera(45.0f, (float) window -> getWidth() / (float) window -> getHeight(), 0.1f, 100.0f);

  renderer = new Renderer(camera, shaderProgram);

  // Accept only the fragments closest to the screen when overlapping
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // Cull triangles which normal is not towards the camera
  glEnable(GL_CULL_FACE);

  // Hide cursor
  glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  // Cube vertices to be rendered to screen
  const GLfloat vertices[] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
  };

  const GLfloat colors[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
  };

  cube = new Mesh(vertices, colors, sizeof(vertices));

  lastTime = glfwGetTime();

  return true;
}

void Game::update(double startTime) {
  deltaTime = startTime - lastTime;
  lastTime = startTime;
  secondsCounter += deltaTime;
  ++fpsCounter;

  // Output FPS
  if (secondsCounter >= 1) {
    std::cout << "FPS: " << fpsCounter << std::endl;
    fpsCounter = 0;
    secondsCounter = 0;
  }

  // Calculate frame time and control FPS by sleeping if needed
  double frameEndTime = glfwGetTime();
  double frameTime = frameEndTime - startTime;
  if (frameTime < targetFrameTime) {
      std::this_thread::sleep_for(std::chrono::microseconds((int) ((targetFrameTime - frameTime) * 1000000)));
  }
}

void Game::handleInput() {
  // Handle movement
  if (glfwGetKey( window -> getWindow(), GLFW_KEY_W ) == GLFW_PRESS){
    camera -> moveForward(deltaTime);
  }

  if (glfwGetKey( window -> getWindow(), GLFW_KEY_S ) == GLFW_PRESS){
    camera -> moveBackward(deltaTime);
  }

  if (glfwGetKey( window -> getWindow(), GLFW_KEY_D ) == GLFW_PRESS){
    camera -> moveRight(deltaTime);
  }

  if (glfwGetKey( window -> getWindow(), GLFW_KEY_A ) == GLFW_PRESS){
    camera -> moveLeft(deltaTime);
  }

  handleMouseMovement();

  // End game if esc is pressed
  if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window->getWindow(), true);
  }
}

void Game::handleMouseMovement() {
  double xPosition, yPosition;
  glfwGetCursorPos(window -> getWindow(), &xPosition, &yPosition);

  int screenWidth, screenHeight;
  glfwGetWindowSize(window -> getWindow(), &screenWidth, &screenHeight);
  glfwSetCursorPos(window -> getWindow(), screenWidth / 2, screenHeight / 2);

  camera -> updateOrientation(deltaTime, xPosition, yPosition, screenWidth, screenHeight);
}

void Game::render() {
  glm::mat4 modelMatrix = glm::mat4(1.0f);

  // Clear the screen, preparing it for new frame rendering
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Render to the screen
  renderer -> render(*cube, modelMatrix);
}

int Game::run() {
  if (!initialize()) {
    return -1;
  }

  while (!window -> shouldClose()) {
    double startTime = glfwGetTime();

    handleInput();

    render();

    // Swap the front and back buffers, displaying the newly rendered frame
    window -> swapBuffers();

    // Process any pending events, such as keyboard and mouse input
    window -> pollEvents();

    update(startTime);
  }
  return 0;
}

Game::~Game() {
  delete camera;
  delete renderer;
  delete shaderProgram;
  delete window;
  delete cube;
}