#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define WIDTH 800
#define HEIGHT 600

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
	Window window(WIDTH, HEIGHT, 50, 50, "Artifact", hInstance, iCmdShow);

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
						  Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
						  Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)), };

	unsigned int indices[] = { 0, 1, 2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Shader shader("./res/basicShader");

	Camera camera(glm::vec3(0, 0, -3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;

	float counterx = 0.0f;

	// game loop
	while (!window.isClosed()) {
		window.Clear(0, 0.15, 0.3, 0);

		float sinCounter = sinf(counterx);
		float cosCounter = cosf(counterx);


		transform.GetPos().x = sinf(counterx);
		transform.GetPos().z = cosCounter;
		transform.GetRot().z = counterx;
		transform.GetRot().y = counterx;
		transform.GetRot().z = counterx;

		mesh.tTransform(transform, shader, camera);

		// Update Window
		window.Update();

		counterx += 0.01f;
	}

	return 0;
}