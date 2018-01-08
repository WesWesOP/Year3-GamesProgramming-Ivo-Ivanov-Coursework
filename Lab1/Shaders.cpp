#include "Shaders.h"
#include <iostream>
#include <fstream>

Shaders::Shaders(const std::string& filename)
{
	trackProgram = glCreateProgram(); // create shader program (openGL saves as ref number)
	shaders[0] = ShaderCreate(ShaderLoad("..\\res\\shader.vert"), GL_VERTEX_SHADER); // create vertex shader
	shaders[1] = ShaderCreate(ShaderLoad("..\\res\\shader.frag"), GL_FRAGMENT_SHADER); // create fragment shader
	//shaders[2] = ShaderCreate(ShaderLoad("..\\res\\fogShader.vert"), GL_VERTEX_SHADER); // create vertex shader
	//shaders[3] = ShaderCreate(ShaderLoad("..\\res\\fogShader.frag"), GL_FRAGMENT_SHADER); // create fragment shader

	for (unsigned int i = 0; i < SHADERS_NUM; i++)
	{
		glAttachShader(trackProgram, shaders[i]); //add all our shaders to the shader program "shaders" 
	}

	glBindAttribLocation(trackProgram, 0, "position"); // associate attribute variable with our shader program attribute (in this case attribute vec3 position;)
	glBindAttribLocation(trackProgram, 1, "texCoord");
	glBindAttribLocation(trackProgram, 2, "normals");

	glLinkProgram(trackProgram); //create executables that will run on the GPU shaders
	CheckError(trackProgram, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // cheack for error

	glValidateProgram(trackProgram); //check the entire program is valid
	CheckError(trackProgram, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_UNI] = glGetUniformLocation(trackProgram, "transform"); // associate with the location of uniform variable within a program
	
}


Shaders::~Shaders()
{
	for (unsigned int i = 0; i < SHADERS_NUM; i++)
	{
		glDetachShader(trackProgram, shaders[i]); //detach shader from program
		glDeleteShader(shaders[i]); //delete the sahders
	}
	glDeleteProgram(trackProgram); // delete the program
}

void Shaders::bindTo()
{
	glUseProgram(trackProgram); //installs the program object specified by program as part of rendering state
}

void Shaders::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(uniforms[TRANSFORM_UNI], 1, GLU_FALSE, &mvp[0][0]);
}


GLuint Shaders::ShaderCreate(const std::string& text, unsigned int types)
{
	GLuint shader = glCreateShader(types); //create shader based on specified type

	if (shader == 0) //if == 0 shader no created
		std::cerr << "Error type creation failed " << types << std::endl;

	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	CheckError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

std::string Shaders::ShaderLoad(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shaders::CheckError(GLuint shader, GLuint flags, bool Program, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (Program)
		glGetProgramiv(shader, flags, &success);
	else
		glGetShaderiv(shader, flags, &success);

	if (success == GL_FALSE)
	{
		if (Program)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

