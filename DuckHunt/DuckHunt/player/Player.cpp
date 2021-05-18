#include <player/Player.h>

#include <SDL.h>
#include <iostream>

Player* Player::player = nullptr;

void Player::Shoot() {

}

void Player::eventHandler(SDL_Event& event) {
	if (event.type == SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_GetMouseState(curX&, curY&)) == SDL_BUTTON_LEFT) {

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




