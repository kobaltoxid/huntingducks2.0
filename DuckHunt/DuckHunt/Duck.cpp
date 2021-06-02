#include "Duck.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

Duck::Duck(int w, int h, int x, int y): 
	_w(w), _h(h), _x(x), _y(y)
{
	img = { _x, _y, _w, _h };
}

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
	if (_x < 700 && _y < 700) {
		_x += 3;
		_y += 3;
	}
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