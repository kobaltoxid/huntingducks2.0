#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <iostream>
#include <SDL.h>
#include "SDL_exception.h"
#include "Engine.h"

void main_loop()
{
	Engine::getEngine()->Update();
	Engine::getEngine()->Render();
}

int main(int argc, char *argv[])
{
	try
	{
		Engine::getEngine()->Init();
	}
	catch (SDL_exception &err)
	{
		std::cout << err.what() << std::endl;
	}

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(main_loop, 0, 1);
#endif
#ifndef __EMSCRIPTEN__
	while (Engine::getEngine()->isRunning())
		main_loop();
#endif

#ifdef __EMSCRIPTEN__
	emscripten_cancel_main_loop();
#endif
	Engine::getEngine()->Clean();

	return 0;
}