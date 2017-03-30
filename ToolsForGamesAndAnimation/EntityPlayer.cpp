#include "EntityPlayer.h"

Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0)),
                      Vertex(glm::vec3(0, 0.5, 0)),
                      Vertex(glm::vec3(0.5, -0.5, 0)) };

unsigned int indices[] = { 0, 1, 2 };

EntityPlayer::EntityPlayer(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale, const float& health) {
	m_loc = Transform(pos, rot, scale);
	m_mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), glm::vec3(0.0f, 1.0f, 0.0f));
	m_health = health;
}

EntityPlayer::~EntityPlayer() {
	delete(m_mesh);
	m_mesh = NULL;
}
