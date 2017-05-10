#pragma once
#include "Mesh.h"
#include "Entity.h"
#include "EntityProjectile.h"
#include <vector>

#include <iostream>

class EntityPlayer : Entity {
	public:
		EntityPlayer(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0), const float& health = 100);
		~EntityPlayer();

		void Move();
		void Rotate(const float& change);
		void Scale(glm::vec3& change);
		void FireProjectile();
		void UpdateProjectiles(Shader &shader, Camera &camera);
		void GetInput(Shader &shader, Camera &camera);
		void Draw(Shader& shader, Camera& camera);

		inline void SetHealth(float health) { m_health = health; }
		inline float GetHealth() { return m_health; }
		inline Transform GetLoc() { return m_loc; }

		// The current velocity of the player
		glm::vec2 velocity;
		// Amount of drag the ship experiences
		float dragFactor;

		// The speed at which the ship accelerates
		float acceleration;
	private:
		float m_health;
		std::vector<EntityProjectile *> projectiles;
};