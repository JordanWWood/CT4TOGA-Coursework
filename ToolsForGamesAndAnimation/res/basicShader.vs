#version 330 core

in vec3 position;
out vec4 vertexColor;
uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(position, 1.0);
	vertexColor = vec4(0.5f, 0.0f, 0.0f, 1.0f);
}