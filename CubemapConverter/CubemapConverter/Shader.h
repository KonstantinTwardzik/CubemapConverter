#pragma once

#include<string>
#include<glew/GL/glew.h>

class Shader {
public:
	Shader(const std::string& fileName);
	virtual ~Shader();
	void Bind();

private:
	static const unsigned int NUM_SHADERS = 2;

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};
