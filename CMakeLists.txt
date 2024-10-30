cmake_minimum_required(VERSION 3.10)
project(RetroKanto)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add executable
add_executable(RetroKanto main.cpp)

# Include GLFW and GLM
find_package(glfw3 3.3 REQUIRED)
include_directories("/opt/homebrew/include/glm") # Explicitly add GLM path

# Link libraries
target_link_libraries(RetroKanto glfw)

# Link the OpenGL framework
target_link_libraries(RetroKanto "-framework OpenGL")