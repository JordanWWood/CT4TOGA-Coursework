#include "window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
	Window window(800, 600, 50, 50, "Artifact", hInstance, iCmdShow);

	float color = .0f;

	while (!window.isClosed()) {
		glClear(GL_COLOR_BUFFER_BIT);

		if (color < .9) {
			glClearColor(color, 0, 0.5, 1.0);

			color += .1f;
		}
		else {
			color = .0f;
		}

		window.Update();
	}

	return 0;
}