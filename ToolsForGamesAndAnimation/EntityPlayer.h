#pragma once
#include "Mesh.h"
#include "Entity.h"

#include <glm\gtc\quaternion.hpp>

#include <iostream>

class EntityPlayer : Entity {
	public:
		EntityPlayer(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0), const float& health = 100);
		~EntityPlayer();

		inline void Move(const float& speed, Shader& shader, Camera& camera) {
			glm::mat4 rotZMatrix = glm::rotate(-m_loc.GetRot().z, glm::vec3(0, 0, 1));
			glm::vec4 forwardVec = glm::vec4(0, 1, 0, 0) * rotZMatrix;

			m_loc.SetPos(m_loc.GetPos() + (glm::vec3)(forwardVec * speed));
			this->m_mesh->tTransform(m_loc, shader, camera);
		}

		inline void Rotate(const float& change, Shader& shader, Camera& camera) {
			m_loc.SetRot(m_loc.GetRot() + glm::vec3(0,0,change));

			std::cout << m_loc.GetRot().x << "," << m_loc.GetRot().y << "," << m_loc.GetRot().z << std::endl;

			this->m_mesh->tTransform(m_loc, shader, camera);
		}

		inline void Draw(Shader shader, Camera camera) {
			m_mesh->tTransform(m_loc, shader, camera);
		}

		inline void Scale(glm::vec3& change, Shader& shader, Camera& camera) {
			m_loc.SetScale(m_loc.GetScale() + change);
			this->m_mesh->tTransform(m_loc, shader, camera);
		}

		inline float GetHealth() { return m_health; }
	private:
		float m_health;
};