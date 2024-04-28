#version 410 core
layout (location = 0) in vec3 position;

uniform mat4 mat4Model;

void main() {
    gl_Position = mat4Model * vec4(position, 1.0);
}
