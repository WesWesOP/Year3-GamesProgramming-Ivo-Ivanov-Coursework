#include "Game.h"
#include "Camera.h"
#include "Screen.h"
#include <iostream>
#include <string>
#include <SDL\SDL.h>

Transform transform;


double shuttleValueX;
double shuttleValueY;
bool keysPress;
float moveLeft1;;
float moveLeft2;
float moveLeft3;

Game::Game()
{
	_stateGame = GameState::PLAY;
	Screen* _gameDisplay = new Screen(); //new display
	WorkMesh* mesh1(); // new mesh
	WorkMesh* mesh2(); // new mesh2
	WorkMesh* mesh3(); // new mesh3
	WorkMesh* mesh4(); // new mesh4
	Audio* audio(); // audio device
	
}

Game::~Game()
{
}

void Game::execute()
{
	systemStart();
	Loop();
}

void Game::systemStart()
{
	_gameScreen.initScreen();

	mesh1.loadModel("..\\res\\Shuttle.obj"); //loading the model from a file
	mesh2.loadModel("..\\res\\asteroid.obj"); // loading the model from a file
	mesh3.loadModel("..\\res\\asteroid.obj");
	mesh4.loadModel("..\\res\\asteroid.obj");

	beep = audio.loadSound("..\\res\\bang.wav"); // loading sound
	bGMusic = audio.loadSound("..\\res\\background.wav"); // loading sound

	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameScreen.getW() / _gameScreen.getH(), 0.01f, 1000.0f);
	
	count = 0.0f;
}

void Game::Loop()
{
	while (_stateGame != GameState::EXIT)
	{
		inputCheck(); 
		gameDraw();
		collision(mesh1.getSpherePosition(), mesh1.getSphereRadius(), mesh2.getSpherePosition(), mesh2.getSphereRadius()); //cheks for collision between sepcified objects
		collision1(mesh1.getSpherePosition(), mesh1.getSphereRadius(), mesh3.getSpherePosition(), mesh3.getSphereRadius());
		collision2(mesh1.getSpherePosition(), mesh1.getSphereRadius(), mesh4.getSpherePosition(), mesh4.getSphereRadius());
		audioPlay(bGMusic, glm::vec3(0.0f, 0.0f, 0.0f)); // plays audio
	}

}

void Game::inputCheck()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) //get and process events
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_stateGame = GameState::EXIT;
			break;
		}

		if (event.type == SDL_KEYDOWN) //if statemnt for when a key is pressed
		{
			SDL_Keycode keyPress = event.key.keysym.sym;

			switch (keyPress) //switch statement for key presses
			{
			case SDLK_LEFT: //case for moving left
				shuttleValueX += 0.4;
				break;
			case SDLK_RIGHT: // case for mving right
				shuttleValueX -= 0.4;
				break;
			case SDLK_UP: //case for moving up
				shuttleValueY += 0.4;
				break;
			case SDLK_DOWN: // case for moving down
				shuttleValueY -= 0.4;
				break;
			}
		}
	}

}


bool Game::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z)); //gets the positions of the squares

	if (distance < (m1Rad + m2Rad)) //checks if distance is smaller
	{
		cout << "Damage!!!"; //prints damage
		audio.setlistener(myCamera.getPos(), m1Pos); //sets the player object as the audio listener
		audioPlay(beep, m1Pos); // plays a sound
		return true;
	}
	else
	{
		return false;
	}
}

bool Game::collision1(glm::vec3 m1Pos, float m1Rad, glm::vec3 m3Pos, float m3Rad)
{
	float distance = glm::sqrt((m3Pos.x - m1Pos.x)*(m3Pos.x - m1Pos.x) + (m3Pos.y - m1Pos.y)*(m3Pos.y - m1Pos.y) + (m3Pos.z - m1Pos.z)*(m3Pos.z - m1Pos.z));

	if (distance < (m1Rad + m3Rad))
	{
		cout << "Damage!!!";
		audio.setlistener(myCamera.getPos(), m1Pos);
		audioPlay(beep, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

bool Game::collision2(glm::vec3 m1Pos, float m1Rad, glm::vec3 m4Pos, float m4Rad)
{
	float distance = glm::sqrt((m4Pos.x - m1Pos.x)*(m4Pos.x - m1Pos.x) + (m4Pos.y - m1Pos.y)*(m4Pos.y - m1Pos.y) + (m4Pos.z - m1Pos.z)*(m4Pos.z - m1Pos.z));

	if (distance < (m1Rad + m4Rad))
	{
		cout << "Damage!!!";
		audio.setlistener(myCamera.getPos(), m1Pos);
		audioPlay(beep, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

void Game::audioPlay(unsigned int Source, glm::vec3 pos)
{

	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		audio.playSound(Source, pos);
	}
}

void Game::gameDraw()
{

	moveLeft1 = (-3.5) + count * 2;
	moveLeft2 = (-2.5) + count + 1;
	moveLeft3 = (-2.5) + count * 3;
	
	_gameScreen.clearScreen(0.0f, 0.0f, 0.0f, 1.0f);

	Shaders shader("..\\res\\shader"); //draws the shaders
	Textures texture("..\\res\\gold.jpg"); //draws the texture
	Textures texture1("..\\res\\moonrock.jpg"); //draws the texture
	
	
	transform.SetPosition(glm::vec3((2.5) + shuttleValueX, shuttleValueY, 0.0)); //controls the position of the object
	transform.SetRotation(glm::vec3(0.0, 0.0, 0.0)); //controls the rotation of the object
	transform.SetScale(glm::vec3(0.7, 0.7, 0.7)); //controls the scale of the object

	shader.bindTo(); //binds the shader
	shader.Update(transform, myCamera); //updates the transform and camera position
	texture.bindTo(0); //binds the texture
	mesh1.Make(); //draws the mesh
	mesh1.updateSphereData(*transform.GetPosition(), 0.35f); //updates the square position in accordance to the mesh object

	if (moveLeft1 > 3.5) //checks for the left edge of the screen
	{
		moveLeft1 = -8 + count; //sets the position of the asteroid to the oposite end of the screen
	}

	transform.SetPosition(glm::vec3(moveLeft1, 0.0, 0.0));
	transform.SetRotation(glm::vec3(0.0, 0.0, count*2));
	transform.SetScale(glm::vec3(0.4, 0.4, 0.4));

	shader.bindTo();
	shader.Update(transform, myCamera);
	texture1.bindTo(0);
	mesh2.Make();
	mesh2.updateSphereData(*transform.GetPosition(), 0.40f);
	count = count + 0.01f;


	if (moveLeft2 > 3.5)
	{
		moveLeft2 = -8 + count + 2;
	}

	transform.SetPosition(glm::vec3(moveLeft2, 1.5, 0.0));
	transform.SetRotation(glm::vec3(0.0, 0.0, count*2));
	transform.SetScale(glm::vec3(0.3, 0.3, 0.3));

	shader.bindTo();
	shader.Update(transform, myCamera);
	texture1.bindTo(0);
	mesh3.Make();
	mesh3.updateSphereData(*transform.GetPosition(), 0.30f);
	count = count + 0.01f;

	if (moveLeft3 > 3.5)
	{
		moveLeft3 = -8 + count +3;
	}

	transform.SetPosition(glm::vec3(moveLeft3, -1.5, 0.0));
	transform.SetRotation(glm::vec3(0.0, 0.0, -count*3));
	transform.SetScale(glm::vec3(0.2, 0.2, 0.2));

	shader.bindTo();
	shader.Update(transform, myCamera);
	texture1.bindTo(0);
	mesh4.Make();
	mesh4.updateSphereData(*transform.GetPosition(), 0.20f);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameScreen.bufferSwap(); //swaps buffers
}
