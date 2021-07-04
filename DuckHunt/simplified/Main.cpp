#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <iostream>
#include <SDL2/SDL.h>
#include "SDL_exception.h"
#include "Engine.h"

void main_loop()
{
	Engine::getEngine()->Update();
	Engine::getEngine()->Render();
}

int main(int argc, char *argv[])
{
	if (!Engine::getEngine()->Init())
		return -1;
	else
	{

#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop(main_loop, 0, 1);
		//emscripten_set_main_loop_timing(EM_TIMING_RAF, 1);
#endif
#ifndef __EMSCRIPTEN__
		while (Engine::getEngine()->isRunning())
			main_loop();
#endif
	}

#ifdef __EMSCRIPTEN__
	emscripten_cancel_main_loop();
#endif
	Engine::getEngine()->Clean();

	return 0;
}