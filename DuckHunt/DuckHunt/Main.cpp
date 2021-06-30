#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <iostream>
#include <SDL.h>
#include "exceptions/SDL_exception.h"
#include "ui/Engine.h"

void main_loop()
{
	Engine::getEngine()->Update();
}

int main(int argc, char* argv[]) {
	try {
		Engine::getEngine()->Init();
	}
	catch (SDL_exception& err) {
		std::cout << err.what() << std::endl;
	}

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop(), 0, 1);
#endif
#ifndef __EMSCRIPTEN__
	while (Engine::getEngine()->isRunning())
		main_loop();
#endif

	while (Engine::getEngine()->isRunning())
	{
		Engine::getEngine()->Update();
		Engine::getEngine()->Render();
	}

	Engine::getEngine()->Clean();
#ifdef __EMSCRIPTEN__
	emscripten_cancel_main_loop();
#endif

	return 0;
}