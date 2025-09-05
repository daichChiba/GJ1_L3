#include "StageManager.h"

using namespace KamataEngine;

StageManager::StageManager() { stageManager_ = nullptr; }

StageManager::~StageManager() { delete stageManager_; }

void StageManager::Load(const std::string& path) {
	stageManager_ = new Stage();
	stageManager_->LoadMapchipCsv(path);
}

std::vector<std::vector<WorldTransform*>> StageManager::GenerateBlockTransforms(StageType type) {
	constexpr uint32_t kNumBlockVertical = 200;
	constexpr uint32_t kNumBlockHorizontal = 300;

	std::vector<std::vector<WorldTransform*>> blockList(kNumBlockVertical);
	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		blockList[i].resize(kNumBlockHorizontal);
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			if (stageManager_->GetMapchipTypeByIndex(j, i) == type) {
				WorldTransform* transform = new WorldTransform();
				transform->Initialize();

				Vector3 position = stageManager_->GetMapChipPositionByIndex(j, i);

				position.y = 2.0f;
				transform->rotation_ = {0.0f, 90.0f, 0.0f};

				transform->translation_ = position;
				blockList[i][j] = transform;
			}
		}
	}
	return blockList;
}

Stage* StageManager::GetMapChipField() const { return stageManager_; }
