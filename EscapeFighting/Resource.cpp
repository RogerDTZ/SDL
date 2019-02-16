#include "Resource.h"

Texture::Texture() {
}

Texture::Texture(float w, float h, SDL_Texture * texture): w(w), h(h), texture(texture) {
}

Texture::~Texture() {
}

void Texture::SetAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Texture::Zoom(float a) {
	w *= a;
	h *= a;
}

void Texture::ZoomBy(int which, float newVal) {
	float a = (which == 0) ? (newVal / w) : (newVal / h);
	Zoom(a);
}

std::unordered_map<std::string, int> Resource::imgIndex;
Texture Resource::imgLib[Resource::MAX_TEXTURE_NUM];
int Resource::imgCnt = 0;

bool Resource::LoadImage(std::string texName, std::string texFile) {
	if (imgIndex.count(texName) > 0) {
		printf("Error loading image! There is already an resource with a same name.\n");
		return false;
	}
	SDL_Surface *image = IMG_Load(texFile.c_str());
	SDL_Texture *texture = SDL_CreateTextureFromSurface(App::renderer, image);
	if (texture == NULL) {
		printf("Error loading image!\n");
		SDL_FreeSurface(image);
		SDL_DestroyTexture(texture);
		return false;
	}
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	imgIndex[texName] = imgCnt++;
	imgLib[imgIndex[texName]] = Texture(float(image->w), float(image->h), texture);
	SDL_FreeSurface(image);
	return true;
}

Texture* Resource::GetImage(std::string texName) {
	if (imgIndex.count(texName) == 0) {
		printf("Error require image! It seems that it has not benn loaded.\n");
		return NULL;
	}
	return &imgLib[imgIndex[texName]];
}

void Resource::Release() {
	for (int i = 0; i < imgCnt; i++)
		SDL_DestroyTexture(imgLib[i].texture);
}
