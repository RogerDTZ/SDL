#pragma once

#include "Resource.h"

struct Texture;

class Sprite {
public:
	float x, y;
	float rotate;
	float alpha;
	bool active;
	Sprite();
	Sprite(Texture* texture);
	~Sprite();
	void Draw();
	void Zoom(float a);
	void ZoomBy(int which, float a);

private:
	Texture * texture;
};
