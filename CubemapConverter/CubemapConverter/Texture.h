#pragma once

#include<string>
#include<glew/GL/glew.h>

class Texture {
public:
	Texture(const std::string& fileName);
	virtual ~Texture();
	void Bind(unsigned int unit);
private:
	GLuint m_texture;
};

