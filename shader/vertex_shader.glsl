#version 330 core

// Input vertex position from location 0, passed in by the CPU
layout (location = 0) in vec3 aPos;

// Input vertex color from location 1, passed in by the CPU
layout (location = 1) in vec3 aColor;

// Output color to be passed to the fragment shader, where it will be interpolated
out vec3 vertexColor;

// Uniform matrix for transforming the vertex position
uniform mat4 modelViewProjection;

void main() {
  // Set the position of the vertex in clip space coordinates
  gl_Position = modelViewProjection * vec4(aPos, 1.0);

  // Propagate color value to fragment shader
  vertexColor = aColor;
}