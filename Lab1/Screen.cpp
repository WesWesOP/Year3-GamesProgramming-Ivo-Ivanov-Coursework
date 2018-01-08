#include "Screen.h"


Screen::Screen()
{
	windowSDL = nullptr; //initialise to generate null access violation for debugging. 
	screenW = 1024.0f; // set the screen width
	screenH = 768.0f; // set screen height
}

Screen::~Screen()
{
	SDL_GL_DeleteContext(contextGL); // delete context
	SDL_DestroyWindow(windowSDL); // detete window (make sure to delete the context and the window in the opposite order of creation in initScreen())
	SDL_Quit();
}

float Screen::getW() { return screenW; } //gets the screen width
float Screen::getH() { return screenH; } //gets the screen height

void Screen::errorReturn(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "press key to exit";
	int integer;
	std::cin >> integer;
	SDL_Quit();
}

void Screen::bufferSwap()
{
	SDL_GL_SwapWindow(windowSDL); //swap buffers
}

void Screen::clearScreen(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

void Screen::initScreen()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	windowSDL = SDL_CreateWindow("THE GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenW, (int)screenH, SDL_WINDOW_OPENGL); // create window

	if (windowSDL == nullptr)
	{
		errorReturn("failed to create window");
	}

	contextGL = SDL_GL_CreateContext(windowSDL);

	if (contextGL == nullptr)
	{
		errorReturn("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		errorReturn("GLEW failed to initialise");
	}

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	/*glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 1.0);
	glFogf(GL_FOG_END, 5.0);
	float color[] = { 1.0,1.0,1.0,1.0 };
	glFogfv(GL_FOG_COLOR, color);*/

	/*GLfloat fogColor[] = { 0.5, 0.5, 0.5, 1 };
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_START, 10.0f);
	glFogf(GL_FOG_END, 20.0f);
	glFogf(GL_FOG_DENSITY, 0.05f);*/

}
