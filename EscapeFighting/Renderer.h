#pragma once

#include "App.h"
#include "Resource.h"
#include <SDL_ttf.h>

#define RENDER_RECT_LU 0
#define RENDER_RECT_CENTER 1

struct Texture;

class Renderer {
public:
	static void SetColor(int r, int g, int b, int a=255);
	static void SetCamPos(float x, float y, float w=cam_rect.w, float h=cam_rect.h);
	static void SetCamOffset(bool flag);
	static void ZoomCam(float a);
	static void DrawRect(float x, float y, float w, float h, float r = 0.0f);
	static void DrawTexture(Texture *texture, float x, float y, float r = 0.0f);
	static void DrawFont(std::string content, float x, float y);
	static void Clear();

private:
	static Uint8 r, g, b, a;
	static SDL_Rect cam_rect;
	static bool cam_offset;
	static void ZoomRect(SDL_Rect &rect);
};
