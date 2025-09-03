#include "Portal.h"
#include <cmath>

using namespace KamataEngine;

Portal::Portal(const Vector3& pos, float radius) : position_(pos), radius_(radius), pair_(nullptr), model_(nullptr) {}

void Portal::SetPair(Portal* pair) { pair_ = pair; }

Portal* Portal::GetPair() const { return pair_; }

bool Portal::IsPlayerInside(const KamataEngine::Vector3& playerPos) const {
	float dx = playerPos.x - position_.x;
	float dy = playerPos.y - position_.y;
	float dz = playerPos.z - position_.z;
	float distSq = dx * dx + dy * dy + dz * dz;
	return distSq <= radius_ * radius_;
}

Vector3 Portal::GetPosition() const { return position_; }

void Portal::Initialize(KamataEngine::Model* model) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position_;
}

void Portal::Draw(Camera* camera) {
	if (model_) {
		model_->Draw(worldTransform_, *camera);
	}
}
