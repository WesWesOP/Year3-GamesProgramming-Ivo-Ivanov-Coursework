#pragma once
#include <string>
#include <GL\glew.h>
#include "transform.h"

class Shaders
{
public:
	Shaders(const std::string& filename);

	void bindTo(); //Set gpu to use our shaders
	void Update(const Transform& transform, const Camera& camera);
	

	std::string Shaders::ShaderLoad(const std::string& fileName);
	void Shaders::CheckError(GLuint shader, GLuint flags, bool Program, const std::string& errorMessage);
	GLuint Shaders::ShaderCreate(const std::string& text, unsigned int types);

	~Shaders();


protected:
private:
	static const unsigned int SHADERS_NUM = 2; // number of shaders

	enum
	{
		TRANSFORM_UNI,

		UNIFORMS_NUM
	};

	GLuint trackProgram; // Track the shader program
	GLuint shaders[SHADERS_NUM]; //array of shaders
	GLuint uniforms[UNIFORMS_NUM]; //no of uniform variables
};
