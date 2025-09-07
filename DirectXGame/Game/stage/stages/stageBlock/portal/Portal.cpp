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

void Portal::Initialize( std::vector<std::vector<StageType>> data_) {
	BlockModel_ = Model::CreateFromOBJ("block");

	objectColor_ = new ObjectColor();
	objectColor_->Initialize();
	objectColor_->SetColor({1.0f, 0.0f, 0.0f, 1.0f});


	PortalData_.data = data_;

	// worldTransform をステージサイズにリサイズ
	worldTransform_.resize(PortalData_.data.size());
	for (uint32_t y = 0; y < PortalData_.data.size(); y++) {
		worldTransform_[y].resize(PortalData_.data[y].size());
	}
	PortalData_.data.resize(PortalData_.data.size());

	// CSVからマップチップデータを読み込む
	for (uint32_t y = 0; y < PortalData_.data.size(); y++) {
		PortalData_.data[y].resize(PortalData_.data[y].size());
		for (uint32_t x = 0; x < PortalData_.data[y].size(); x++) {
			Vector3 BlockPos = {1.0f * x, 1.0f * y, 0};

			worldTransform_[y][x].translation_ = BlockPos;
			worldTransform_[y][x].Initialize();
		}
	}
}

void Portal::Update() {
	for (uint32_t y = 0; y < PortalData_.data.size(); y++) {
		for (uint32_t x = 0; x < PortalData_.data[y].size(); x++) {
			worldTransform_[y][x].UpdateMatrix();
		}
	}
}

void Portal::Draw(KamataEngine::Camera* camera_) {
	for (uint32_t y = 0; y < PortalData_.data.size(); y++) {
		for (uint32_t x = 0; x < PortalData_.data[y].size(); x++) {
			if (PortalData_.data[y][x] == StageType::kEntrancePortal) {
				BlockModel_->Draw(worldTransform_[y][x], *camera_,objectColor_);
			}
			if (PortalData_.data[y][x] == StageType::kExitPortal) {
				BlockModel_->Draw(worldTransform_[y][x], *camera_,objectColor_);
			}
		}
	}
}