#ifndef ENGINE_H
#define ENGINE_H

#include <duck/Duck.h>
#include <string>
#include <SDL.h>
#include <map>

class Engine {
private:
	Engine() {}
	~Engine();

	static Engine* engine;

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool running;
	bool isGameStarted;
	bool gameA = false, gameB = false;
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
	void handleOnMenu();
	void handleInGameEvents();
	void spawnDuck(SDL_Rect* rect, SDL_Renderer* renderer);
	void renderAmmo();
	void renderFenixesOnXPos(int xPos, int count, char game);
	void renderFenixesGameB();
	void renderFenixesGameA();
	void renderScore();
	void clearFenixMap();
	void cleanupBetweenGames();
	void cleanupBetweenLevels();
	void timer();
};


#endif //ENGINE_H

