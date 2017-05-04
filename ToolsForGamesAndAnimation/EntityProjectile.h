#pragma once
#include "Entity.h"
#include <chrono>

class EntityProjectile : Entity {
	//transform.SetScale(glm::vec3(0.1f, 0.2f, 1.0f));
	public:
		EntityProjectile(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3());
		~EntityProjectile();

		inline void Move(const float& speed) {
			glm::mat4 rotZMatrix = glm::rotate(-m_loc.GetRot().z, glm::vec3(0, 0, 1));
			glm::vec4 forwardVec = glm::vec4(0, 1, 0, 0) * rotZMatrix;

			m_loc.SetPos(m_loc.GetPos() + (glm::vec3)(forwardVec * speed));
		}

		inline void Draw(Shader& shader, Camera& camera) {
			m_mesh->tTransform(m_loc, shader, camera);
		}

		inline Transform GetLoc() { return m_loc; }
		inline std::chrono::microseconds GetTTL() { return m_ttl; }
	private:
		std::chrono::milliseconds m_ttl;
};