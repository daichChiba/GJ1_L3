#pragma once
#include "Game/LoadJsonFile/FileJson.h"
#include "Game/stage/StageID.h"
#include "Game/stage/stages/stageBlock/portal/Portal.h"
#include "KamataEngine.h"

class PortalManager {

public:
	void Initialize(int ereaNum_, int stageNum_, std::string stage_);

	void Update();

	void Draw(KamataEngine::Camera* camera_);

	// getter
	std::vector<std::vector<StageType>> GetData() { portal_->GetData(); }

private:
	// Csvデータ
	std::vector<std::vector<int>> csvData_;

	Portal* portal_;
};
