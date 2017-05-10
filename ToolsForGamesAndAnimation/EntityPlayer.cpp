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
	// Leaving this here just incase the parent deconstructor isnt invoked when this object is deconstructed, couldnt find any information relating to this
}

void EntityPlayer::Move() {
	// Get the rotation matrix based on the current rotation of the character
	glm::mat4 rotZMatrix = glm::rotate(-m_loc.GetRot().z, glm::vec3(0, 0, 1));
	// Multiply a vector where the defualt direction is Y by the rotation matrix. The forward vector is 1.0f on the Y because the player starts looking up
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

	// Apply the transformation to the object
	m_mesh->tTransform(m_loc, shader, camera);

	// Update projectiles that have been created
	UpdateProjectiles(shader, camera);
}

void EntityPlayer::FireProjectile() {
	// Add projectile to list of projectiles that are in the world
	projectiles.push_back(new EntityProjectile(m_loc.GetPos(), m_loc.GetRot()));

	// Debug
	std::cout << "Projectile created" << std::endl;
}

void EntityPlayer::UpdateProjectiles(Shader &shader, Camera &camera) {
	// Pre define a list for projectiles that have expended their ttl and add them as a pointer because we want to reference the esact same object as the one in the other vector
	std::vector<EntityProjectile *> toRemove;

	// Loop through the projectiles that are in the world
	for (EntityProjectile * proj : projectiles) {
		// Move that projectile forward and draw it
		proj->Move(0.3);
		proj->Draw(shader, camera);

		// Debug
		std::cout << "Drawing Projectile" << std::endl;

		// Store the current time in milliseconds
		std::chrono::milliseconds millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			
		// Check if the TTL is less than the current time
		if (proj->GetTTL() < millis) {
			// Add the projectile to a list of objects to remove since we cant edit the array whilst we are iterating it
			toRemove.push_back(proj);

			// Debug
			std::cout << "Projectile added to remove list" << std::endl;
		}
	}

	// Loop through the list of projectiles that have expended their TTL
	for (EntityProjectile * proj : toRemove) {
		// Search for the object in the vector of projectiles in the world
		auto it = std::find(projectiles.begin(), projectiles.end(), proj);

		// Double check we havent gone past the last position in the vector
		if (it != projectiles.end()) {
			// Remove it
			projectiles.erase(it);
		}
	}
}

// Last shot time
std::chrono::milliseconds lastShot;
// Amount of time between shots
std::chrono::milliseconds timeBetweenShots = std::chrono::milliseconds(100);

void EntityPlayer::GetInput(Shader& shader, Camera& camera) {

	// These arent else ifs so players are able to move forward at the same time as rotating
	// If player is holding down the left arrow key
	if (GetAsyncKeyState(VK_LEFT)) {
		// Rotate left
		Rotate(-0.05);
	}
	// If player is holding down the right arrow key
	if (GetAsyncKeyState(VK_RIGHT)) {
		// Rotate right
		Rotate(0.05);
	}
	// If player is holding down the up arrow key
	if (GetAsyncKeyState(VK_UP)) {
		// Move
		Move();
	}

	// If the player is holding down z and the current time is greater than the lastShot time + the time between shots
	if (GetAsyncKeyState('Z') && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) > lastShot + timeBetweenShots) {
		// Debug
		std::cout << "Creating Projectile" << std::endl;

		// FireProjectile
		FireProjectile();

		// Set last shot to the current time in milliseconds
		lastShot = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	}

	// Update the player on the other buffer
	Draw(shader, camera);
}