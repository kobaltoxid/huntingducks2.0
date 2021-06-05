#ifndef ENGINE_H
#define ENGINE_H

#include <duck/Duck.h>
#include <string>
#include <SDL.h>

class Engine {
private:
	Engine() {}
	~Engine();

	static Engine* engine;

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool running;
public:
	static Engine* getEngine() {
		engine = (engine == nullptr) ? new Engine() : engine;
		return engine;
	}

	void Init();
	void Update();	
	bool isRunning();
	void Clean();
	void Render();
	void handleEvents();
	void spawnDuck(SDL_Rect* rect, SDL_Renderer* renderer);
};


#endif //ENGINE_H

