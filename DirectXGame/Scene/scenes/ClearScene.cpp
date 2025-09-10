#include "ClearScene.h"
using namespace KamataEngine;
#include "Scene/SpriteManager/GlobalSpriteManger.h"
#include "Scene/SpriteManager/SpriteManger.h"

ClearScene::ClearScene() {}

ClearScene::~ClearScene() {}

void ClearScene::Initialize() { th_ = globalSpriteManager.CreateSprite("clearScene/GameClear.png", Vector2{0.0f, 0.0f}); }

void ClearScene::Update() {
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		isFinish = true;
	}
	if (isFinish) {
		nextScene_ = SceneID::Title;
	}
}

void ClearScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	Sprite::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	globalSpriteManager.DrawSprite(th_);

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
	/// </summary>

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

void ClearScene::Delete() {

}

void ClearScene::DrawImGui() {

}

SceneID ClearScene::NextScene() const { return nextScene_; }
