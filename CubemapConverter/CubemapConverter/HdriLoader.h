#pragma once

#include<string>
#include<IL/il.h>
#include<glew/GL/glew.h>

class HdriLoader
{
public:
	HdriLoader(const std::wstring& fileName);
	~HdriLoader();
	void Bind(unsigned int unit);
private:
	GLuint m_hdri;
	ILuint img_id;
};

