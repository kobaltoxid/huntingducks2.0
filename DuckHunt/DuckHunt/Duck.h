#pragma once
#ifndef DUCK_H
#define DUCK_H

#include <SDL.h>
#include <string>

class Duck {
public:
	Duck(int w, int h, int x, int y);
	//Duck(SDL_Renderer* renderer, int w, int h, int x, int y, const std::string& image_path);
	~Duck();
	//void draw(SDL_Renderer* renderer) const;
	void eventHandler(SDL_Event& event);
	bool die();
	bool isAlive();
	void move();
	int getX();
	int getY();
	SDL_Rect *getRect();

private:
	bool alive = 1;
	int _w, _h;
	int _x, _y;
	SDL_Rect img;
	//SDL_Texture* _duck_texture = nullptr;
};

#endif