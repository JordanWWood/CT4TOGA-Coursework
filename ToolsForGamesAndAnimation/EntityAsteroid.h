#pragma once
#include "Entity.h"

class EntityAsteroid : Entity {
	public:
		EntityAsteroid(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3());
		~EntityAsteroid();

		void Move();
		void Draw(Shader& shader, Camera& camera);
		void Rotate(const float& change);

	private:
		float m_speed;
		glm::vec4 m_forwardVector;
};

