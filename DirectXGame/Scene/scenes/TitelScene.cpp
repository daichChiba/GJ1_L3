#include "TitelScene.h"
using namespace KamataEngine;
#include "Scene/SpriteManager/GlobalSpriteManger.h"
#include "Scene/SpriteManager/SpriteManger.h"
TitelScene::TitelScene() {}

TitelScene::~TitelScene() {}

void TitelScene::Initialize() {
	th_ = globalSpriteManager.CreateSprite("titleScene/Title.png", Vector2{0.0f, 0.0f});
	th2_ = globalSpriteManager.CreateSprite("titleScene/TitleBackGround.png", Vector2{0.0f, 0.0f});
}

void TitelScene::Update() {
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		isFinish = true;
	}
	if (isFinish) {
		nextScene_ = SceneID::Reset;
	}
}

void TitelScene::Draw() {
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

	globalSpriteManager.DrawSprite(th2_);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void TitelScene::Delete() {}

void TitelScene::DrawImGui() {}

SceneID TitelScene::NextScene() const { return nextScene_; }
