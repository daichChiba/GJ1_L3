#pragma once
#include "Game/LoadJsonFile/FileJson.h"
#include "Game/stage/StageID.h"
#include "Game/stage/stages/stageBlock/portal/Portal.h"
#include "KamataEngine.h"

class PortalManager {

public:
	void Initialize( std::vector<std::vector<StageType>> data);

	void Update();

	void Draw(KamataEngine::Camera* camera_);


private:
	// Csvデータ
	std::vector<std::vector<int>> csvData_;

	std::vector<std::vector<StageType>> data_;

	Portal* portal_;
};
