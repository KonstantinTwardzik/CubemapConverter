#pragma once

#include <glm/glm.hpp>
#include <glew/GL/glew.h>
#include <iostream>

class Vertex {
public:
	Vertex(const glm::vec3& pos) {
		this->pos = pos;
	}
	Vertex() {};
	void getCoord() {
		std::cout << pos.x << "\n";
	}
protected:
private:
	glm::vec3 pos;
};

class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	virtual ~Mesh();
	void Draw();
private:
	enum {
		POSITION_VB,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

