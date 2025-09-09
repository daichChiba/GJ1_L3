#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Fade.h"
#include "scene/Scene.h"

// シーンの種類
enum class SceneState {

	Title,
	Game,
	Clear,
};

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

private:
	KamataEngine::Camera* camera_ = nullptr;
	Player player_;
	Fade fade_;

	// シーン管理
	SceneState sceneState_ = SceneState::Title; // 現在のシーン
	SceneState nextScene_ = SceneState::Title;  // フェード後に移行するシーン
};
