#pragma once
#include "KamataEngine.h"
#include "../stage/StageID.h"


class StageMapCollider {
public:
	struct IndexSet {
		uint32_t xIndex;
		uint32_t yIndex;
	};
	struct Rect {
		float left;
		float right;
		float bottom;
		float top;
	};

	IndexSet GetMapChipIndexSetByPos(const KamataEngine::Vector3& position);
	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);
	KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);


	void SetData(std::vector<std::vector<StageType>> data_) { data = data_; }
	void SetBlockSize(KamataEngine::Vector2 blockSize_) { blockSize = blockSize_; }

private:
	std::vector<std::vector<StageType>> data;
	KamataEngine::Vector2 blockSize;

};
