#include "TestScene.h"

TestScene::TestScene() {
}

TestScene::~TestScene() {
}

void TestScene::OnEnterScene() {
	Texture *tex = Resource::GetImage("excalibur");
	img = Sprite(tex);
	img.Zoom(0.5);
}

void TestScene::OnExitScene(){
}

void TestScene::Update(float delta) {
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	mx = App::screenWidth - mx;
	my = App::screenHeight - my;
	Renderer::SetCamPos(mx, my);

	static float now=0;
	now += delta * 10;
	Renderer::SetCamOffset(true);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			img.x = j * 100;
			img.y = i * 70;
			img.rotate = now + i * j * 2 % 360;
			img.Draw();
		}
}