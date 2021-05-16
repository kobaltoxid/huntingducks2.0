#include <iostream>
#include <SDL.h>
#include <SDL_exception.h>
#include <Engine.h>

int main(int argc, char* argv[]) {
	try {
		Engine::getEngine()->Init();
	}
	catch (SDL_exception& err) {
		std::cout << err.what() << std::endl;
	}

	return 0;
}