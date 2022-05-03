#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"
#include "GLS_Program.h"

enum class GameState{
	PLAY, EXIT
};
class MainGame
{
private:
	float time;
	GLS_Program program;
	int width;
	GameState gameState;
	int height;
	SDL_Window* window;
	void update();
	void init();
	void processInput();
	void draw();
	void initShaders();
	Sprite sprite[2];
public:
	void run();
	MainGame();
	~MainGame();
};

