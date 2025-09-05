#include "GameScene.h"


using namespace KamataEngine;
GameScene::GameScene() {

}

GameScene::~GameScene() {
	
}

void GameScene::Initialize() {

	// FileAccessorの初期化
	fileAccessor_ = nullptr;
	// JSONファイル名を指定してFileAccessorを初期化 (相対パスを使用)
	fileAccessor_ = new FileJson::FileAccessor("Resources/Json/Stage.json");

	csvData_ = fileAccessor_->ReadCsvData(stage, ereaNum + "_" + stageNum);

}

void GameScene::Update() {
	if (isFinish == true) {
		nextScene_ = SceneID::Reset;
		if (isClear==false) {
			if (is1stPortalThrough==false) {
				is1stPortalThrough = true;
			} else if (is2ndPortalThrough==false) {
				is2ndPortalThrough = true;
			}
			if (isGoal==true) {
				isClear = true;
			}
		}
	}
}

void GameScene::Draw() {
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



	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw();

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
	ImGui::End();
}

SceneID GameScene::NextScene() const {
	return nextScene_;
}
