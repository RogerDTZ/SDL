#include "Renderer.h"

SDL_Rect Renderer::cam_rect = {0,0,160,90};
bool Renderer::cam_offset = true;
Uint8 Renderer::r = 0;
Uint8 Renderer::g = 0;
Uint8 Renderer::b = 0;
Uint8 Renderer::a = 0;

void Renderer::SetColor(int nr, int ng, int nb, int na) {
	r = nr; g = ng; b = nb; a = na;
	SDL_SetRenderDrawColor(App::renderer, r, g, b, a);
}

void Renderer::SetCamPos(float x, float y, float w, float h) {
	cam_rect = {int(round(x - w / 2)), int(round(y - h / 2)), int(round(w)), int(round(h))};
}

void Renderer::SetCamOffset(bool flag) {
	cam_offset = flag;
}

void Renderer::ZoomCam(float a) {
	float cx = cam_rect.x + cam_rect.w / 2;
	float cy = cam_rect.y + cam_rect.h / 2;
	cam_rect.w *= a;
	cam_rect.h *= a;
	SetCamPos(cx, cy, cam_rect.w, cam_rect.h);
}

void Renderer::DrawRect(float x, float y, float w, float h, float rotate) {
	SDL_Rect rect = {0, 0, int(round(w)), int(round(h))};
	SDL_Surface *surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
	Uint32 color = SDL_MapRGBA(surface->format, r, g, b, a);
	SDL_FillRect(surface, NULL, color);
	Texture texture(surface->w, surface->h, SDL_CreateTextureFromSurface(App::renderer, surface));
	DrawTexture(&texture, x + w / 2, y + h / 2, rotate);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture.texture);
}

void Renderer::DrawTexture(Texture *texture, float x, float y, float rotate) {
	SDL_Rect rect;
	rect = {int(round(x - texture->w / 2)),int(round(y - texture->h / 2)),int(round(texture->w)),int(round(texture->h))};
	if (cam_offset)
		ZoomRect(rect);
	texture->SetAlpha(a);
	SDL_RenderCopyEx(App::renderer, texture->texture, NULL, &rect, rotate, NULL, SDL_FLIP_NONE);
}

void Renderer::DrawFont(std::string content, float x, float y) {
	TTF_Font *font = TTF_OpenFont("Fonts/consolab.ttf", 12);
	SDL_Surface *message = TTF_RenderText_Solid(font, content.c_str(), SDL_Color({r, g, b}));
	SDL_Texture *texture = SDL_CreateTextureFromSurface(App::renderer, message);
	SDL_RenderCopy(App::renderer, texture, NULL, &SDL_Rect({int(round(x)),int(round(y)),150,30}));
	SDL_FreeSurface(message);
	SDL_DestroyTexture(texture);
}

void Renderer::Clear() {
	SetColor(0, 0, 0);
	SetCamOffset(false);
	DrawRect(0, 0, App::screenWidth, App::screenHeight);
} 

void Renderer::ZoomRect(SDL_Rect &rect) {
	if (cam_offset == false)
		return;
	float a = float(cam_rect.w) / App::screenWidth;
	rect.w /= a;
	rect.h /= a;
	rect.x -= cam_rect.x / a;
	rect.y -= cam_rect.y / a;
}
