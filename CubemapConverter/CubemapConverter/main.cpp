#include <iostream>
#include <math.h>
#include <glew/GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include <iostream>

int main(int argc, char** argv) {
	Display display(800, 600, "Hello World!");

	int parCount = 10;
	int merCount = 10;
	int arrCount = 0;
	float parallel;
	float meridian;
	Vertex vert[100] = {};

	for (int i = 0; i < parCount; i++) {
		parallel = 3.141592654 * (i + 1) / parCount;
		for (int j = 0; j < merCount; j++) {
			meridian = 2.0 * 3.141592654 * j / merCount;
			float x = 5.0f*sinf(parallel)*sinf(meridian);
			float z = -5.0f*sinf(parallel)*cosf(meridian);
			float y = 5.0f*cosf(parallel);
			vert[arrCount] = Vertex(glm::vec3(x, y, z));
			arrCount++;
		}
	}

	for (int i = 0; i < 100; i++) {
		vert[i].getCoord();
	}


	Mesh mesh(vert, sizeof(vert) / sizeof(vert[0]));

	Shader shader("./res/basicShader");
	while (!display.IsClosed()) {
		display.Clear(0.3, 0.3, 0.3, 1.0);

		shader.Bind();

		mesh.Draw();

		display.Update();
	}
	return 0;
}