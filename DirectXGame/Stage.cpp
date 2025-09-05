#include "Stage.h"
#include <cassert>
#include <fstream>
#include <map>
#include <sstream>

using namespace KamataEngine;

namespace {

std::map<std::string, StageType> mapChipTable = {
    {"0", StageType::kBlank         },
    {"1", StageType::kBlock         },
    {"2", StageType::kEntrancePortal},
    {"3", StageType::kExitPortal    },
};
}

void Stage::Initialize(int ereaNum_, int stageNum_, std::string stage_) {
	// FileAccessorの初期化
	fileAccessor_ = nullptr;
	// JSONファイル名を指定してFileAccessorを初期化 (相対パスを使用)
	fileAccessor_ = new FileJson::FileAccessor("Resources/Json/Stage.json");

	csvData_ = fileAccessor_->ReadCsvData(stage_, ereaNum_ + "_" + stageNum_);

	// CSVからマップチップデータを読み込む
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			if (csvData_[y][x] == 0) {
				StageData_.data[y][x] = StageType::kBlank;
			} else {
				StageData_.data[y][x] = static_cast<StageType>(csvData_[y][x]);
			}

			Vector3 BlockPos = {0 + 0.1f * x, 0 + 0.1f * y, 0};
			worldTransform_[y][x].translation_ = BlockPos;
		}
	}

	BlockModel_ = Model::CreateFromOBJ("cube");
}

void Stage::Update() {
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			worldTransform_[y][x].UpdateMatrix();
		}
	}
}

void Stage::Draw(KamataEngine::Camera* camera_) {
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			BlockModel_->Draw(worldTransform_[y][x], *camera_);
		}
	}
}

// Vector3 Stage::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) { return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockVirtical - 1 - yIndex), 0); }
//
// Stage::IndexSet Stage::GetMapChipIndexSetByPosition(const Vector3& position) {
//
//	IndexSet indexSet = {};
//
//	indexSet.xIndex = static_cast<uint32_t>((position.x + kBlockWidth / 2) / kBlockWidth);
//
//	indexSet.yIndex = kNumBlockVirtical - 1 - static_cast<uint32_t>((position.y + kBlockHeight / 2) / kBlockHeight);
//
//	return indexSet;
// }
//
// Stage::Rect Stage::GetRectByIndex(uint32_t xIndex, uint32_t yIndex) {
//	// 指定ブロックの中心座標を取得する
//	Vector3 center = GetMapChipPositionByIndex(xIndex, yIndex);
//
//	Rect rect;
//	rect.left = center.x - kBlockWidth / 2.0f;
//	rect.right = center.x + kBlockWidth / 2.0f;
//	rect.bottom = center.y - kBlockHeight / 2.0f;
//	rect.top = center.y + kBlockHeight / 2.0f;
//
//	return rect;
// }