#pragma once
#include "../LoadJsonFile/FileJson.h"
#include "../stage/StageID.h"
#include "KamataEngine.h"
struct PlayerData {
	std::vector<std::vector<StageType>> data;
};
class Player {
public:
	void Initialize(std::vector<std::vector<StageType>> Data_);
	void Update();
	void Draw(const KamataEngine::Camera& camera);
	void DrawImGui();

	KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	float velocityY_ = 0.0f;
	bool isJumping_ = false;            // ジャンプ中かどうか
	float targetAngleY_ = 90.0f;        // 初期は右向き
	int jumpCount_ = 0;                 // 現在のジャンプ回数
	const int maxJumpCount_ = 1;        // 最大ジャンプ数
	bool isHoldingJump_ = false;        // ジャンプ中にホールドしてるか
	float holdTimer_ = 0.0f;            // ジャンプホールド時間
	const float maxHoldTime_ = 0.2f;    // 最大ホールド時間（秒）
	const float holdJumpBoost_ = 0.01f; // フレームごとの追加ジャンプ力

	// Json読み書き用のファイルアクセサ
	FileJson::FileAccessor* fileAccessor_;

	const std::string playerJson_ = "Player";

	PlayerData playerData_;

	bool isSave_ = false;

private:
	float speed;
	float gravity;
	float jumpPower;
	float groundY;
	float rotationSpeed;
};