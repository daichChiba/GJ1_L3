#include "PortalManager.h"

using namespace KamataEngine;

void PortalManager::Initialize(int ereaNum_, int stageNum_, std::string stage_) {

	portal_ = new Portal();
	portal_->Initialize(ereaNum_, stageNum_, stage_);
}

void PortalManager::Update() { portal_->Update(); }

void PortalManager::Draw(KamataEngine::Camera* camera_) { portal_->Draw(camera_); }
