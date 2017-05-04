#include "EntityPlayer.h"
#include <chrono>
#include <Windows.h>
#include "glm/gtx/string_cast.hpp"

Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0)),
                      Vertex(glm::vec3(0, 0.5, 0)),
                      Vertex(glm::vec3(0.5, -0.5, 0)) };

unsigned int indices[] = { 0, 1, 2 };

EntityPlayer::EntityPlayer(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale, const float& health) : acceleration(0.1f), dragFactor(0.02f) {
	m_loc = Transform(pos, rot, scale);
	m_mesh = new Mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), glm::vec3(0.0f, 1.0f, 0.0f));
	m_health = health;
}

EntityPlayer::~EntityPlayer() {
	delete(m_mesh);
	m_mesh = NULL;
}

void EntityPlayer::Move() {
	glm::mat4 rotZMatrix = glm::rotate(-m_loc.GetRot().z, glm::vec3(0, 0, 1));
	glm::vec4 forwardVec = glm::vec4(0, 1, 0, 0) * rotZMatrix;

	velocity.x = forwardVec.x * acceleration;
	velocity.y = forwardVec.y * acceleration;

	std::cout << "velocity (" << velocity.x << ", " << velocity.y << ")" << std::endl  << glm::to_string(forwardVec) << std::endl;
}

void EntityPlayer::Rotate(const float& change) {
	m_loc.SetRot(m_loc.GetRot() + glm::vec3(0, 0, change));
}

void EntityPlayer::Scale(glm::vec3& change) {
	m_loc.SetScale(m_loc.GetScale() + change);
}

void EntityPlayer::Draw(Shader& shader, Camera& camera) {
	// Update position based on velocity
	m_loc.GetPos().x += velocity.x;
	m_loc.GetPos().y += velocity.y;

	// Use Stokes' law to apply drag to the ship
	velocity.x = velocity.x - velocity.x * dragFactor;
	velocity.y = velocity.y - velocity.y * dragFactor;

	m_mesh->tTransform(m_loc, shader, camera);
	UpdateProjectiles(shader, camera);
}

void EntityPlayer::FireProjectile() {
	projectiles.push_back(new EntityProjectile(m_loc.GetPos(), m_loc.GetRot()));
	std::cout << "Projectile created" << std::endl;
}

void EntityPlayer::UpdateProjectiles(Shader &shader, Camera &camera) {
	std::vector<EntityProjectile *> toRemove;
	for (EntityProjectile * proj : projectiles) {
		proj->Move(0.3);
		proj->Draw(shader, camera);
		std::cout << "Drawing Projectile" << std::endl;

		std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			
		if (proj->GetTTL() < millis) {
			toRemove.push_back(proj);
			std::cout << "Projectile added to remove list" << std::endl;
		}
	}

	for (EntityProjectile * proj : toRemove) {
		auto it = std::find(projectiles.begin(), projectiles.end(), proj);
		if (it != projectiles.end()) {
			projectiles.erase(it);
		}
	}
}

std::chrono::milliseconds lastShot;
std::chrono::milliseconds timeBetweenShots = std::chrono::milliseconds(100);

void EntityPlayer::GetInput(Shader& shader, Camera& camera) {
	bool move = false;

	if (GetAsyncKeyState(VK_LEFT)) {
		Rotate(-0.05);
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		Rotate(0.05);
	}
	if (GetAsyncKeyState(VK_UP)) {
		Move();
	}
	if (GetAsyncKeyState('Z') && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) > lastShot + timeBetweenShots) {
		std::cout << "Creating Projectile" << std::endl;
		FireProjectile();
		lastShot = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	}

	Draw(shader, camera);
}