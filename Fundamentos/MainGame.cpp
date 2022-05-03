#include "MainGame.h"
#include <iostream>
#include "Error.h"

MainGame::MainGame() :window(nullptr), width(800),
height(720),
gameState(GameState::PLAY)
{
	/*window = nullptr;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;*/
}

void MainGame::init()
{
	time = 0.0f;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Hola"
		, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		fatalError("No se pudo inicializar el SDL");
	}
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("No se pudo inicializar el GLEW");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	initShaders();
}

void MainGame::initShaders() {
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();
}

void MainGame::run()
{
	init();
	sprite[1].init(-1, -1, 1, 1,"Textures/texture.png");
	sprite[2].init(-1, 0, 1, 1, "Textures/texture2.png");
	update();
}

void MainGame::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
			case SDL_QUIT:
				gameState = GameState::EXIT;
			break;
			case SDL_MOUSEMOTION:
			break;
		}
	}
}

void MainGame::draw() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	glActiveTexture(GL_TEXTURE0);
	GLuint imageLocation = program.getUniformLocation("myImage");
	glUniform1i(imageLocation, 0);
	time += 0.0002f;
	GLuint timeLocation = program.getUniformLocation("delta");
	glUniform1f(timeLocation, time);
	sprite[1].draw();
	sprite[2].draw();
	program.unuse();
	SDL_GL_SwapWindow(window);
}

void MainGame::update()
{
	while (gameState == GameState::PLAY)
	{
		//dibujar pantalla y otros
		processInput();
		draw();
	}
}

MainGame::~MainGame()
{
}
