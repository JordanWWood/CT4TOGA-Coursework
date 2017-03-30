#pragma once
#include "Mesh.h"

class Entity {
	public:
		virtual void Move(const float& speed, Shader& shader, Camera& camera) {}

		virtual void Rotate(const float& change, Shader& shader, Camera& camera) {}

		virtual void Draw(Shader shader, Camera camera) {}

		virtual void Scale(glm::vec3& change, Shader& shader, Camera& camera) {}
	protected:
		Mesh* m_mesh;
		Transform m_loc;
};