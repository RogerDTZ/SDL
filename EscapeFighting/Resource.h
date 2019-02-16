#pragma once

#include <string>
#include <unordered_map>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>

#include "App.h"

struct Texture {
	float w, h;
	SDL_Texture *texture;

	Texture();
	Texture(float w, float h, SDL_Texture *texture);
	~Texture();
	void SetAlpha(Uint8 alpha);
	void Zoom(float a);
	void ZoomBy(int which, float newVal);
};


class Resource {
public:
	static bool LoadImage(std::string srcName, std::string srcPath);
	static Texture* GetImage(std::string srcName);
	static void Release();

private:
	static const int MAX_TEXTURE_NUM = 1000;
	static std::unordered_map<std::string, int> imgIndex;
	static Texture imgLib[MAX_TEXTURE_NUM];
	static int imgCnt;
};