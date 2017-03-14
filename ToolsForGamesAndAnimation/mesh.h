#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <vector>
#include "shader.h"


class Vertex {
	public:
		Vertex(const glm::vec3& pos): pos(pos) {}
		
		inline glm::vec3* GetPos() { return &pos; }
	protected:
	private:
		glm::vec3 pos;
};

class Mesh
{
	public:
		Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices, glm::vec3& color);

		void dDraw();
		void tTransform(Transform transform, Shader &shader, Camera &camera); //TODO Rename

		inline Transform* GetLastTransform() { return &m_lastTransform; }

		virtual ~Mesh();
	private:
		enum {
			POSITION_VB,
			INDEX_VB,

			NUM_BUFFERS
		};

		glm::vec3 m_color;

		GLuint m_vertexArrayObject;
		GLuint m_vertexArrayBuffers[NUM_BUFFERS];
		unsigned int m_drawCount;

		Transform m_lastTransform;

		class Update {

		};
};

