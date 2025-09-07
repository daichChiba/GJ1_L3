#pragma once
#include "Game/LoadJsonFile/FileJson.h"
#include "Game/stage/StageID.h"
#include <KamataEngine.h>
#include <base/DirectXCommon.h>
#include <math/Vector3.h>

using namespace KamataEngine;

struct PortalData {
	std::vector<std::vector<StageType>> data;
};

class Portal {

public: // 関数
	void Initialize(int ereaNum_, int stageNum_, std::string stage_);

	void Update();

	void Draw(KamataEngine::Camera* camera_);

	// getter
	std::vector<std::vector<StageType>> GetData() { return PortalData_.data; }

private: // 変数
	PortalData PortalData_;

	// Csvデータ
	std::vector<std::vector<int>> csvData_;

	// Json読み書き用のファイルアクセサ
	FileJson::FileAccessor* fileAccessor_;

	// モデル
	KamataEngine::Model* BlockModel_;

	// ワールドトランスフォーム
	std::vector<std::vector<WorldTransform>> worldTransform_;

	KamataEngine::Camera* camera;
};