#pragma once

#include "Portal.h"
#include <3d/Camera.h>
#include <3d/Model.h>
#include <string>
#include <vector>

class PortalManager {
public:
	void LoadMapAndCreatePortals(const std::string& filePath, KamataEngine::Model* portalModel);
	void Draw(Camera* camera);
	const std::vector<Portal*>& GetPortals() const { return portals_; }

private:
	std::vector<Portal*> portals_;
	std::vector<std::vector<int>> LoadCSV(const std::string& filePath);
};
