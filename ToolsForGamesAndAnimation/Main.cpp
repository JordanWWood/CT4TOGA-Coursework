#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
// Temp
#include <iostream>

#define WIDTH 800
#define HEIGHT 600

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow);

Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0)),
					  Vertex(glm::vec3(0, 0.5, 0)),
                      Vertex(glm::vec3(0.5, -0.5, 0))};

Vertex vertices1[] = { Vertex(glm::vec3(-0.5f, 0.5f, 1.0f)),
		               Vertex(glm::vec3(0.5f, 0.5f, 0.0f)),
		               Vertex(glm::vec3(0.5f, -0.5f, 0.0f)),
		               Vertex(glm::vec3(-0.5f, -0.5f, 1.0f)) };

unsigned int indices[] = { 0, 1, 2 };
unsigned int indices1[] = { 0, 1, 2, 
		                    2, 3, 0 };

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
	// enable console
	AllocConsole();
	FILE* pCin; //for CIN to work
	freopen_s(&pCin, "CONIN$", "r", stdin);
	FILE* pCout; //for COUT to work
	freopen_s(&pCout, "CONOUT$", "w", stdout);
	FILE* pCerr; //for CERR to work
	freopen_s(&pCerr, "CONOUT$", "w", stderr);

	Window window(WIDTH, HEIGHT, 50, 50, "Artifact", hInstance, iCmdShow);

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), glm::vec3(0.0f, 1.0f, 0.0f));
	Mesh mesh1(vertices1, sizeof(vertices1) / sizeof(vertices1[0]), indices1, sizeof(indices1) / sizeof(indices1[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	Mesh mesh2(vertices1, sizeof(vertices1) / sizeof(vertices1[0]), indices1, sizeof(indices1) / sizeof(indices1[0]), glm::vec3(0.5f, 0.0f, 0.5f));
	Shader shader("./res/basicShader");

	Camera camera(glm::vec3(0, 0, -3), -5.0f, 5.0f, -5.0f, 5.0f, 0.01f, 1000.0f);
	Transform transform;

	float counterx = 0.0f;
	float pos = 0.0f;

	// game loop
	while (!window.isClosed()) {
		window.Clear(0.0, 0.15, 0.3, 0.0);

		float sinCounter = sinf(counterx);
		float cosCounter = cosf(counterx);

		// mesh
		transform.GetPos().x = sinf(counterx);
		transform.GetPos().z = cosCounter;
		transform.GetRot().z = counterx;
		transform.GetRot().y = counterx;
		transform.GetRot().z = counterx;

		mesh.tTransform(transform, shader, camera);

		// mesh1
		transform.GetPos().x = cosf(counterx);
		transform.GetPos().z = sinCounter;
		transform.GetRot().z = counterx;
		transform.GetRot().y = counterx;
		transform.GetRot().z = counterx;

		mesh1.tTransform(transform, shader, camera);

		// mesh2
		transform.GetPos().x = -cosf(counterx);
		transform.GetPos().z = sinCounter;
		transform.GetRot().x = counterx;
		transform.GetRot().y = counterx;
		transform.GetRot().z = counterx;

		mesh2.tTransform(transform, shader, camera);



		if (GetAsyncKeyState(VK_LEFT)) {
			std::cout << counterx << std::endl;
			counterx += 0.01f;
		} else if (GetAsyncKeyState(VK_RIGHT)) {
			std::cout << counterx << std::endl;
			counterx -= 0.01f;
		} else if (GetAsyncKeyState('Z')) {
			std::cout << "z" << std::endl;
			pos = 0.01f;
		} else if (GetAsyncKeyState('W')) {
			std::cout << "w" << std::endl;
		}
			
		// Update Window
		window.Update();
	}

	return 0;
}