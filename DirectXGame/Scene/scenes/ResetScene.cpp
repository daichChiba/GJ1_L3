#include "ResetScene.h"
using namespace KamataEngine;
#include "Scene/SpriteManager/GlobalSpriteManger.h"
#include "Scene/SpriteManager/SpriteManger.h"
ResetScene::ResetScene() {}

ResetScene::~ResetScene() {}

void ResetScene::Initialize() {
	th_ = globalSpriteManager.CreateSprite("white1x1.png",Vector2(0.0f,0.0f));
	globalSpriteManager.GetSprite(th_)->SetSize(Vector2(1280.0f, 720.0f));
	globalSpriteManager.GetSprite(th_)->SetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
}

void ResetScene::Update() {


	if (isClear==false) {
		isFinish = true;
		if (is1stPortalThrough==true&&is2ndPortalThrough==false) {
			stageNum += 1;
		} else if (is1stPortalThrough == true && is2ndPortalThrough == true) {
			stageNum += 1;
		}
	} else {
		if (input_->GetInstance()->PushKey(DIK_SPACE)) {
			isFinish = true;
		}
		is1stPortalThrough = false;
		is2ndPortalThrough = false;
		stageNum = 1;
	}

	if (isFinish==true) {
		isClear = false;
		nextScene_ = SceneID::Game;
	}
	if (ereaNum==1) {
		stage = "Tutorial";
	} else if(ereaNum == 2) {
		stage = "Stage_2";
	}
}

void ResetScene::Draw() {
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


void ResetScene::Delete() {}

void ResetScene::DrawImGui() {
#ifdef DEBUG_
	ImGui::Begin("ResetScene");
	ImGui::Text("Test");
	ImGui::Checkbox("isFinished", &isFinish);
	ImGui::SliderInt("ereaNum", &ereaNum, 1, 1);
	ImGui::SliderInt("stageNum", &stageNum, 1, 3);
	ImGui::Text("%d_%d", ereaNum, stageNum);
	ImGui::Text("stage=%s", stage.c_str());
	ImGui::End();

#endif // DEBUG_

}

SceneID ResetScene::NextScene() const { return nextScene_; }