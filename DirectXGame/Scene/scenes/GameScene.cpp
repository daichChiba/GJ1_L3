#include "scene/scenes/GameScene.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete camera_;
	camera_ = nullptr;

	delete stageManager_;
}

void GameScene::Initialize() {

	Model::StaticInitialize();

	camera_ = new Camera();
	camera_->translation_.y = 1.0f;
	camera_->translation_.z = -30.0f;
	camera_->Initialize();

	// ステージマネージャー初期化
	stageManager_ = new StageManager();
	stageManager_->Initialize(ereaNum, stageNum, stage);

	// プレイヤーの初期化
	player_.Initialize(stageManager_->GetData(), stageManager_->GetBlockSize());

	// ポータルマネージャー初期化
	portalManager_ = new PortalManager();
	portalManager_->Initialize(stageManager_->GetData());
}

void GameScene::Update() {
	player_.Update();

	stageManager_->Update();

	portalManager_->Update();

	if (isFinish == true) {
		nextScene_ = SceneID::Reset;
		if (isClear == false) {
			if (is1stPortalThrough == false) {
				is1stPortalThrough = true;
			} else if (is2ndPortalThrough == false) {
				is2ndPortalThrough = true;
			}
			if (isGoal == true) {
				isClear = true;
			}
		}
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
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	player_.Draw(*camera_);
	/// </summary>

	portalManager_->Draw(camera_);

	player_.Draw(*camera_);

	stageManager_->Draw(camera_);

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

void GameScene::Delete() {
	// FileAccessorの開放
	if (fileAccessor_) {
		delete fileAccessor_;
		fileAccessor_ = nullptr;
	}
}

void GameScene::DrawImGui() {
	ImGui::Begin("GameScene");
	ImGui::Text("Test");
	ImGui::Checkbox("isFinished", &isFinish);
	ImGui::Text("%d_%d", ereaNum, stageNum);
	ImGui::Checkbox("isGoal", &isGoal);
	ImGui::DragFloat3("transform", &camera_->translation_.x, 0.01f);
	ImGui::End();
	//player_.DrawImGui();
}

SceneID GameScene::NextScene() const { return nextScene_; }