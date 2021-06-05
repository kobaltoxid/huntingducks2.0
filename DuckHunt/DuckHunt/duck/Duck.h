#pragma once
#ifndef DUCK_H
#define DUCK_H

#include <SDL.h>
#include <string>

class Duck {
public:
	Duck(int w, int h, int x, int y);
	~Duck();
	void eventHandler(SDL_Event& event);
	bool die();
	bool spawn();
	bool isAlive();
	void move();
	int getX();
	int getY();
	SDL_Rect *getRect();

private:
	bool alive;
	int _w, _h;
	int _x, _y;
	SDL_Rect img;
};

#endif