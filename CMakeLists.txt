cmake_minimum_required(VERSION 3.10)
project(RetroKanto)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add executable
add_executable(RetroKanto main.cpp camera/Camera.cpp shader/ShaderProgram.cpp window/Window.cpp mesh/Mesh.cpp renderer/Renderer.cpp)

# Include GLFW and GLM
find_package(glfw3 3.3 REQUIRED)
find_library(GLEW_LIBRARIES GLEW PATHS /opt/homebrew/lib /usr/local/lib REQUIRED)
find_path(GLEW_INCLUDE_DIRS GL/glew.h PATHS /opt/homebrew/include /usr/local/include REQUIRED)

# Include directories for GLM and GLEW
include_directories("/opt/homebrew/include/glm") # Explicitly add GLM path
include_directories(${GLEW_INCLUDE_DIRS})

# Link libraries
target_link_libraries(RetroKanto glfw ${GLEW_LIBRARIES})

# Link the OpenGL framework
target_link_libraries(RetroKanto "-framework OpenGL")