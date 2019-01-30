#include "HdriLoader.h"
#include <cassert>
#include <iostream>

HdriLoader::HdriLoader(const std::wstring& fileName) {
	ilInit();

	img_id = ilGenImage();
	ilBindImage(img_id);
	ILboolean ok = ilLoadImage(fileName.c_str());

	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	int format = ilGetInteger(IL_IMAGE_FORMAT);
	int dataType = ilGetInteger(IL_IMAGE_TYPE);

	if (ilGetData() == NULL) {
		std::wcerr << "Texture loading failed for texture: " << fileName << std::endl;
	}

	glGenTextures(1, &m_hdri);
	glBindTexture(GL_TEXTURE_2D, m_hdri);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, dataType, ilGetData());
}


HdriLoader::~HdriLoader(){
	glDeleteTextures(1, &m_hdri);
	ilDeleteImage(img_id);
}

void HdriLoader::Bind(unsigned int unit) {
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_hdri);
}
