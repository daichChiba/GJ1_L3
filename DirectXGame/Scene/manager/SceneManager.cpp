#include "SceneManager.h"

using namespace KamataEngine;

void SceneManager::ChangeScene(SceneID nextScene) {
	// 既存シーンのリソース削除
	if (currentScene_) {
		currentScene_->Delete();
		currentScene_.reset();
	}
	// 新しいシーンを生成
	switch (nextScene) {
	case SceneID::Game:
		currentScene_ = std::make_unique<GameScene>();
		// stageの数値と文字列を引き継ぐ
		currentScene_->SetStageNum(stageNum);
		currentScene_->SetEreaNum(ereaNum);
		currentScene_->SetStage(stage);
		break;
	case SceneID::Reset:
		currentScene_ = std::make_unique<ResetScene>();
		// stageの数値と文字列を引き継ぐ
		currentScene_->SetStageNum(stageNum);
		currentScene_->SetEreaNum(ereaNum);
		currentScene_->SetStage(stage);
		break;
	}


	currentSceneID_ = nextScene;

	// セットアップ
	if (currentScene_) {
		currentScene_->SetUp();
	}
}

void SceneManager::Update() {
	currentScene_->Update();

	// シーン終了が指示されたら、ゲーム <-> リセットを交互に切替
	if (currentScene_->IsFinish()) {
		SceneID next = currentScene_->NextScene();
		stageNum = currentScene_->GetStageNum();
		ereaNum = currentScene_->GetEreaNum();
		stage = currentScene_->GetStage();
		ChangeScene(next);
	}
}

void SceneManager::Draw() {
	if (currentScene_) {
		currentScene_->Draw();
	}
}

void SceneManager::DrawImGui() {
	if (currentScene_) {
		currentScene_->DrawImGui();
	}
}