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

std::string grass_img_path = "images/grass.png";
std::string background_img_path = "images/background.png";

Duck duck1(DUCK_WIDTH, DUCK_HEIGHT, duck_pos_x, duck_pos_y);
Duck duck2(DUCK_WIDTH, DUCK_HEIGHT, duck_pos_x - 100, duck_pos_y-100);
Player player;

SDL_Texture* duckTexture;
SDL_Texture* grassTexture;
SDL_Texture* backgroundTexture;
SDL_Rect* rect;
SDL_Rect bgRect = {0,0,800,800};
SDL_Rect grassRect = { 0, 600, 800, 200 };


Engine* Engine::engine = nullptr;
void Engine::Init() {
	
	//srand(time(NULL));
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
	isGameStarted = false;
	
	auto tmpSurface = IMG_Load(background_img_path.c_str());
	backgroundTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load(duck_img_path.c_str());
	duckTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	tmpSurface = IMG_Load(grass_img_path.c_str());
	grassTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

}

void Engine::Update() {
	std::cout << isGameStarted << std::endl;
	if (isGameStarted == false) {
		//render menu bckgrnd
		handleOnMenu();
	}
	else {
		SDL_RenderCopy(renderer, backgroundTexture, nullptr, &bgRect);
		if (gameA == true) {
			srand((unsigned)(time(0)));
			duck1.move();
			rect = duck1.getRect();
			SDL_RenderCopy(renderer, duckTexture, nullptr, rect);
		}
		else if (gameB == true) {
			srand((unsigned)(time(0)));
			duck1.move();
			rect = duck1.getRect();
			SDL_RenderCopy(renderer, duckTexture, nullptr, rect);

			srand((unsigned)(time(0) + 47));
			duck2.move();
			rect = duck2.getRect();
			SDL_RenderCopy(renderer, duckTexture, nullptr, rect);
		}
		SDL_RenderCopy(renderer, grassTexture, nullptr, &grassRect);
	}


	
	//std::cout << "X: " << duck1.getX() << "Y: " << duck1.getY() << std::endl
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


void Engine::handleOnMenu() {
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			std::cout << "in A" << std::endl;
			gameA = true;
			isGameStarted = true;
			break;
		case SDLK_b:
			std::cout << "in B" << std::endl;
			gameB = true;
			isGameStarted = true;
			break;
		}
	}
	else if (event.type == SDL_QUIT) running = false;
}

void Engine::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	player.eventHandler(event, duck1, duck2);
	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		/*case SDLK_SPACE:
			duck1.die();
			break;*/
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