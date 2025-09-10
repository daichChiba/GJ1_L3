#pragma once
#include "../stage/StageID.h"
#include "KamataEngine.h"

class StageMapCollider {
public:
	struct IndexSet {
		uint32_t xIndex;
		uint32_t yIndex;
	};

	struct MapChipIndex {
		int x;
		int y;
	};

	struct Rect {
		float left;
		float right;
		float bottom;
		float top;
	};

	MapChipIndex GetMapChipIndex(const KamataEngine::Vector3& pos_);

	StageType GetMapChipType(const MapChipIndex& index);
	StageType GetMapChipType(const KamataEngine::Vector3& pos_);

	IndexSet GetMapChipIndexSetByPos(const KamataEngine::Vector3& position);
	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);
	KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	void SetData(const std::vector<std::vector<StageType>>& data_) { data = data_; }
	void SetBlockSize(const KamataEngine::Vector2& blockSize_) { blockSize = blockSize_; }

private:
	std::vector<std::vector<StageType>> data;
	KamataEngine::Vector2 blockSize;
};