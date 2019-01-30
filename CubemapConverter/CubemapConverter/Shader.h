#pragma once

#include<string>
#include<glew/GL/glew.h>
#include <SDL2/SDL.h>
#include"Transform.h"
#include"Camera.h"

class Shader {
public:
	Shader(const std::string& fileName);
	virtual ~Shader();
	void Bind();
	void Update(const Transform& transform, const Camera& camera);

private:
	void createRenderTarget();
	static const unsigned int NUM_SHADERS = 2;

	enum {
		PROJECTION_MATRIX_U,
		VIEW_MATRIX_U,
		MODEL_MATRIX_U,
		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

