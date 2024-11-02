#version 330 core

// Get the color from vertex shader
in vec3 vertexColor;

// Output color for the fragment (pixel)
out vec4 fragmentColor;

void main() {
    // Set the fragment color to the interpolated vertex color with full opacity
    fragmentColor = vec4(vertexColor, 1.0);
}