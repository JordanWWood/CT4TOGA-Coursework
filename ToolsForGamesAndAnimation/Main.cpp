#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
	Window window(800, 600, 50, 50, "Artifact", hInstance, iCmdShow);

	Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
						  Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
						  Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Transform transform;

	float counterx = 0.0f;

	while (!window.isClosed()) {
		window.Clear(0, 0.15, 0.3, 0);

		float sinCounter = sinf(counterx);
		float cosCounter = cosf(counterx);

		transform.GetPos().x = sinf(counterx);
		transform.GetRot().z = counterx * 5;
		transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform);
		mesh.Draw();

		window.Update();

		counterx += 0.01f;
	}

	return 0;
}