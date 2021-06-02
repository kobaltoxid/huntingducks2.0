#include <player/Player.h>
#include <bridge/bridge.h>

#include <SDL.h>
#include <iostream>

Player::Player() {

}

Player::~Player() {

}

bool Player::Shoot(SDL_Rect* duck, SDL_Rect* scope) {
	if (Collision(duck, scope)) {
		std::cout << "Success" << "\n";
		return true;
	}
	else {
		std::cout << "Failure" << "\n";
		return false;
	}
}

void Player::eventHandler(SDL_Event& event, SDL_Rect* duck) {
	if (event.type == SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_GetMouseState(&curX, &curY)) == SDL_BUTTON_LEFT) {
		this->gBox.x = curX;
		this->gBox.y = curY;
		Shoot(duck, this->getRect());
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




