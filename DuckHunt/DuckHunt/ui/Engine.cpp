#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Engine.h"
#include "exceptions/SDL_exception.h"
#include <Duck.h>

const int WIDTH = 800, HEIGHT = 800;
const int DUCK_WIDTH = 100, DUCK_HEIGHT = 100;
int duck_pos_x = 0, duck_pos_y = 0;
SDL_Texture* duckTexture;
SDL_Rect* rect;

Engine* Engine::engine = nullptr;

void Engine::Init() {
	SDL_Surface* windowSurface = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		throw SDL_exception("SDL could not initialize!");
		//std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
	}

	window = SDL_CreateWindow("Hunting Ducks 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	windowSurface = SDL_GetWindowSurface(window);


	//checks if the window was initialized properly
	if (window == nullptr)
	{
		throw SDL_exception("Could not create window!");
	}

	//checks if the renderer was initialized properly
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		throw SDL_exception("Could not create renderer!");
	}

	running = true;


	//Place to initialize objects
	Duck duck(DUCK_WIDTH, DUCK_HEIGHT, duck_pos_x, duck_pos_y);
	rect = duck.getRect();
	auto tmpSurface = IMG_Load("duck/duck1.png");
	duckTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	
}

void Engine::Update() {
	
	//duck.draw(renderer);
	//duck.move();
	
}

bool Engine::isRunning() {
	return running;
}

void Engine::Clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned." << std::endl;
}

void Engine::Render() 
{
	SDL_RenderClear(renderer);
	//Place to add stuff for rendering
	SDL_RenderCopy(renderer, duckTexture, nullptr, rect);
	SDL_RenderPresent(renderer);

}

void Engine::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event); 
	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	default:
		break;
	}
	
}