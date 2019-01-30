#include <iostream>
#include <math.h>
#include <glew/GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include <iostream>
#include <math.h>
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "HdriLoader.h"

int main(int argc, char** argv) {
	Display display(1920, 1020, "Cubemap Converter");
	Shader shader("./res/basicShader");
	//Texture texture("./res/bricks.jpg");
	HdriLoader hdri(L"./res/flower_road_4k.hdr");
	//HdriLoader hdri(L"./res/VizPeople_non_commercial_hdr_v1_01.hdr");
	Mesh sphere("./res/sphere.obj");
	Camera camera(glm::vec3(-3, 0, 0), 70.f, (float)display.GetWindowWidth()/display.GetWindowHeight(), 0.01f, 1000.0f);
	Transform transform;
	float counter = 0.0f;

	//Endless loop
	while (!display.IsClosed()) {

		display.Clear(0.3f, 0.3f, 0.3f, 1.0f);

		transform.GetPos().x = sinf(counter);
		//transform.GetRot().y = sinf(counter);

		shader.Bind();

		//texture.Bind(0);
		hdri.Bind(0);

		shader.Update(transform, camera);

		sphere.Draw();

		display.Update();

		counter += 0.01f;
	}
	return 0;
}
