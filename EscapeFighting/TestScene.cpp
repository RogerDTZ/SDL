#include "TestScene.h"

TestScene::TestScene() {
}

TestScene::~TestScene() {
}

void TestScene::OnEnterScene() {
	img = Resource::GetImage("excalibur");
}

void TestScene::OnExitScene() {
	img = NULL;
}

void TestScene::Update(float delta) {
	Resource::RenderTexture(img, 0, 0);
}