#include "Portal.h"
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

void Portal::Initialize(int ereaNum_, int stageNum_, std::string stage_) {
	BlockModel_ = Model::CreateFromOBJ("block");

	objectColor_ = new ObjectColor();
	objectColor_->Initialize();
	objectColor_->SetColor({1.0f, 0.0f, 0.0f, 1.0f});

	// FileAccessorの初期化
	fileAccessor_ = nullptr;
	// JSONファイル名を指定してFileAccessorを初期化 (相対パスを使用)
	fileAccessor_ = new FileJson::FileAccessor("Resources/Json/Stage.json");

	csvData_ = fileAccessor_->ReadCsvData(stage_, std::to_string(ereaNum_) + "_" + std::to_string(stageNum_));

	// worldTransform をステージサイズにリサイズ
	worldTransform_.resize(csvData_.size());
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		worldTransform_[y].resize(csvData_[y].size());
	}
	PortalData_.data.resize(csvData_.size());

	// CSVからマップチップデータを読み込む
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		PortalData_.data[y].resize(csvData_[y].size());
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			if (csvData_[y][x] == 2) {
				PortalData_.data[y][x] = StageType::kEntrancePortal;
			} else if (csvData_[y][x] == 3) {
				PortalData_.data[y][x] = StageType::kExitPortal;
			} else {
				PortalData_.data[y][x] = static_cast<StageType>(csvData_[y][x]);
			}
			Vector3 BlockPos = {1.0f * x, 1.0f * y, 0};

			worldTransform_[y][x].translation_ = BlockPos;
			worldTransform_[y][x].Initialize();
		}
	}
}

void Portal::Update() {
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			worldTransform_[y][x].UpdateMatrix();
		}
	}
}

void Portal::Draw(KamataEngine::Camera* camera_) {
	for (uint32_t y = 0; y < csvData_.size(); y++) {
		for (uint32_t x = 0; x < csvData_[y].size(); x++) {
			if (PortalData_.data[y][x] == StageType::kEntrancePortal) {
				BlockModel_->Draw(worldTransform_[y][x], *camera_,objectColor_);
			}
			if (PortalData_.data[y][x] == StageType::kExitPortal) {
				BlockModel_->Draw(worldTransform_[y][x], *camera_,objectColor_);
			}
		}
	}
}