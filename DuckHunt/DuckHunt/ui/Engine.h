#ifndef ENGINE_H
#define ENGINE_H

class Engine {
private:
	Engine(){}
	static Engine *engine;

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
};


#endif //ENGINE_H
