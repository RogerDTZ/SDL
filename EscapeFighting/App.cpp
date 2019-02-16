#include "App.h"
#include "Renderer.h"
#include "Resource.h"

std::string App::windowTitle = "";
int App::screenHeight = 0;
int App::screenWidth = 0;
SDL_Window *App::window = NULL;
SDL_Surface *App::screenSurface = NULL;
SDL_Renderer *App::renderer = NULL;

App::App(std::string windowTitle, int screenWidth, int screenHeight) {
	this->windowTitle = windowTitle;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	if (this->InitSDL() == false)
		exit(0);
	if (this->LoadMedia() == false)
		exit(0);
	Renderer::SetCamPos(screenWidth / 2, screenHeight / 2, screenWidth, screenHeight);
}

App::~App() {
	this->ReleaseMedia();
	this->CloseSDL();
}

bool App::InitSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL could not initialize! Error: %s\n", SDL_GetError());
		return false;
	}
	int img_init_flag = IMG_INIT_PNG | IMG_INIT_JPG;
	if (IMG_Init(img_init_flag) != img_init_flag) {
		printf("Image system could not initialize!\n");
		return false;
	}
	if (TTF_Init() == -1) {
		printf("Font system could not initialize!\n");
		return false;
	}
	window = SDL_CreateWindow(windowTitle.c_str(),
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
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	return true;
}

void App::CloseSDL() {
	SDL_DestroyWindow(window);
	SDL_FreeSurface(screenSurface);
	SDL_DestroyRenderer(renderer);

	window = nullptr;
	screenSurface = nullptr;
	renderer = nullptr;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool App::LoadMedia() {
	bool suc = true;
	suc &= Resource::LoadImage("excalibur", "Assets/alpha.png");
	if (suc == false) {
		fprintf(stderr, "Loading Images Error");
		return false;
	}
	return true;
}

void App::ReleaseMedia() {
	Resource::Release();
}

void App::Main() {
	SDL_Event e;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_MOUSEWHEEL:
					if (e.wheel.y > 0) {
						Renderer::ZoomCam(0.8f);
					}
					if (e.wheel.y < 0) {
						Renderer::ZoomCam(1.25f);
					}
			}
		}
		Update();
	}
}


void App::Update() {
	FPSControl();
	printf("%.2f\n", fps);
	Renderer::Clear();
	if (scene != NULL)
		scene->Update(delta);
	char fpsmsg[] = "FPS: xx.xx";
	sprintf_s(fpsmsg, "FPS: %.2lf", fps);
	Renderer::SetColor(255, 255, 255);
	Renderer::DrawFont(fpsmsg, 0, 0);
	SDL_RenderPresent(renderer);
}

void App::SwitchScene(Scene *newScene) {
	if (this->scene != NULL)
		this->scene->OnExitScene();
	this->scene = newScene;
	this->scene->OnEnterScene();
}

void App::FPSControl() {
	static Uint32 preClock = 0, nowClock;
	nowClock = SDL_GetTicks();
	if (nowClock - preClock < 16) {
		SDL_Delay(16 - (nowClock - preClock));
		nowClock = SDL_GetTicks();
	}
	fps = std::min(60.0f, 1000.0f / (nowClock - preClock));
	delta = float(nowClock - preClock) / 1000.0f;
	preClock = nowClock;
}
