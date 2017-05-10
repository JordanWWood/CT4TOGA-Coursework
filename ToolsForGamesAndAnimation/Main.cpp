#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "EntityPlayer.h"
#include "AsteroidController.h"

#include "glm/gtx/string_cast.hpp"

// Temp
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow);

EntityPlayer * p;
AsteroidController * a;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
	// enable console
	AllocConsole();
	FILE* pCin; //for CIN to work
	freopen_s(&pCin, "CONIN$", "r", stdin);
	FILE* pCout; //for COUT to work
	freopen_s(&pCout, "CONOUT$", "w", stdout);
	FILE* pCerr; //for CERR to work
	freopen_s(&pCerr, "CONOUT$", "w", stderr);

	Window window(WIDTH, HEIGHT, 50, 50, "UP826858 Asteroids Artifact", hInstance, iCmdShow);
	Shader shader("./res/basicShader");
	Camera camera(glm::vec3(0, 0, -3), -8.0f, 8.0f, -6.0f, 6.0f, 0.01f, 1000.0f);

	p = new EntityPlayer();
	a = new AsteroidController();

	// game loop
	while (!window.isClosed()) {
		window.Clear(0.0, 0.15, 0.3, 0.0);
			
		p->GetInput(shader, camera);
		//a->Update(shader, camera);

		// Update Window
		window.Update();
	}

	return 0;
}