#pragma once
#include "../LoadJsonFile/FileJson.h"
#include "../stage/StageID.h"
#include "../stage/stages/Stage.h"
#include "KamataEngine.h"
struct PlayerData {
	std::vector<std::vector<StageType>> data;
	KamataEngine::Vector2 blockSize;
};
struct CollisionMapInfo {
	bool isCeilingCollision = false;
	bool landing = false;
	bool isWallTouch = false;
	Vector3 velocity;
};

// 範囲短形
enum Corner { kRightBottom, kLeftBottom, kRightTop, kLeftTop, kNumCorner };

class Player {
public:
	void Initialize(std::vector<std::vector<StageType>> Data_, KamataEngine::Vector2 BlockSize);
	void Update();
	void Draw(const KamataEngine::Camera& camera);
	void DrawImGui();

	void MoveInput();

	KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; }

	KamataEngine::Vector3 GetWorldPos();

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

	//void MapCollision(CollisionMapInfo& info);

	//void MapCollisionTop(CollisionMapInfo& info);
	//void MapCollisionBottom(CollisionMapInfo& info);
	//void MapCollisionLeft(CollisionMapInfo& info);
	//void MapCollisionRight(CollisionMapInfo& info);

	//void Move(CollisionMapInfo& info);


private:
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	float velocityY_ = 0.0f;
	bool isJumping_ = false;            // ジャンプ中かどうか
	float targetAngleY_ = 90.0f;        // 初期は右向き
	int jumpCount_ = 0;                 // 現在のジャンプ回数
	const int maxJumpCount_ = 2;        // 最大ジャンプ数
	bool isHoldingJump_ = false;        // ジャンプ中にホールドしてるか
	float holdTimer_ = 0.0f;            // ジャンプホールド時間
	const float maxHoldTime_ = 0.2f;    // 最大ホールド時間（秒）
	const float holdJumpBoost_ = 0.01f; // フレームごとの追加ジャンプ力

	// Json読み書き用のファイルアクセサ
	FileJson::FileAccessor* fileAccessor_;

	const std::string playerJson_ = "Player";

	PlayerData playerData_;

	bool isSave_ = false;

	Stage* stage_ = nullptr;

	Input* input = Input::GetInstance();

private:
	float speed;
	float gravity;
	float jumpPower;
	float groundY;
	float rotationSpeed;
};