/**
 * @file ShaderProgram.h
 * @brief Declares the ShaderProgram class, which manages shader compilation, linking, and usage in OpenGL.
 */

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include <GL/glew.h>

/**
 * @class ShaderProgram
 * @brief Represents a shader program that handles the loading, compiling, and linking of vertex and fragment shaders.
 *
 * The ShaderProgram class provides methods for initializing, using, and managing shader programs in OpenGL. It supports
 * loading shaders from file paths, compiling shader source code, and linking the compiled shaders into an executable
 * program that runs on the GPU.
 */
class ShaderProgram {
public:
  /**
   * @brief Constructs a ShaderProgram with file paths to vertex and fragment shaders.
   * @param vertexShaderPath File path to the vertex shader source code.
   * @param fragmentShaderPath File path to the fragment shader source code.
   *
   * This constructor sets up the paths for the shaders but does not initialize or compile them. Call `init()` to 
   * compile, link, and prepare the shader program for use.
   */
  ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

  /**
   * @brief Destructor that cleans up the shader program from OpenGL memory.
   *
   * Deletes the shader program from GPU memory, freeing resources.
   */
  ~ShaderProgram();

  /**
   * @brief Initializes the shader program by loading, compiling, and linking the shaders.
   * @return true if the shader program is successfully initialized; false if there was an error.
   *
   * This method loads shader source code from the specified files, compiles the vertex and fragment shaders, links them
   * into an OpenGL program, and prepares the program for use.
   */
  bool init();

  /**
   * @brief Activates the shader program for use in the OpenGL context.
   *
   * After calling this method, the shader program will be used for rendering until another program is activated or
   * unbound.
   */
  void useProgram();

private:
  /**
   * File path to the vertex shader source code.
   */
  std::string vertexShaderPath;

  /**
   * File path to the fragment shader source code.
   */
  std::string fragmentShaderPath;

  /**
   * OpenGL program ID for the linked shader program.
   */
  GLuint programId;

  /**
   * @brief Loads the shader source code from a file.
   * @param filepath Path to the shader file.
   * @return A string containing the loaded shader source code.
   */
  std::string loadShaderSource(const std::string& filepath);

  /**
   * @brief Compiles a shader from source code.
   * @param type Type of the shader (e.g., GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
   * @param source Pointer to the source code string of the shader.
   * @return The OpenGL ID of the compiled shader.
   */
  GLuint compileShader(unsigned int type, const char* source);
};

#endif
