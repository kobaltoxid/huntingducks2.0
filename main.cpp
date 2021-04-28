#include <iostream>
#include <SDL.h>
#include <Engine.h>

int main(int argc, char* argv[]) {
	Engine::getEngine()->Init();

	while (Engine::getEngine()->isRunning()) {
		Engine::getEngine()->Update();
	}
	Engine::getEngine()->Clean();
	return 0;
}