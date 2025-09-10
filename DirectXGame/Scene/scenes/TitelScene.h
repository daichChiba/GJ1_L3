#pragma once
#include "../Scene.h"
class TitelScene : public Scene {
public:
	TitelScene();
	~TitelScene();
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
	uint32_t th2_;
};
