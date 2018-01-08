#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Screen.h" 
#include "Shaders.h"
#include "WorkMesh.h"
#include "Textures.h"
#include "transform.h"
#include "Audio.h"

enum class GameState { PLAY, EXIT };

class Game
{
public:
	Game();
	~Game();

	void execute();

private:

	void systemStart();
	void inputCheck();
	void Loop();
	void gameDraw();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	bool collision1(glm::vec3 m1Pos, float m1Rad, glm::vec3 m3Pos, float m3Rad);
	bool collision2(glm::vec3 m1Pos, float m1Rad, glm::vec3 m4Pos, float m4Rad);
	void audioPlay(unsigned int Source, glm::vec3 pos);


	Screen _gameScreen;
	GameState _stateGame;
	WorkMesh mesh1;
	WorkMesh mesh2;
	WorkMesh mesh3;
	WorkMesh mesh4;
	Audio audio;
	Camera myCamera;


	float count;
	unsigned int beep;
	unsigned int bGMusic;

};

