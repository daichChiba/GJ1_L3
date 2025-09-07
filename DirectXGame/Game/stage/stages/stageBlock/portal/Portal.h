#pragma once
#include "Game/LoadJsonFile/FileJson.h"
#include "Game/stage/StageID.h"
#include <KamataEngine.h>


using namespace KamataEngine;

struct PortalData {
	std::vector<std::vector<StageType>> data;
};

class Portal {

public: // 関数
	void Initialize( std::vector<std::vector<StageType>> data_);

	void Update();

	void Draw(KamataEngine::Camera* camera_);


private: // 変数
	PortalData PortalData_;


	// モデル
	KamataEngine::Model* BlockModel_;

	// ワールドトランスフォーム
	std::vector<std::vector<WorldTransform>> worldTransform_;

	KamataEngine::Camera* camera;

	KamataEngine::ObjectColor* objectColor_;
};