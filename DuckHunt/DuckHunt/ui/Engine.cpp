#include <iostream>
#include <SDL.h>
#include <exceptions/SDL_exception.h>
#include <ui/Engine.h>

const int WIDTH = 640, HEIGHT = 640;

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
}