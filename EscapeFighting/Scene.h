#pragma once

#include "Renderer.h"
#include "App.h"
#include "Resource.h"

class Scene {
public:
	virtual void Update(float delta);
	virtual void OnEnterScene();
	virtual void OnExitScene();
};
