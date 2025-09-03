#include "PortalManager.h"
#include <fstream>
#include <sstream>

using namespace KamataEngine;

std::vector<std::vector<int>> PortalManager::LoadCSV(const std::string& filePath) {
	std::ifstream file(filePath);
	std::vector<std::vector<int>> mapData;
	std::string line;

	while (std::getline(file, line)) {
		std::vector<int> row;
		std::stringstream ss(line);
		std::string cell;
		while (std::getline(ss, cell, ',')) {
			row.push_back(std::stoi(cell));
		}
		mapData.push_back(row);
	}
	return mapData;
}

void PortalManager::LoadMapAndCreatePortals(const std::string& filePath, KamataEngine::Model* portalModel) {
	auto mapData = LoadCSV(filePath);
	float cellSize = 1.0f; // 1マスの大きさ

	Portal* portalA = nullptr;
	Portal* portalB = nullptr;

	for (int y = 0; y < mapData.size(); ++y) {
		for (int x = 0; x < mapData[y].size(); ++x) {
			int cell = mapData[y][x];
			Vector3 worldPos = {x * cellSize, 0, y * cellSize};

			if (cell == 2) {
				portalA = new Portal(worldPos);
				portalA->Initialize(portalModel);
				portals_.push_back(portalA);
			} else if (cell == 3) {
				portalB = new Portal(worldPos);
				portalB->Initialize(portalModel);
				portals_.push_back(portalB);
			}
		}
	}

	// A と B をペアリング
	if (portalA && portalB) {
		portalA->SetPair(portalB);
		portalB->SetPair(portalA);
	}
}

void PortalManager::Draw(Camera* camera) {
	for (auto portal : portals_) {
		portal->Draw(camera);
	}
}
