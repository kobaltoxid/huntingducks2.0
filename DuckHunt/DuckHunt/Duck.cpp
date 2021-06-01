#include "Duck.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h> 
#include <iostream>
#include <string>

Duck::Duck(int w, int h, int x, int y): 
	_w(w), _h(h), _x(x), _y(y)
{
	img = { _x, _y, _w, _h };
}
//
//Duck::Duck(SDL_Renderer* renderer, int w, int h, int x, int y, const std::string& image_path) :
//	_w(w), _h(h), _x(x), _y(y)
//{
//	auto surface = IMG_Load(image_path.c_str());
//	if (!surface) {
//		std::cerr << "Failed to create surface.\n";
//	}
//
//	_duck_texture = SDL_CreateTextureFromSurface(renderer, surface);
//
//	if (!_duck_texture) {
//		std::cerr << "Failed to create texture.\n";
//	}
//	SDL_FreeSurface(surface);
//}

Duck::~Duck() {
	
}

//void Duck::draw(SDL_Renderer* renderer) const {
//	SDL_Rect img = { _x, _y, _w, _h };
//	SDL_RenderCopy(renderer, _duck_texture, NULL, &img);
//}

void Duck::move() {
	srand(time(NULL));
	int dir = rand() % 8 + 1;
	int distance = rand() % 3 + 3;
	switch (dir)
	{
	case 1:
		_y -= distance;
		break;
	case 2:
		_x += distance;
		_y -= distance;
		break;
	case 3:
		_x += distance;
		break;
	case 4:
		_x += distance;
		_y += distance;
		break;
	case 5:
		_y += distance;
		break;
	case 6:
		_x -= distance;
		_y += distance;
		break;
	case 7:
		_x -= distance;
		break;
	case 8:
		_x -= distance;
		_y -= distance;
		break;
	default:
		break;
	}

	img = { _x, _y, _w, _h };
}

int Duck::getX() {
	return _x;
}

int Duck::getY() {
	return _y;
}

bool Duck::isAlive(){
	return alive;
}

bool Duck::die() {

	alive = 0;

	return alive;
}

SDL_Rect* Duck::getRect() {
	return &img;
}