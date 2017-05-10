#pragma once
#include "Camera.h"
#include "Shader.h"
#include "EntityAsteroid.h"
#include <vector>

class AsteroidController {
	public:
		AsteroidController();
		void Update(Shader &shader, Camera &camera);
	private:
		std::vector<EntityAsteroid *> m_asteroids;
		int m_difficulty;
};

