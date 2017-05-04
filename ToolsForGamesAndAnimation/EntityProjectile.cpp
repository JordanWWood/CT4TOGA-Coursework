#include "EntityProjectile.h"

Vertex vertices1[] = { Vertex(glm::vec3(-0.5f, 0.5f, 1.0f)),
					   Vertex(glm::vec3(0.5f, 0.5f, 0.0f)),
					   Vertex(glm::vec3(0.5f, -0.5f, 0.0f)),
					   Vertex(glm::vec3(-0.5f, -0.5f, 1.0f)) };

unsigned int indices1[] = { 0, 1, 2,
							2, 3, 0 };

EntityProjectile::EntityProjectile(const glm::vec3& pos, const glm::vec3& rot) : m_ttl(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) + std::chrono::milliseconds(1000)) {
	m_loc = Transform(pos, rot, glm::vec3(0.1, 0.2, 1));
	m_mesh = new Mesh(vertices1, sizeof(vertices1) / sizeof(vertices1[0]), indices1, sizeof(indices1) / sizeof(indices1[0]), glm::vec3(1.0f, 0.0f, 0.0f));
}

EntityProjectile::~EntityProjectile() {
	
}