#include "StageMapCollider.h"
#include <algorithm>
using namespace KamataEngine;

StageMapCollider::MapChipIndex StageMapCollider::GetMapChipIndex(const KamataEngine::Vector3& pos_) {
	MapChipIndex index;
	index.x = static_cast<int>(pos_.x / blockSize.x);
	index.y = static_cast<int>(pos_.y / blockSize.y);
	index.x = std::clamp<int>(index.x, 0, static_cast<int>(data[0].size()) - 1);
	index.y = std::clamp<int>(index.y, 0, static_cast<int>(data.size()) - 1);
	return index;
}

StageType StageMapCollider::GetMapChipType(const MapChipIndex& index) {
	return data[index.x][index.y]; }

StageType StageMapCollider::GetMapChipType(const Vector3& pos_) {
	MapChipIndex index = GetMapChipIndex(pos_);
	return data[index.x][index.y];
}

StageMapCollider::IndexSet StageMapCollider::GetMapChipIndexSetByPos(const Vector3& position) {
	IndexSet indexSet = {};
	indexSet.xIndex = static_cast<uint32_t>((position.x + blockSize.x / 2.0f) / blockSize.x);
	indexSet.yIndex = static_cast<uint32_t>(data.size()) - 1 - static_cast<uint32_t>((position.y + blockSize.y / 2.0f) / blockSize.y);

	return indexSet;
}

StageMapCollider::Rect StageMapCollider::GetRectByIndex(uint32_t xIndex, uint32_t yIndex) {
	Vector3 center = GetMapChipPositionByIndex(xIndex, yIndex);
	Rect rect;

	rect.left = center.x - blockSize.x / 2.0f;
	rect.right = center.x + blockSize.x / 2.0f;
	rect.bottom = center.y - blockSize.y / 2.0f;
	rect.top = center.y + blockSize.y / 2.0f;

	return rect;
}

Vector3 StageMapCollider::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) {
	return Vector3(blockSize.x * xIndex, blockSize.y * (data.size() - 1 - yIndex), 0);
 }