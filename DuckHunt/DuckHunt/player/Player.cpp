#include <player/Player.h>
#include <bridge/bridge.h>
#include <duck/Duck.h>

#include <SDL.h>
#include <iostream>

Player::Player() {

}

Player::~Player() {

}

bool Player::Shoot(Duck &duck, SDL_Rect* scope) {
	if (Collision(duck.getRect(), scope)) {
		std::cout << "Success" << "\n";
		return true;
	}
	else {
		std::cout << "Failure" << "\n";
		return false;
	}
}

void Player::eventHandler(SDL_Event& event, Duck &duck, Duck& duck1) {
	if (event.type == SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_GetMouseState(&curX, &curY)) == SDL_BUTTON_LEFT) {
		this->gBox.x = curX;
		this->gBox.y = curY;
		if (Shoot(duck, this->getRect()))
		{
			duck.die();
		}
		if (Shoot(duck1, this->getRect()))
		{
			duck1.die();
		}
	}
}

int Player::getScore() {
	return Score;
}

void Player::resetScore() {
	Score = 0;
}

void Player::incScore(int inc) {
	Score += inc;
}

int Player::getCurX() {
	return curX;
}

int Player::getCurY() {
	return curY;
}

bool Player::die() {
	alive = 0;
	return alive;
}

bool Player::isAlive() {
	return alive;
}

SDL_Rect* Player::getRect() {
	return &gBox;
}




