#pragma once
#include "Game/LoadJsonFile/FileJson.h"
#include <KamataEngine.h>
#include <base/DirectXCommon.h>
#include <math/Vector3.h>

using namespace KamataEngine;

enum class StageType {
	kBlank,          // 空白
	kBlock,          // ブロック
	kEntrancePortal, // 入口ポータル
	kExitPortal,     // 出口ポータル
};

struct StageData {
	std::vector<std::vector<StageType>> data;
};

class Stage {

public: // 関数

	void LoadMapchipCsv(const std::string& filePath);

	StageType GetMapchipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	uint32_t GetNumBlockVirtical() { return kNumBlockVirtical; }
	uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal; }

	struct IndexSet {
		uint32_t xIndex;
		uint32_t yIndex;
	};

	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);

	// 範囲短形
	struct Rect {
		float left;   // 左端
		float right;  // 右端
		float bottom; // 下端
		float top;    // 上端
	};

	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);

private: // 変数
	// ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	StageData StageData_;

	// Csvデータ
	std::vector<std::vector<int>> csvData_;

	// Json読み書き用のファイルアクセサ
	FileJson::FileAccessor* fileAccessor_;
};