#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <Enemy.h>
#include <vector>

class Engine {
private:
	Engine(){}

	int lives = 5;
	int timer;
	int startTime = 0;
	int count = 0;
	//bool once = false;
	int count1 = 0;
	int check = 13;
	int highestScore = 0;
	bool started = false;
	bool running;
	Mix_Music* gmusic = NULL;
	Mix_Music* imusic = NULL;
	SDL_Window* window;
	SDL_Renderer* renderer;
	static Engine* engine;
	std::vector<int> safe;

	SDL_Rect EnemySprite[3];
	SDL_Rect Message_rect;
	SDL_Rect Lives_rect;
	SDL_Rect Timer_rect;
	SDL_Rect Score_rect;
	SDL_Rect Restart_rect;
	TTF_Font* Langar;
	SDL_Surface* surfaceMessage;
	SDL_Texture* Message;

	std::vector<Enemy> enemies;
public:
	static Engine* getEngine() {
		engine = (engine == NULL) ? new Engine() : engine;
		return engine;
	}
	bool isRunning();
	SDL_Renderer* getRenderer();
	bool Init();
	void Update();

	void RenderBG(int x, int y, std::string item, int width, int height);
	void Render(int x, int y, std::string item, int width, int height, std::string type);
	void TextDraw(char choice);
	void printHS();

	void startEvent();
	void Events();
	void finalEvent();

	bool Collision(SDL_Rect a, SDL_Rect a0);
	
	void reset();
	void Clean();
};

#endif //ENGINE_H