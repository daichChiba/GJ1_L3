#pragma once
#include "../Scene.h"

class ClearScene : public Scene {
public:
	ClearScene();
	~ClearScene();
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

	uint32_t th_;
};
