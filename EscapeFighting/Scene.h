#pragma once

class Scene {
public:
	virtual void Update(float delta);
	virtual void OnEnterScene();
	virtual void OnExitScene();
};
