#pragma once
#include "Scene/scenes/GameScene.h"
#include "Scene/scenes/ResetScene.h"
#include "Scene/manager/SceneID.h"
#include <KamataEngine.h>
#include <map>
class SceneManager {
public:
	SceneManager() = default;
	~SceneManager() = default;

	/// <summary>
	/// シーン切り替え（現在のシーンを破棄して新しいシーンを生成）
	/// </summary>
	/// <param name="nextScene"></param>
	void ChangeScene(SceneID nextScene);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// ImGui描画
	/// </summary>
	void DrawImGui();

	// setter
	void SetEreaNum(int num) { ereaNum = num; }
	void SetStageNum(int num) { stageNum = num; }
	void SetStage(std::string str) { stage = str; }

private:
	std::unique_ptr<Scene> currentScene_;
	SceneID currentSceneID_;

	int ereaNum = 1;
	int stageNum = 1;
	std::string stage = "Tutorial";
};
