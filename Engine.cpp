#include <iostream>
#include <SDL.h>
#include <Engine.h>
#include <Texture.h>
#include <Frog.h>
#include <string>

const int WIDTH = 640, HEIGHT = 640;

Engine* Engine::engine = nullptr;

bool Engine::Init() {
	SDL_Surface* windowSurface = NULL;
		
	//checks if SDL was initialized
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//initializes the window
	window = SDL_CreateWindow("Hunting Ducks 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	windowSurface = SDL_GetWindowSurface(window);

	//checks if the window was initialized properly
	if (window == nullptr)
	{
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return false;
	}

	//checks if the renderer was initialized properly
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "Could not create renderer" << SDL_GetError() << std::endl;
		return false;
	}

	if (Mix_OpenAudio(44100, AUDIO_F32MSB , 2, 2048) < 0)
	{
		std::cout<<("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError()) <<std::endl;
	}

	//checks if the library for drawing text was initialized
	if (TTF_Init() < 0) {
		std::cout<<"Failed to initialize SDL_TTF library" << std::endl;
	}

	//loads the font file
	Langar = TTF_OpenFont("Font/Langar-Regular.ttf", 25);
	if (Langar == NULL) std::cout << TTF_GetError() << std::endl;

	imusic = Mix_LoadMUS("Assets_frog_cars_bckgrd/Music/Intro_16.wav");
	if (imusic == NULL)
	{
		std::cout<<("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError())<<std::endl;
	}

	gmusic = Mix_LoadMUS("Assets_frog_cars_bckgrd/Music/Level_16.wav");
	if (gmusic == NULL)
	{
		std::cout << ("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError()) << std::endl;
	}

	//initializes the properties of SDL_Rect for displaying the in-game score
	Message_rect.x = 10;  
	Message_rect.y = 580; 
	Message_rect.w = 100; 
	Message_rect.h = 40;

	//initializes the properties of SDL_Rect for displaying the lives
	Lives_rect.x = 530;
	Lives_rect.y = 580;
	Lives_rect.w = 100;
	Lives_rect.h = 40;

	//initializes the properties of SDL_Rect for displaying the timer
	Timer_rect.x = 220;
	Timer_rect.y = 0;
	Timer_rect.w = 200;
	Timer_rect.h = 25;

	//initializes the properties of SDL_Rect for displaying the end-game score
	Score_rect.x = 220;
	Score_rect.y = 340;
	Score_rect.w = 200;
	Score_rect.h = 50;

	//initializes the properties of SDL_Rect for displaying the restart prompt
	Restart_rect.x = 180;
	Restart_rect.y = 490;
	Restart_rect.w = 300;
	Restart_rect.h = 50;

	//loading textures
	/*Texture::getTexture()->Load("Background_ver1", "Assets_frog_cars_bckgrd/Background_ver1.png");
	Texture::getTexture()->Load("Lose_background", "Assets_frog_cars_bckgrd/youlose_game.png");
	Texture::getTexture()->Load("Win_background", "Assets_frog_cars_bckgrd/Youwin_screen.png");
	Texture::getTexture()->Load("Frog_front", "Assets_frog_cars_bckgrd/Frogger_front.png");
	Texture::getTexture()->Load("Ambulance", "Assets_frog_cars_bckgrd/ambulance_car_t1.png");
	Texture::getTexture()->Load("Fire_car", "Assets_frog_cars_bckgrd/fire_car_t.png");
	Texture::getTexture()->Load("Taxi", "Assets_frog_cars_bckgrd/taxi_car_t.png");
	Texture::getTexture()->Load("Lambo_car", "Assets_frog_cars_bckgrd/lambo_car_t.png");
	Texture::getTexture()->Load("Police_car", "Assets_frog_cars_bckgrd/police_car_t.png");
	Texture::getTexture()->Load("Normal_car", "Assets_frog_cars_bckgrd/normal_car_t.png");
	Texture::getTexture()->Load("Jeep_bus", "Assets_frog_cars_bckgrd/jeep_bus_t.png");
	Texture::getTexture()->Load("White_bus", "Assets_frog_cars_bckgrd/white_bus_t.png");
	Texture::getTexture()->Load("Brown_car", "Assets_frog_cars_bckgrd/brown_car_t.png");
	Texture::getTexture()->Load("Short_log", "Assets_frog_cars_bckgrd/short_log.png");
	Texture::getTexture()->Load("Long_log", "Assets_frog_cars_bckgrd/long_log.png");
	Texture::getTexture()->Load("Turtle", "Assets_frog_cars_bckgrd/turtle.png");
	Texture::getTexture()->Load("11", "Assets_frog_cars_bckgrd/Pixel Animation components/0.png");
	Texture::getTexture()->Load("10", "Assets_frog_cars_bckgrd/Pixel Animation components/1.png");
	Texture::getTexture()->Load("9", "Assets_frog_cars_bckgrd/Pixel Animation components/2.png");
	Texture::getTexture()->Load("8", "Assets_frog_cars_bckgrd/Pixel Animation components/3.png");
	Texture::getTexture()->Load("7", "Assets_frog_cars_bckgrd/Pixel Animation components/4.png");
	Texture::getTexture()->Load("6", "Assets_frog_cars_bckgrd/Pixel Animation components/5.png");
	Texture::getTexture()->Load("5", "Assets_frog_cars_bckgrd/Pixel Animation components/6.png");
	Texture::getTexture()->Load("4", "Assets_frog_cars_bckgrd/Pixel Animation components/7.png");
	Texture::getTexture()->Load("3", "Assets_frog_cars_bckgrd/Pixel Animation components/8.png");
	Texture::getTexture()->Load("2", "Assets_frog_cars_bckgrd/Pixel Animation components/9.png");
	Texture::getTexture()->Load("1", "Assets_frog_cars_bckgrd/Pixel Animation components/10.png");
	Texture::getTexture()->Load("0", "Assets_frog_cars_bckgrd/Pixel Animation components/11.png");
	Texture::getTexture()->Load("press", "Assets_frog_cars_bckgrd/Press_key components/1.png");
	Texture::getTexture()->Load("no_press", "Assets_frog_cars_bckgrd/Press_key components/2.png");
	Texture::getTexture()->Load("Logo", "Assets_frog_cars_bckgrd/Logo.png");
	Texture::getTexture()->Load("Frog_l", "Assets_frog_cars_bckgrd/frogger_left_up.png");
	Texture::getTexture()->Load("Frog_r", "Assets_frog_cars_bckgrd/frogger_right_up.png");*/

	int j = 1;
	int wid = EnemySprite[0].w;

	//creating the enemy objects, setting their properties (based on whether they're a car or a log)
	//and adding them to a vector of enemies
	for (int i = 0; i < 21; i++) {
		Enemy a;
		if (i % 2 == 0) a.setDir("r");
		else a.setDir("l");

		if (i == 11) wid = EnemySprite[1].w;
		if(i==9 || i==14 || i==18) a.setWid(EnemySprite[0].w);
		else if(i==10 || i==17 || i==19) a.setWid(EnemySprite[2].w);
		else a.setWid(wid);

		if (i == 0) a.setVelocity(15);
		else if (i < 3) a.setVelocity(5);
		else if (i < 5) a.setVelocity(10);
		else if (i < 7) a.setVelocity(5);
		else if (i < 9) a.setVelocity(10);
		else if (i < 11)a.setVelocity(2);
		else if (i == 11)a.setVelocity(3);
		else if (i < 14)a.setVelocity(2);
		else if (i == 14)a.setVelocity(3);
		else if (i < 17)a.setVelocity(2);
		else if (i == 17)a.setVelocity(3);
		else if (i < 20)a.setVelocity(2);
		else a.setVelocity(3);

		enemies.push_back(a);
	}

	//if running is true the application continues running
	running = true;
	return running;
}

//---------------------------------------------------------------------------------
//checks whether the application is still running
bool Engine::isRunning() {
	return running;
}

//---------------------------------------------------------------------------------

//updates the game cycle until the game stops running
void Engine::Update() {
	if (started == false) {
		if (Mix_PlayingMusic() == 0)
		{
			//Play intro music
			Mix_PlayMusic(imusic, -1);
		}
		SDL_RenderClear(renderer);
		//Render the background and Logo for the Menu screen
		RenderBG(0, 0, "Background_ver1", 1920, 2863);
		Render(150, 100, "Logo", 3500, 1500, "none");

		int s = check;
		int i = 0;
		while (check > -5000) {
			startEvent();
			if (running == false) break;
			if (started == true) break;

			check = 14 - SDL_GetTicks()/500;
			//checks if a second has passed
			if (check < s) { 
				//runs 12 times for every png of the "pixel version" gif
				if(check > 0) Render(190, 240, std::to_string(i), 2600, 584, "none");

				//changes the "press any key to start" image every second
				if (count1 % 2 == 0) Render(150, 456, "press", 3500, 300, "none");
				else Render(150, 456, "no_press", 3500, 300, "none");
				count1++;

				SDL_RenderPresent(getRenderer());

				s = check;
				i++;
			}
		}
		startEvent();
		//stops refreshing images if 83 minutes have passed
		Render(190, 240, "11", 2600, 584, "none");
		Render(150, 456, "press", 3500, 300, "none");
		SDL_RenderPresent(getRenderer());
		Mix_FreeMusic(imusic);
		imusic = NULL;
	}
	else {
		Events();
		SDL_RenderClear(renderer);
		if (Mix_PlayingMusic() == 0)
		{
			//Play in-game music
			Mix_PlayMusic(gmusic, -1);
		}
		safe = Frog::getFrog()->getSafe();

		//if all fives zones are reached it displays the win screen
		if (safe.size() == 5) {
			RenderBG(0, 0, "Win_background", 1920, 2863);
			printHS();
			SDL_RenderPresent(getRenderer());
			finalEvent();
		}

		//if the player dies 5 times or the timer reaches zero, the lose screen is displayed
		else if (lives == 0 || timer == 0) {
			RenderBG(0, 0, "Lose_background", 1920, 2863);
			printHS();
			SDL_RenderPresent(getRenderer());
			finalEvent();
		}

		else {
			timer = startTime + 220 - SDL_GetTicks() / 1000;
			//counter for the second wave of cars and logs
			count += 5;

			//rendering of the background, texts, cars, logs and turtles
			RenderBG(0, 0, "Background_ver1", 1920, 2863);

			surfaceMessage = TTF_RenderText_Solid(Langar, ("Score: " + std::to_string(Frog::getFrog()->getScore())).c_str(), { 26,26,26 });
			TextDraw('m');

			surfaceMessage = TTF_RenderText_Solid(Langar, ("Lives: " + std::to_string(lives)).c_str(), { 26,26,26 });
			TextDraw('l');

			surfaceMessage = TTF_RenderText_Solid(Langar, ("Time:       " + std::to_string(timer) + "s").c_str(), { 26,26,26 });
			TextDraw('t');

			Render(enemies[0].getPosX(), enemies[0].setPosY(544), "Lambo_car", EnemySprite[0].w, EnemySprite[0].h, "none");
			Render(enemies[1].getPosX(), enemies[1].setPosY(500), "Police_car", EnemySprite[0].w, EnemySprite[0].h, "flip");
			Render(enemies[2].getPosX(), enemies[2].setPosY(456), "Taxi", EnemySprite[0].w, EnemySprite[0].h, "none");
			Render(enemies[3].getPosX(), enemies[3].setPosY(412), "Fire_car", EnemySprite[0].w, EnemySprite[0].h, "flip");
			Render(enemies[4].getPosX(), enemies[4].setPosY(368), "Ambulance", EnemySprite[0].w, EnemySprite[0].h, "none");

			Render(enemies[5].getPosX(), enemies[5].setPosY(500), "Jeep_bus", EnemySprite[0].w, EnemySprite[0].h, "flip");
			Render(enemies[6].getPosX(), enemies[6].setPosY(456), "Normal_car", EnemySprite[0].w, EnemySprite[0].h, "none");
			Render(enemies[7].getPosX(), enemies[7].setPosY(412), "Brown_car", EnemySprite[0].w, EnemySprite[0].h, "flip");
			Render(enemies[8].getPosX(), enemies[8].setPosY(368), "White_bus", EnemySprite[0].w, EnemySprite[0].h, "none");

			Render(enemies[9].getPosX(), enemies[9].setPosY(260), "Turtle", EnemySprite[0].w + 150, EnemySprite[0].h + 200, "flip");
			Render(enemies[10].getPosX(), enemies[10].setPosY(235), "Long_log", EnemySprite[2].w, EnemySprite[0].h, "none");
			Render(enemies[11].getPosX(), enemies[11].setPosY(202), "Short_log", EnemySprite[1].w, EnemySprite[0].h, "none");
			Render(enemies[12].getPosX(), enemies[12].setPosY(160), "Short_log", EnemySprite[1].w, EnemySprite[0].h, "none");
			Render(enemies[13].getPosX(), enemies[13].setPosY(114), "Short_log", EnemySprite[1].w, EnemySprite[0].h, "none");
			Render(enemies[14].getPosX(), enemies[14].setPosY(65), "Turtle", EnemySprite[0].w + 150, EnemySprite[0].h + 200, "none");

			Render(enemies[15].getPosX(), enemies[15].setPosY(285), "Short_log", EnemySprite[1].w, EnemySprite[0].h, "none");
			Render(enemies[16].getPosX(), enemies[16].setPosY(235), "Short_log", EnemySprite[1].w, EnemySprite[0].h, "none");
			Render(enemies[17].getPosX(), enemies[17].setPosY(202), "Long_log", EnemySprite[2].w, EnemySprite[0].h, "none");
			Render(enemies[18].getPosX(), enemies[18].setPosY(150), "Turtle", EnemySprite[0].w + 150, EnemySprite[0].h + 200, "none");
			Render(enemies[19].getPosX(), enemies[19].setPosY(114), "Long_log", EnemySprite[2].w, EnemySprite[0].h, "none");
			Render(enemies[20].getPosX(), enemies[20].setPosY(70), "Short_log", EnemySprite[1].w, EnemySprite[0].h, "none");

			//if the frog is moved change the asset
			if(Frog::getFrog()->getFrame() % 2 == 0) Render(Frog::getFrog()->getPosX(), Frog::getFrog()->getPosY(), "Frog_l", 512, 512, "none");
			else Render(Frog::getFrog()->getPosX(), Frog::getFrog()->getPosY(), "Frog_r", 512, 512, "none");
			
			/*//display frog's collision bounding box	
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderDrawPoint(renderer, enemies[18].getBox().x, enemies[18].getBox().y);
			SDL_RenderDrawPoint(renderer, enemies[18].getBox().x + enemies[18].getBox().w, enemies[18].getBox().y);*/

			//if a safe zone is reached in a previous cycle it renders a frog on that position
			for (int i = 0; i < safe.size(); i++) {
				Render(safe[i] + 10, 4, "Frog_front", 512, 512, "none");
			}

			//checks if there is a collision with a car or log on the specified Y coord
			switch (Frog::getFrog()->getPosY())
			{
			case 532:
				if (Collision(Frog::getFrog()->getBox(), enemies[0].getBox())) {
					Frog::getFrog()->begin();
					lives--;
				}
				break;
			case 488:
				if (Collision(Frog::getFrog()->getBox(), enemies[1].getBox()) || Collision(Frog::getFrog()->getBox(), enemies[5].getBox())) {
					Frog::getFrog()->begin();
					lives--;
				}
				break;
			case 444:
				if (Collision(Frog::getFrog()->getBox(), enemies[2].getBox()) || Collision(Frog::getFrog()->getBox(), enemies[6].getBox())) {
					Frog::getFrog()->begin();
					lives--;
				}
				break;
			case 400:
				if (Collision(Frog::getFrog()->getBox(), enemies[3].getBox()) || Collision(Frog::getFrog()->getBox(), enemies[7].getBox())) {
					Frog::getFrog()->begin();
					lives--;
				}
				break;
			case 356:
				if (Collision(Frog::getFrog()->getBox(), enemies[4].getBox()) || Collision(Frog::getFrog()->getBox(), enemies[8].getBox())) {
					Frog::getFrog()->begin();
					lives--;
				}
				break;
			case 268:
				if (Collision(Frog::getFrog()->getBox(), enemies[9].getBox()) || Collision(Frog::getFrog()->getBox(), enemies[15].getBox())) {
					Frog::getFrog()->setPosX(-2);
				}
				else {
					Frog::getFrog()->begin();
					lives--;
				}
				break;
			case 224:
				if (Collision(Frog::getFrog()->getBox(), enemies[10].getBox()) || Collision(Frog::getFrog()->getBox(), enemies[16].getBox())) {
					Frog::getFrog()->setPosX(2);
				}
				else {
					Frog::getFrog()->begin();
					lives--;
				}
				break;
			case 180:
				if (Collision(Frog::getFrog()->getBox(), enemies[11].getBox()) || Collision(Frog::getFrog()->getBox(), enemies[17].getBox())) {
					Frog::getFrog()->setPosX(-3);
				}
				else {
					Frog::getFrog()->begin();
					lives--;
				}
				break;
			case 136:
				if (Collision(Frog::getFrog()->getBox(), enemies[12].getBox()) || Collision(Frog::getFrog()->getBox(), enemies[18].getBox())) {
					Frog::getFrog()->setPosX(2);
				}
				else {
					Frog::getFrog()->begin();
					lives--;
				}
				break;
			case 92:
				if (Collision(Frog::getFrog()->getBox(), enemies[13].getBox()) || Collision(Frog::getFrog()->getBox(), enemies[19].getBox())) {
					Frog::getFrog()->setPosX(-2);
				}
				else {
					Frog::getFrog()->begin();
					lives--;
				}
				break;
			case 48:
				if (Collision(Frog::getFrog()->getBox(), enemies[14].getBox()) || Collision(Frog::getFrog()->getBox(), enemies[20].getBox())) {
					Frog::getFrog()->setPosX(3);
				}
				else {
					Frog::getFrog()->begin();
					lives--;
				}
				break; 
			//if a safe zone is reached it resets the frog position
			case 4:
				Frog::getFrog()->begin();
				Frog::getFrog()->setHighest();
				break;
			}

			SDL_RenderPresent(getRenderer());

			//checks if the frog is on a log and it's still in the visible boundaries
			if (Frog::getFrog()->getPosX() < -34 || Frog::getFrog()->getPosX() > 606) {
				Frog::getFrog()->begin();
				lives--;
			}
		}
	}
}

//---------------------------------------------------------------------------------

//render background
void Engine::RenderBG(int x, int y, std::string item, int width, int height) {
	SDL_Rect rectBox = { x, y, WIDTH, HEIGHT };
	Texture::getTexture()->Draw(item, 0, 0, width, height, rectBox, "none");
}

//render assets
void Engine::Render(int x, int y, std::string item, int width, int height, std::string type) {
	SDL_Rect rectBox = { x, y, width/10, height/10};
	Texture::getTexture()->Draw(item, 0, 0, width, height, rectBox, type);
}

//return renderer
SDL_Renderer* Engine::getRenderer() {
	return renderer;
}

//---------------------------------------------------------------------------------

//draw text on screen
void Engine::TextDraw(char choice) {
	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	switch (choice)
	{
	//render score in-game
	case 'm':
		SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
		break;
	//render lives left
	case 'l':
		SDL_RenderCopy(renderer, Message, NULL, &Lives_rect);
		break;
	//render timer
	case 't':
		SDL_RenderCopy(renderer, Message, NULL, &Timer_rect);
		break;
	//render end-game score
	case 's':
		SDL_RenderCopy(renderer, Message, NULL, &Score_rect);
		break;
	//reneder restart prompt
	case 'r':
		SDL_RenderCopy(renderer, Message, NULL, &Restart_rect);
		break;
	}

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	Message = nullptr;
}

//print the highest score and restart option
void Engine::printHS() {
	if (highestScore < Frog::getFrog()->getScore()) highestScore = Frog::getFrog()->getScore();
	surfaceMessage = TTF_RenderText_Solid(Langar, ("Highest Score: " + std::to_string(highestScore)).c_str(), { 200,200,200 });
	TextDraw('s');
	surfaceMessage = TTF_RenderText_Solid(Langar, "Press 'r' to restart", { 200,200,200 });
	TextDraw('r');
}

//---------------------------------------------------------------------------------

//checks whether a button is pressed while on menu screen
void Engine::startEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);
	//if a key is pressed start the game
	if (event.type == SDL_KEYDOWN) started = true;
	else if (event.type == SDL_QUIT) running = false;
}

//handles all events
void Engine::Events() {
	SDL_Event event;
	SDL_PollEvent(&event);
	Frog::getFrog()->eventHandler(event);
	
	enemies[0].eventHandler();
	enemies[1].eventHandler();
	enemies[2].eventHandler();
	enemies[3].eventHandler();
	enemies[4].eventHandler();
	
	enemies[9].eventHandler();
	enemies[10].eventHandler();
	enemies[11].eventHandler();
	enemies[12].eventHandler();
	enemies[13].eventHandler();
	enemies[14].eventHandler();
	
	
	if (count >= 600) {
		enemies[5].eventHandler();
		enemies[6].eventHandler();
		enemies[7].eventHandler();
		enemies[8].eventHandler();
	}

	if (count >= 1000) {
		enemies[15].eventHandler();
		enemies[16].eventHandler();
		enemies[17].eventHandler();
		enemies[18].eventHandler();
		enemies[19].eventHandler();
		enemies[20].eventHandler();
	}

	if (event.type == SDL_QUIT) running = false;
}

//checks if the restart button is pressed on end screen
void Engine::finalEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);
	//if "r" is pressed restart the game
	if (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_r)) reset();
}

//---------------------------------------------------------------------------------

//checks for collision bethween the player and an enemy
bool Engine::Collision(SDL_Rect a, SDL_Rect b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB){
		return false;
	}

	if (topA >= bottomB){
		return false;
	}

	if (rightA <= leftB){
		return false;
	}

	if (leftA >= rightB){
		return false;
	}

	return true;
}

//---------------------------------------------------------------------------------

//resets values after restarting game
void Engine::reset() {
	safe.clear();
	std::cout << safe.size() << std::endl;
	count = 0;
	lives = 5;
	timer = 1;
	startTime = SDL_GetTicks() / 1000;
	Frog::getFrog()->setHighest();
	Frog::getFrog()->begin();
	Frog::getFrog()->resetScore();
	Frog::getFrog()->clearZone();
	for (int i = 0; i < 21; i++) {
		if (i % 2 == 0)
			enemies[i].setPosX(-220);
		else
			enemies[i].setPosX(860);
	}
}

//freeing space
void Engine::Clean() {
	Texture::getTexture()->Clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//Mix_FreeMusic(imusic);
	Mix_FreeMusic(gmusic);
	//imusic = NULL;
	gmusic = NULL;
	IMG_Quit();
	SDL_Quit();
}