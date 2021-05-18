#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player {
private:
	Player() {}
	static Player* player;
	bool alive = 1;
	SDL_Rect gBox;
	int gWidth, gHeight = 10;
	int curX = 0;
	int curY = 0;
	int Score = 0;

public:
	static Player* getPlayer() {
		player = (player == NULL) ? new Player() : frog;
		return player;
	}
	void Shoot();
	void eventHandler(SDL_Event& event);
	int getScore();
	int getCurX();
	int getCurY();
	void resetScore();
	void incScore(int inc);
	bool die();
	bool isAlive();
};

#endif