#pragma once

#include <cstdio>
#include <string>
#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>

#include "Scene.h"

class Scene;

class App {
public:
	static std::string windowTitle;
	static int screenWidth, screenHeight;
	static SDL_Window *window;
	static SDL_Surface *screenSurface;
	static SDL_Renderer *renderer;

	App(std::string windowTitle, int screenWidth, int screenHeight);
	~App();
	void Main();
	void SwitchScene(Scene *newScene);

private:
	const int FPS_LIMIT = 60;
	float fps, delta;
	Scene *scene;

	bool InitSDL();
	void CloseSDL();
	bool LoadMedia();
	void ReleaseMedia();
	void FPSControl();
	void Update();
};
