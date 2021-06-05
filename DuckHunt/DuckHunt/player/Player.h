#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <duck/Duck.h>

class Player {
private:
	static Player* player;
	bool alive = 1;
	SDL_Rect gBox;
	int gWidth, gHeight = 40;
	int curX = 0;
	int curY = 0;
	int Score = 0;

public:
	Player();
	~Player();
	bool Shoot(Duck &duck, SDL_Rect* scope);
	void eventHandler(SDL_Event& event, Duck &duck);
	int getScore();
	int getCurX();
	int getCurY();
	void resetScore();
	void incScore(int inc);
	bool die();
	bool isAlive();
	SDL_Rect* getRect();
};

#endif