#pragma once
#include "scene/manager/SceneID.h"

class IScene {
public:
	virtual ~IScene() = default;
	virtual void SetUp() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void DrawImGui() = 0;
	virtual void Delete() = 0;
	virtual bool IsFinish() = 0;
	virtual SceneID NextScene() = 0;
};