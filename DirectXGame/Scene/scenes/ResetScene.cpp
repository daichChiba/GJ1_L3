#include "ResetScene.h"

ResetScene::ResetScene() {}

ResetScene::~ResetScene() {}

void ResetScene::Initialize() {}

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

}

void ResetScene::Draw() {}

void ResetScene::Delete() {}

void ResetScene::DrawImGui() {
	ImGui::Begin("ResetScene");
	ImGui::Text("Test");
	ImGui::Checkbox("isFinished", &isFinish);
	ImGui::SliderInt("ereaNum", &ereaNum, 1, 1);
	ImGui::SliderInt("stageNum", &stageNum, 1, 3);
    ImGui::Text("%d_%d", ereaNum, stageNum);
    ImGui::Text("stage=%s", stage.c_str());
	ImGui::End();
}

SceneID ResetScene::NextScene() const { return nextScene_; }