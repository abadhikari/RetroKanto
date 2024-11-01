#version 330 core

// Input vertex position from location 0, passed in by the CPU
layout (location = 0) in vec3 aPos;
void main() {
    // Set the position of the vertex in clip space coordinates
    gl_Position = vec4(aPos, 1.0);
}