#include "window.h"
#include "shader.h"
#include "mesh.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
	Window window(800, 600, 50, 50, "Artifact", hInstance, iCmdShow);

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0)),
						  Vertex(glm::vec3(0, 0.5, 0)),
						  Vertex(glm::vec3(0.5, -0.5, 0)) };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Shader shader("./res/basicShader");

	while (!window.isClosed()) {
		window.Clear(0, 0, 0.5, 0);

		

		shader.Bind();
		mesh.Draw();

		window.Update();
	}

	return 0;
}