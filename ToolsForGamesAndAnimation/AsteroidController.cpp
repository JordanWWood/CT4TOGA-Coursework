#include "AsteroidController.h"

// no arg constructor to initialize the difficulty
AsteroidController::AsteroidController() : m_difficulty(5) {}

void AsteroidController::Update(Shader &shader, Camera &camera) {
	if (m_asteroids.size() < 1) {
		for (int i = 0; i < m_difficulty + 2; i++) {
			glm::vec4 view = camera.GetOrthoViewAsVector();

			glm::vec3 loc(view.x + (rand() % (int)(view.y - view.x + 1)), view.z + (rand() % (int)(view.w - view.z + 1)), 0.0f);
			glm::vec3 rot(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / glm::two_pi<float>())));

			EntityAsteroid * ast = new EntityAsteroid(loc , rot);
		}
	}

	for (EntityAsteroid * ast : m_asteroids) {
		ast->Move();
		ast->Draw(shader, camera);
	}
}
