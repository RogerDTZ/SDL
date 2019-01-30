#include "Resource.h"

Texture::Texture() {
}

Texture::Texture(float w, float h, SDL_Texture * texture): w(w),h(h),texture(texture) {
}

Texture::~Texture() {
	SDL_DestroyTexture(texture);
}

std::unordered_map<std::string, Texture*> Resource::imgLib;

bool Resource::LoadImage(std::string texName, std::string texFile) {
	if (imgLib.count(texName) > 0) {
		printf("Error loading image! There is already an resource with a same name.\n");
		return false;
	}
	SDL_Surface *image = IMG_Load(texFile.c_str());
	SDL_Texture *texture = SDL_CreateTextureFromSurface(App::renderer, image);
	if (texture == NULL) {
		printf("Error loading image!\n");
		return false;
	}
	imgLib[texName] = &Texture(float(image->w), float(image->h), texture);
	return true;
}

Texture* Resource::GetImage(std::string texName) {
	if (imgLib.count(texName) == 0) {
		printf("Error require image! It seems that it has not benn loaded.\n");
		return NULL;
	}
	return imgLib[texName];
}

void Resource::Release() {
	std::unordered_map<std::string, Texture*>::iterator it;
	for (it = imgLib.begin(); it != imgLib.end();) {
		delete it->second;
		it = imgLib.erase(it);
	}
}

void Resource::RenderTexture(Texture *texture, float x, float y) {
	SDL_Rect pos = {int(std::round(x)),int(std::round(y)),int(std::round(texture->w)),int(std::round(texture->h))};
	SDL_RenderCopy(App::renderer, texture->texture, NULL, &pos);
}
