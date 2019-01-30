#version 330
#define M_PI 3.1415926535897932384626433832795

in vec2 UVPos0;
in vec3 normal;

uniform float exposure = 1.0f;
uniform sampler2D hdri;
vec2 sphericalCoord;

out vec4 fragColor;


void main() {
	sphericalCoord.x = acos(normal.z / sqrt(((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z))));
	sphericalCoord.y = atan(normal.y, normal.x);
	
	sphericalCoord.x = sphericalCoord.x / M_PI;
	sphericalCoord.y = sphericalCoord.y + M_PI;
	sphericalCoord.y = sphericalCoord.y / (2*M_PI);

	fragColor = texture2D(hdri, sphericalCoord);
	fragColor *= exposure;
	
	//layout(location = 0) out vec3 color;

	//fragColor = vec4 (normal, sphericalCoord);
}