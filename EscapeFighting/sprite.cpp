#include "Sprite.h"

Sprite::Sprite() {
}

Sprite::Sprite(Texture *tex) {
	texture = tex;
	x = y = 0;
	rotate = 0;
	alpha = 255;
	active = true;
}

Sprite::~Sprite() {
}

void Sprite::Zoom(float a) {
	texture->Zoom(a);
}

void Sprite::ZoomBy(int which, float a) {
	texture->ZoomBy(which, a);
}

void Sprite::Draw() {
	if (active) {
		Renderer::SetColor(0, 0, 0, int(round(alpha)));
		Renderer::DrawTexture(texture, x, y, rotate);
	}
}
