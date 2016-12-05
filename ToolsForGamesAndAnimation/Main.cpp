#include "window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
	Window window(800, 600, 50, 50, "Artifact", hInstance, iCmdShow);

	while (!window.isClosed()) {
		glClear(GL_COLOR_BUFFER_BIT);

		window.Update();
	}

	return 0;
}