#include "App.h"
#include "Resource.h"

App *App::app = NULL;
SDL_Window *App::window = NULL;
SDL_Surface *App::screenSurface = NULL;
SDL_Renderer *App::renderer = NULL;

App::App(std::string title, int screen_width, int screen_height) {
	app = this;
	app->screenWidth = screen_width;
	app->screenHeight = screen_height;
	app->InitSDL();
	app->LoadMedia();
}

App::~App() {
	app->ReleaseMedia();
	app->CloseSDL();
}

bool App::InitSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL could not initialize! Error: %s\n", SDL_GetError());
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) != 0) {
		printf("Image system could not initialize!\n");
		return false;
	}

	window = SDL_CreateWindow("Escape Fighting",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  screenWidth,
							  screenHeight,
							  SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		printf("SDL could not create window! Error: %s\n", SDL_GetError());
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, 0);

	return true;
}

bool App::LoadMedia() {
	bool suc = true;
	suc &= Resource::LoadImage("excalibur", "Assets/test.bmp");
	return suc;
}

void App::ReleaseMedia() {
	Resource::Release();
}

void App::CloseSDL() {
	SDL_DestroyWindow(window);
	SDL_FreeSurface(screenSurface);
	SDL_DestroyRenderer(renderer);

	window = nullptr;
	screenSurface = nullptr;
	renderer = nullptr;

	IMG_Quit();
	SDL_Quit();
}

void App::Main() {
	bool running = true;
	SDL_Event e;
	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_QUIT:
					running = false;
					break;
			}
		}
		if (curScene == NULL)
			continue;
		Update();
	}
}

void App::Update() {
	CalcFPS();
	if(fps>FPS_LIMIT)
	curScene->Update(fps);
	SDL_RenderPresent(renderer);
}

void App::SwitchScene(Scene *newScene) {
	if (app->curScene != NULL)
		app->curScene->OnExitScene();
	app->curScene = newScene;
	app->curScene->OnEnterScene();
}

void App::CalcFPS() {
	static int preClock = 0;
	int curClock = SDL_GetTicks();
	fps = 1000.0f / (curClock - preClock);
	preClock = curClock;
}
