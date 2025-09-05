#pragma once
#include "Game/LoadJsonFile/FileJson.h"
#include "KamataEngine.h"
#include "Stage.h"
#include <string>
#include <vector>

class StageManager {

public:
	StageManager();

	~StageManager();

	// csvファイル読み込み
	void Load(const std::string& path);

	// ブロック生成（通常 or クリア）
	std::vector<std::vector<WorldTransform*>> GenerateBlockTransforms(StageType type);

	// Stage取得
	Stage* GetMapChipField() const;

private:
	Stage* stageManager_;
};
