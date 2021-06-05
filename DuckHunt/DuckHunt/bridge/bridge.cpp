#include <SDL.h>
#include <iostream>

bool Collision(SDL_Rect* duck, SDL_Rect* scope) {
	SDL_Rect rect1 = *duck;
	SDL_Rect rect2 = *scope;


	if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h &&
		rect1.y + rect1.h > rect2.y) {
		std::cout << "Noice" << "\n";
		return true;
	}
	else
	{
		std::cout << "Fail" << "\n";
		return false;
	}
}