#pragma once
#include <string>
#include <GL\glew.h>

class Textures
{
public:
	Textures(const std::string& filename);

	void bindTo(unsigned int units); // bind upto 32 textures
	

	~Textures();

protected:
private:

	GLuint texHandler;
};

