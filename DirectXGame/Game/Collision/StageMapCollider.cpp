#include "StageMapCollider.h"

using namespace KamataEngine;

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
