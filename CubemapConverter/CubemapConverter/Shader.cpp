#include "Shader.h"
#include <iostream>
#include <fstream>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName) {
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader("./res/normalShader.fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		glAttachShader(m_program, m_shaders[i]);
	}
	
	glBindAttribLocation(m_program, 0, "XYZPos");
	glBindAttribLocation(m_program, 1, "UVPos");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	m_uniforms[MODEL_MATRIX_U] = glGetUniformLocation(m_program, "modelMat");
	m_uniforms[VIEW_MATRIX_U] = glGetUniformLocation(m_program, "viewMat");
	m_uniforms[PROJECTION_MATRIX_U] = glGetUniformLocation(m_program, "projectionMat");

	//createRenderTarget();
}

Shader::~Shader() {
	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);
}

static GLuint CreateShader(const std::string & text, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0) {
		std::cerr << "Error: Shader creation failed!" << shaderType << std::endl;
	}
	const GLchar* shaderSourceString[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceString[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceString, shaderSourceStringLengths);
	glCompileShader(shader);
	
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}

void Shader::Bind() {
	glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera) {
	glm::mat4 modelMat = transform.GetModelMatrix();
	glm::mat4 viewMat = camera.GetViewMatrix();
	glm::mat4 projectionMat = camera.GetProjectionMatrix();
	glUniformMatrix4fv(m_uniforms[MODEL_MATRIX_U], 1, GL_FALSE, &modelMat[0][0]);
	glUniformMatrix4fv(m_uniforms[VIEW_MATRIX_U], 1, GL_FALSE, &viewMat[0][0]);
	glUniformMatrix4fv(m_uniforms[PROJECTION_MATRIX_U], 1, GL_FALSE, &projectionMat[0][0]);
}

static std::string LoadShader(const std::string& fileName) {
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) {
		glGetProgramiv(shader, flag, &success); 
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

void Shader::createRenderTarget() {
	glDisable(GL_DEPTH_TEST);
		
	//Creating the Render Target
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	GLuint renderedTexture;
	glGenTextures(1, &renderedTexture);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, 512, 512, 0, GL_RGB32F, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "Error: Render to Texture failed!"  << std::endl;
	}

	//Rendering to Texture
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
	glViewport(0, 0, 1920, 1020); // Render on the whole framebuffer, complete from the lower left corner to the upper right

	glEnable(GL_DEPTH_TEST);
}