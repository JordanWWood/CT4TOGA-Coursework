#include "window.h"
#include "shader.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
	Window window(800, 600, 50, 50, "Artifact", hInstance, iCmdShow);

	Shader shader("./res/basicShader");

	while (!window.isClosed()) {
		shader.Bind();

		window.Update();
	}

	return 0;
}