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
};


class Resource {
public:
	static bool LoadImage(std::string srcName, std::string srcPath);
	static Texture *GetImage(std::string srcName);
	static void Release();
	static void RenderTexture(Texture *texture,float x,float y);

private:
	static std::unordered_map<std::string, Texture*> imgLib;
};