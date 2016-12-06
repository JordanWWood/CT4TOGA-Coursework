#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
	Window window(800, 600, 50, 50, "Artifact", hInstance, iCmdShow);

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
						  Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
						  Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");

	while (!window.isClosed()) {
		window.Clear(0, 0, 0.5, 0);

		shader.Bind();
		texture.Bind(0);
		mesh.Draw();

		window.Update();
	}

	return 0;
}