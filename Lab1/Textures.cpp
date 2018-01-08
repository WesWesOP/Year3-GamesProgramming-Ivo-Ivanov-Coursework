#include "Textures.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Textures::Textures(const std::string& fileName)
{
	int width, height, componentsNum; //width, height, and no of components of image
	unsigned char* dataImage = stbi_load((fileName).c_str(), &width, &height, &componentsNum, 4); //load the image and store the data

	if (dataImage == NULL)
	{
		std::cerr << "failed to load texture" << fileName << std::endl;
	}

	glGenTextures(1, &texHandler); // number of and address of textures
	glBindTexture(GL_TEXTURE_2D, texHandler); //bind texture - define type 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap texture outside height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnifcation (texture is larger)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataImage); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data

	stbi_image_free(dataImage);
}

Textures::~Textures()
{
	glDeleteTextures(1, &texHandler); // number of and address of textures
}

void Textures::bindTo(unsigned int units)
{
	assert(units >= 0 && units <= 31); // check we are working with one of the 32 textures

	glActiveTexture(GL_TEXTURE0 + units); //set acitve texture unit
	glBindTexture(GL_TEXTURE_2D, texHandler); //type of and texture to bind to unit
}
