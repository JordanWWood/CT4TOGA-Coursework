#pragma once
#include "Entity.h"

class EntityAsteroid : Entity {
	public:
		EntityAsteroid(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0));
		~EntityAsteroid();

		void Move();
		void Rotate(const float& change, Shader& shader, Camera& camera);
		void Draw(Shader& shader, Camera& camera);

	private:
		float m_speed;
};

