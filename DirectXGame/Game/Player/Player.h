#pragma once
#include "../Collision/StageMapCollider.h"
#include "../LoadJsonFile/FileJson.h"
#include "../stage/StageID.h"
#include "../stage/stages/Stage.h"
#include "KamataEngine.h"
#include <functional>

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

//// コールバック関数の型定義（衝突時に実行する関数）
//using CollisionCallback = std::function<void(Player*)>;

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

	void OnCollision();
	bool CanMove(const KamataEngine::Vector3& nextPosition);
	bool CheckCollisionWithBlocks(const KamataEngine::Vector3& nextPosition);
	void AdjustPositionForBlockCollision(KamataEngine::Vector3& position);

	// コリジョンコールバックの設定
	//void SetCollisionCallback(const CollisionCallback& callback) {
 //   collisionCallback_ = callback;
	//}

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

	StageMapCollider* stage_map_collider_ = nullptr;

	Input* input = Input::GetInstance();

	//// コリジョンコールバック
	//CollisionCallback collisionCallback_;

private:
	float speed;
	float gravity;
	float jumpPower;
	float groundY;
	float rotationSpeed;
};