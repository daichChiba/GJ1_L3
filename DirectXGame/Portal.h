#pragma once
#include <3d/Model.h>
#include <3d/WorldTransform.h>
#include <math/Vector3.h>

class Portal {
public:
	Portal(const KamataEngine::Vector3& pos, float radius = 1.0f);

	void SetPair(Portal* pair);
	Portal* GetPair() const;
	bool IsPlayerInside(const KamataEngine::Vector3& playerPos) const;
	KamataEngine::Vector3 GetPosition() const;

	void Initialize(KamataEngine::Model* model);
	void Draw(KamataEngine::Camera* camera);

	KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	KamataEngine::Vector3 position_;
	float radius_;
	Portal* pair_;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_;
};
