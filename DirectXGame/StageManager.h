#pragma once
#include "Game/LoadJsonFile/FileJson.h"
#include "KamataEngine.h"
#include "Stage.h"
#include "StageID.h"

class StageManager {

public:
	void Initialize(int ereaNum_, int stageNum_, std::string stage_);

	void Update();

	void Draw(KamataEngine::Camera* camera_);

	// getter
	std::vector<std::vector<StageType>> GetData() { Stage_->GetData(); }

private:
	// Csvデータ
	std::vector<std::vector<int>> csvData_;

	Stage* Stage_;
};
