#pragma once

#include "Scene.h"

#include <SDL.h>
#include "Resource.h"

class TestScene : public Scene {
public:
	TestScene();
	~TestScene();

	Texture *img;

	virtual void OnEnterScene();
	virtual void OnExitScene();
	virtual void Update(float delta);
};