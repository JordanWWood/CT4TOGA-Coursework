#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <gl\glew.h>
#include "transform.h"

class Shader {
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform);
	
	virtual ~Shader();

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
