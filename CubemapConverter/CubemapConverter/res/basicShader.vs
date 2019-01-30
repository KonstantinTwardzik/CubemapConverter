#version 330 core

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

in vec2 UVPos;
in vec3 XYZPos;

out vec2 UVPos0;
out vec3 normal;

void main() {

	UVPos0 = UVPos;

	mat4 modelViewMat = viewMat * modelMat;
	mat4 modelViewProjectionMat = projectionMat * modelViewMat;

	gl_Position = modelViewProjectionMat * vec4(XYZPos, 1.0);

	normal = (modelViewMat * vec4(XYZPos, 0.0)).xyz;
}