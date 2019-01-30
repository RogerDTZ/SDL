#pragma once

#include <cstdio>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Scene.h"
#include "TestScene.h"

class App {
public:
	static const int FPS_LIMIT = 60;
	int screenWidth;
	int screenHeight;
	Scene *curScene;
	static App *app;
	static SDL_Window *window;
	static SDL_Surface *screenSurface;
	static SDL_Renderer *renderer;

	App(std::string title, int screen_width, int screen_height);
	~App();

	bool InitSDL();
	bool LoadMedia();
	void ReleaseMedia();
	void CloseSDL();
	void Main();
	void Update();
	void SwitchScene(Scene *newScene);

private:
	float fps;
	void CalcFPS();
};
