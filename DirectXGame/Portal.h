#pragma once
#include <math/Vector3.h>
#include <3d/WorldTransform.h>
#include <3d/Model.h>


class Portal {
public:
	Portal(const Vector3& pos, float radius = 1.0f);

	void SetPair(Portal* pair);
	Portal* GetPair() const;
	bool IsPlayerInside(const Vector3& playerPos) const;
	Vector3 GetPosition() const;

	void Initialize(KamataEngine::Model* model);
	void Draw(Camera* camera);

	WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	Vector3 position_;
	float radius_;
	Portal* pair_;
	WorldTransform worldTransform_;
	KamataEngine::Model* model_;
};
