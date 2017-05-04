#pragma once
#include "Mesh.h"
/**
 * Abstract class to define what all entitys should need
 */
class Entity {
	public:
		// Delete the mesh pointer when the object is deconstructed. This should be invoked when the child object is destroyed from what I understand
		~Entity() {
			delete(m_mesh);
			m_mesh = NULL;
		}

		// Virtual functions that must be part of an entity. All entitiys, at least in my situation, will need to be moved rotated and scaled.
		virtual void Move(const float& speed) {}
		virtual void Rotate(const float& change) {}
		virtual void Scale(glm::vec3& change) {}

		inline void Draw(Shader& shader, Camera& camera) {
			m_mesh->tTransform(m_loc, shader, camera);
		} // Potentially uneeded function that allows me to draw an object without passing a transform to the shader in its last position

		inline Transform GetLoc() { return m_loc; }
	protected:
		Mesh* m_mesh;
		Transform m_loc;
};