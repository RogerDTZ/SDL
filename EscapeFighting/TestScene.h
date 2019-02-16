#pragma once

#include "Scene.h"
#include "Sprite.h"

class TestScene : public Scene {
public:
	TestScene();
	~TestScene();
	void OnEnterScene();
	void OnExitScene();
	void Update(float delta);
private:
	Sprite img;
};
