#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

class Vertex
{
public:
	Vertex(const glm::vec3& position, const glm::vec2& texCoordinates, const glm::vec3& normals =glm::vec3(0,0,0))
	{
		this->position = position;
		this->texCoordinates = texCoordinates;
		this->normals = normals;
	}

	glm::vec3* GetPosition() { return &position; }
	glm::vec2* GetTexCoordinates() { return &texCoordinates; }
	glm::vec3* GetNormals() { return &normals; }

	glm::vec3 position;
	glm::vec2 texCoordinates; //postion on texture to map to vertex
	glm::vec3 normals;
};

struct Sphere
{
public:

	Sphere() {}

	Sphere(glm::vec3& pos, float radius)
	{
		this->pos = pos;
	}

	glm::vec3 GetPosition() { return pos; }
	float GetRadius() { return radius; }

	void SetPosition(glm::vec3 pos)
	{
		this->pos = pos;
	}

	void SetRadius(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 pos;
	float radius;
};

class WorkMesh
{
public:
	WorkMesh();

	~WorkMesh();

	void Make();
	void init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadModel(const std::string& filename);
	void initModel(const IndexedModel& model);
	void updateSphereData(glm::vec3 pos, float radius);
	glm::vec3 getSpherePosition() { return sphereMesh.GetPosition(); }
	float getSphereRadius() { return sphereMesh.GetRadius(); }
private:

	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORDINATES_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	Sphere sphereMesh;
	GLuint vertexArrayObj;
	GLuint vertexArrayBuff[NUM_BUFFERS]; // create our array of buffers
	unsigned int countDraw; //how much of the vertexArrayObject do we want to draw
};

