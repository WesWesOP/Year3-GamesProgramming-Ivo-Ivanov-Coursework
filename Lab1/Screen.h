#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Screen
{
public:
	Screen();

	~Screen();
	void initScreen();
	void bufferSwap();
	void clearScreen(float r, float g, float b, float a);

	float getW();
	float getH();
	float screenW;
	float screenH;

private:

	void errorReturn(std::string errorString);

	SDL_GLContext contextGL; //global variable to hold the context
	SDL_Window* windowSDL; //holds pointer to out window

};


