#include "EntityAsteroid.h"
#include <stdlib.h>

// Points
Vertex asteroid[] = { Vertex(glm::vec3(0.0f,   0.0f, 0.0f)),
					  Vertex(glm::vec3(-0.5f,   1.0f, 0.0f)),
				      Vertex(glm::vec3(0.5f,   1.0f, 0.0f)),
					  Vertex(glm::vec3(1.0f,   0.0f, 0.0f)),
					  Vertex(glm::vec3(0.5f,   -1.0f, 0.0f)),
					  Vertex(glm::vec3(-0.5f,  -1.0f, 0.0f)),
					  Vertex(glm::vec3(-1.0f,   0.0f, 0.0f))
};

// Order to render the points
unsigned int asteroidIndices[] = { 0, 1, 2, 3, 4, 5, 6, };

EntityAsteroid::EntityAsteroid(const glm::vec3& pos, const glm::vec3& rot) : m_speed(0.1f) {
	float f = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // Generate a number between 0 and 1.0f to create a pseudo random scale

	// Set the location, rotation and scale to render the object
	m_loc = Transform(pos, rot, glm::vec3(f, f, f));

	// Create the mesh for the object
	m_mesh = new Mesh(asteroid, sizeof(asteroid) / sizeof(asteroid[0]), asteroidIndices, sizeof(asteroidIndices) / sizeof(asteroidIndices[0]), glm::vec3(0.0f, 1.0f, 0.0f));

	// Set forward vector to be the direction it started facing
	glm::mat4 rotZMatrix = glm::rotate(-m_loc.GetRot().z, glm::vec3(0, 0, 1));
	m_forwardVector = glm::vec4(0, 1, 0, 0) * rotZMatrix;
}

EntityAsteroid::~EntityAsteroid() {
	// Leaving this here just incase the parent deconstructor isnt invoked when this object is deconstructed, couldnt find any information relating to this
}

void EntityAsteroid::Move() {
	m_loc.SetPos(m_loc.GetRot() + (glm::vec3)(m_forwardVector * m_speed));
}

void EntityAsteroid::Rotate(const float& change) {
	m_loc.SetRot(m_loc.GetRot() + glm::vec3(0, 0, change));
}

void EntityAsteroid::Draw(Shader& shader, Camera& camera) {
	m_mesh->tTransform(m_loc, shader, camera);
}
