#pragma once
#include "../../Game/Player/Player.h"
#include "../../Game/stage/StageManager.h"
#include "../../Game/stage/stages/stageBlock/PortalManager.h"
#include "../Scene.h"
#include "../manager/SceneID.h"
#include "Game/LoadJsonFile/FileJson.h"
#include "KamataEngine.h"
#include "SkyDome.h"

class GameScene : public Scene {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
	/// <summary>
	/// 削除
	/// </summary>
	void Delete() override;
	/// <summary>
	/// ImGui描画
	/// </summary>
	void DrawImGui() override;

	SceneID NextScene() const override;

private:
	SceneID nextScene_;

	PortalManager* portalManager_;

	KamataEngine::Camera* camera_ = nullptr;
	Player player_;

	// ステージマネージャー
	StageManager* stageManager_;

	// Csvデータ
	std::vector<std::vector<int>> csvData_;

	// Json読み書き用のファイルアクセサ
	FileJson::FileAccessor* fileAccessor_;

	SkyDome skydome_;
	KamataEngine::Model* Skydomemodel_ = nullptr;

	bool isGoal = false;
};