#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <gl\glew.h>
#include "transform.h"
#include "camera.h"

class Shader {
public:
	Shader(const std::string& fileName);

	void Bind();
	void UnBind();

	void Update(const Transform& transform, const Camera& camera, glm::vec3& color);
	
	virtual ~Shader();

	inline GLuint getProgram() { return m_program; } // TODO OOPify
protected:
private:
	static const unsigned int NUM_SHADERS = 2;

	enum {
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};
