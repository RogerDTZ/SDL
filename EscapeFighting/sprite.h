#pragma once

#include <SDL.h>

class Sprite {
public:
	float x, y;
	float rotate;
	float alpha;
	bool enable;
	Sprite(const char *texturePath);
	~Sprite();
	void update();
private:
	SDL_Texture *texture;
};
