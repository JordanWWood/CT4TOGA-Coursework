#include "EntityAsteroid.h"

Vertex asteroid[] = { Vertex(glm::vec3(0.0f,   0.0f, 0.0f)),
					  Vertex(glm::vec3(-0.5f,   1.0f, 0.0f)),
				      Vertex(glm::vec3(0.5f,   1.0f, 0.0f)),
					  Vertex(glm::vec3(1.0f,   0.0f, 0.0f)),
					  Vertex(glm::vec3(0.5f,   -1.0f, 0.0f)),
					  Vertex(glm::vec3(-0.5f,  -1.0f, 0.0f)),
					  Vertex(glm::vec3(-1.0f,   0.0f, 0.0f))
};

unsigned int asteroidIndices[] = { 0, 1, 2, 3, 4, 5, 6, };

EntityAsteroid::EntityAsteroid(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale) : m_speed(0.1f) {
	m_loc = Transform(pos, rot, scale);
	m_mesh = new Mesh(asteroid, sizeof(asteroid) / sizeof(asteroid[0]), asteroidIndices, sizeof(asteroidIndices) / sizeof(asteroidIndices[0]), glm::vec3(0.0f, 1.0f, 0.0f));
}

EntityAsteroid::~EntityAsteroid() {

}

void EntityAsteroid::Move() {
	glm::mat4 rotZMatrix = glm::rotate(-m_loc.GetRot().z, glm::vec3(0, 0, 1));
	glm::vec4 forwardVec = glm::vec4(0, 1, 0, 0) * rotZMatrix;

	m_loc.SetPos(m_loc.GetRot() + (glm::vec3)(forwardVec * m_speed));
}

void EntityAsteroid::Rotate(const float& change, Shader& shader, Camera& camera) {
	
}

void EntityAsteroid::Draw(Shader& shader, Camera& camera) {
	m_mesh->tTransform(m_loc, shader, camera);
}
