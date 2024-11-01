/**
 * @file ShaderProgram.cpp
 * @brief Implements the ShaderProgram class, which manages shader compilation, linking, and usage in OpenGL.
 */

#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) 
  : vertexShaderPath(vertexShaderPath), fragmentShaderPath(fragmentShaderPath), programId(0) {}

bool ShaderProgram::init() {
  // Initialize GLEW
  glewExperimental = GL_TRUE;  // Enable modern OpenGL functionality in GLEW
  if (glewInit() != GLEW_OK) {
      std::cerr << "Failed to initialize GLEW" << std::endl;
      return false;
  }

  // Vertex and fragment shader source code
  std::string vertexShaderSource = loadShaderSource(vertexShaderPath);
  std::string fragmentShaderSource = loadShaderSource(fragmentShaderPath);

  // Compile the shaders
  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

  // Create shader program and link shaders
  programId = glCreateProgram();
  glAttachShader(programId, vertexShader);
  glAttachShader(programId, fragmentShader);
  glLinkProgram(programId);

  // Use the shader program and clean up individual shaders since they are already compiled and linked into the programId
  glUseProgram(programId);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return true;
}

std::string ShaderProgram::loadShaderSource(const std::string& filepath) {
  std::ifstream shaderFile(filepath);
  std::stringstream shaderStream;

  if(!shaderFile.is_open()) {
    std::cerr << "Failed to open shader file " << filepath << std::endl;
    return "";
  }

  // Read file's buffer contents into a stream and then return the contents converted into a string
  shaderStream << shaderFile.rdbuf();
  shaderFile.close();
  return shaderStream.str();
}

void ShaderProgram::useProgram() {
  glUseProgram(programId);
}

GLuint ShaderProgram::compileShader(unsigned int type, const char* source) {
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "Shader compilation error:\n" << infoLog << std::endl;
    }

    return id;
}

ShaderProgram::~ShaderProgram() {
  if(programId) {
    glDeleteProgram(programId);
  }
}