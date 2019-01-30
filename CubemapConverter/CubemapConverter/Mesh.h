#pragma once

#include <glm/glm.hpp>
#include <glew/GL/glew.h>
#include <iostream>
#include "obj_loader.h"

class Vertex {
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord) {
		this->pos = pos;
		this->texCoord = texCoord;
	}
	Vertex() {};
	void getCoord() {
		std::cout << "X: " << pos.x << "	Y: " << pos.y << "	Z: " << pos.z << "\n";
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }

protected:
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	virtual ~Mesh();
	void printVertices(unsigned int num);
	void Draw();
private:
	void InitMesh(const IndexedModel& model);

	enum {
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
	Vertex* verts;
};

