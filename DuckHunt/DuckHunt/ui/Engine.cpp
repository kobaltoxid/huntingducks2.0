#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Engine.h"
#include "exceptions/SDL_exception.h"
#include <duck/Duck.h>
#include <player/Player.h>
#include <string>

const int WIDTH = 800, HEIGHT = 800;
const int DUCK_WIDTH = 100, DUCK_HEIGHT = 100;
int duck_pos_x = 350, duck_pos_y = 350;

std::string duck_img_path = "images/duck.png";
<<<<<<< Updated upstream

=======
std::string grass_img_path = "images/grass.png";
std::string background_img_path = "images/background.png";
>>>>>>> Stashed changes
Duck duck1(DUCK_WIDTH, DUCK_HEIGHT, duck_pos_x, duck_pos_y);
Player player;

SDL_Texture* duckTexture;
SDL_Texture* grassTexture;
SDL_Texture* backgroundTexture;
SDL_Rect* rect;
SDL_Rect bgRect = {0,0,800,800};
SDL_Rect grassRect = { 0, 600, 800, 200 };


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

	
	auto tmpSurface = IMG_Load(background_img_path.c_str());
	backgroundTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	SDL_RenderCopy(renderer, backgroundTexture, nullptr, &bgRect);

	rect = duck1.getRect();
	tmpSurface = IMG_Load(duck_img_path.c_str());
	duckTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	SDL_RenderCopy(renderer, duckTexture, nullptr, rect);

	tmpSurface = IMG_Load(grass_img_path.c_str());
	grassTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	SDL_RenderCopy(renderer, grassTexture, nullptr, &grassRect);

}

void Engine::Update() {

	duck1.move();
	rect = duck1.getRect();
	SDL_RenderCopy(renderer, backgroundTexture, nullptr, &bgRect);
	SDL_RenderCopy(renderer, duckTexture, nullptr, rect);
	SDL_RenderCopy(renderer, grassTexture, nullptr, &grassRect);
	//std::cout << "X: " << duck1.getX() << "Y: " << duck1.getY() << std::endl;
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
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

void Engine::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	player.eventHandler(event, rect);
	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_SPACE:
			duck1.die();
			break;
		case SDLK_s:
			duck1.spawn();
			break;
		default:
			break;
		}
	default:
		break;
	}

}