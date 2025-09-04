#include "scene/scenes/GameScene.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete camera_;
	camera_ = nullptr;
}

void GameScene::Initialize() {

	Model::StaticInitialize();
	// プレイヤーの初期化
	player_.Initialize();

	camera_ = new Camera();
	camera_->Initialize();

	// ポータル初期化
	KamataEngine::Model* portalModel = KamataEngine::Model::CreateFromOBJ("player");

	// CSVからポータル生成
	portalManager_.LoadMapAndCreatePortals("Resources/Json/Stage.json", portalModel);
}

void GameScene::Update() {
	player_.Update();

	if (isFinish == true) {
		nextScene_ = SceneID::Reset;
	}
}

void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	portalManager_.Draw(camera_);
	player_.Draw(*camera_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Delete() {}

void GameScene::DrawImGui() {
	ImGui::Begin("GameScene");
	ImGui::Text("Test");
	ImGui::Checkbox("isFinished", &isFinish);
	ImGui::End();
}

SceneID GameScene::NextScene() const { return nextScene_; }