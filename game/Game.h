/**
 * @file Game.h
 * @brief Declares the Game class, which manages the core game loop.
 */

#ifndef GAME_H
#define GAME_H

#include <string>
#include "../shader/ShaderProgram.h"
#include "../window/Window.h"
#include "../camera/Camera.h"
#include "../renderer/Renderer.h"

/**
 * @class Game
 * @brief Manages the core game loop and rendering pipeline.
 *
 * The Game class initializes the game window, handles rendering,
 * updates frame-by-frame, and processes input from user.;
 */
class Game {
public:
  /**
   * @brief Constructs the Game object with specified window dimensions and title.
   * @param width Width of the game window.
   * @param height Height of the game window.
   * @param title Title displayed in the game window.
   */
  Game(int width, int height, std::string title);

  /**
   * @brief Destroys the Game object, releasing allocated resources.
   */
  ~Game();

  /**
   * @brief Starts and runs the main game loop.
   * @return Returns 0 upon successful execution.
   */
  int run();

private:
  /**
   * @brief Updates game state, including time management and FPS control.
   * @param startTime Timestamp of the start of the current frame.
   */
  void update(double startTime);

  /**
   * @brief Renders the current frame.
   */
  void render();

  /**
   * @brief Initializes all core components, including the window, shaders, camera, and renderer.
   * @return Returns true if initialization was successful; false otherwise.
   */
  bool initialize();

  /**
   * @brief Handles input from user.
   */
  void handleInput();

  /**
   * @brief Handles mouse movement from user.
   */
  void handleMouseMovement();

  /**
   * Pointer to the window object managing the display.
   */
  Window* window; 

  /**
   * Pointer to the shader program used for rendering.
   */
  ShaderProgram* shaderProgram;

  /**
   * Pointer to the renderer responsible for drawing.
   */
  Renderer* renderer;

  /**
   * Pointer to the camera for view transformations.
   */
  Camera* camera;

  /**
   * Pointer to the mesh representing the 3D cube.
   */
  Mesh* cube;

  /**
   * Width of the game window.
   */
  int width;

  /**
   * Height of the game window.
   */
  int height;

  /**
   * Title of the game window.
   */
  std::string title;

  /**
   * Timestamp of the last frame, used for deltaTime calculations.
   */
  double lastTime;

  /**
   * Target frames per second for the game.
   */
  double targetFps;

  /**
   * Target frame time duration for target FPS.
   */
  double targetFrameTime;

  /**
   * Counter for tracking frames per second.
   */
  int fpsCounter;

  /**
   * Counter for accumulating elapsed seconds to find frames per second.
   */
  double secondsCounter;

  /**
   * Time elapsed between the last frame and the current frame.
   */
  double deltaTime;
};

#endif