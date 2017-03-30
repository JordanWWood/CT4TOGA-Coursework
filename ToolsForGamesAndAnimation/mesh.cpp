#include "mesh.h"
#include <map>
#include <algorithm> 

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, glm::vec3& color) {
	m_drawCount = numIndices;
	m_color = color;

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	std::vector<glm::vec3> positions;

	positions.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++) {
		positions.push_back(*vertices[i].GetPos());
	}

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}


Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() {
	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Mesh::tTransform(Transform transform, Shader &shader, Camera &camera) {
	// Bind the shader
	shader.Bind();

	if (&m_lastTransform != NULL) {
		//transform = m_current + transform;
	}

	shader.Update(transform, camera, m_color); // Update the shader with the newly created transform
	this->Draw();

	m_lastTransform = transform; // save the last transform
	
	shader.UnBind(); // Unbind the shader, freeing it up for another object to transform
}