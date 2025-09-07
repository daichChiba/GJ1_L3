#include "PortalManager.h"

using namespace KamataEngine;

void PortalManager::Initialize( std::vector<std::vector<StageType>> data) {
	data_ = data;

	portal_ = new Portal();
	portal_->Initialize(data_);
}

void PortalManager::Update() { portal_->Update(); }

void PortalManager::Draw(KamataEngine::Camera* camera_) { portal_->Draw(camera_); }
