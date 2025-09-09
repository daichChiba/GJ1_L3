#include "Player.h"
#include "input/Input.h"
#include <DirectXMath.h>

using namespace KamataEngine;
using namespace DirectX;
using namespace MathUtility;

void Player::Initialize(std::vector<std::vector<StageType>> Data_, KamataEngine::Vector2 BlockSize) {

	// FileAccessorの初期化
	fileAccessor_ = nullptr;
	// JSONファイル名を指定してFileAccessorを初期化 (相対パスを使用)
	fileAccessor_ = new FileJson::FileAccessor("Resources/Json/Player.json");

	//stage_ = new Stage;

	playerData_.data = Data_;
	playerData_.blockSize = BlockSize;

	model_ = Model::CreateFromOBJ("player");
	worldTransform_.Initialize();
	// worldTransform_.translation_ = {0.0f, -5.0f, -30.0f};
	// worldTransform_.translation_ = fileAccessor_->ReadVector3(playerJson_, "1stPos", Vector3());
	for (uint32_t y = 0; y < playerData_.data.size(); y++) {
		playerData_.data[y].resize(playerData_.data[y].size());
		for (uint32_t x = 0; x < playerData_.data[y].size(); x++) {
			Vector3 BlockPos = {1.0f * x, 1.0f * (playerData_.data.size() - 1 - y), 0};

			if (playerData_.data[y][x] == StageType::kFirstPlayer || playerData_.data[y][x] == StageType::kEntrancePortal) {
				worldTransform_.translation_ = BlockPos;
			}
		}
	}

	// Y軸を +90度回転して右向きにする
	worldTransform_.rotation_.y = XMConvertToRadians(90.0f);

	speed = fileAccessor_->Read(playerJson_, "speed", float());                 // キャラのスピード
	gravity = fileAccessor_->Read(playerJson_, "gravity", float());             // 重力加速度
	jumpPower = fileAccessor_->Read(playerJson_, "jumpPower", float());         // ジャンプの初速度
	groundY = fileAccessor_->Read(playerJson_, "groundY", float());             // 地面Y座標
	rotationSpeed = fileAccessor_->Read(playerJson_, "rotationSpeed", float()); // 補間係数（滑らかさ）
}

void Player::Update() {

	MoveInput();
	//if (input->PushKey(DIK_A)) {
	//	worldTransform_.translation_.x -= speed;
	//	targetAngleY_ = -90.0f; // 左向き
	//}
	//if (input->PushKey(DIK_D)) {
	//	worldTransform_.translation_.x += speed;
	//	targetAngleY_ = 90.0f; // 右向き
	//}

	// 現在の角度（度）
	float currentAngle = XMConvertToDegrees(worldTransform_.rotation_.y);

	// 差分（度）
	float delta = targetAngleY_ - currentAngle;

	// 最初の方向転換かどうかを判定するフラグ
	bool firstTurnDone_ = false;

	// 正規化（-180° ～ 180°に収める）
	if (delta > 180.0f) {
		delta -= 360.0f;
	} else if (delta < -180.0f) {
		delta += 360.0f;
	}

	// 左(-90) → 右(90) は必ず反時計回り
	if (currentAngle > -135.0f && currentAngle < -45.0f && targetAngleY_ == 90.0f) {
		delta = -270.0f;
	}

	// 最初の右(90) → 左(-90) だけは時計回り
	if (!firstTurnDone_ && currentAngle > 45.0f && currentAngle < 135.0f && targetAngleY_ == -90.0f) {
		delta = +270.0f;       // 時計回り
		firstTurnDone_ = true; // 以降は通常処理
	}

	// 新しい角度を計算
	float newAngle = currentAngle + delta * rotationSpeed;

	// ラジアンにして反映
	worldTransform_.rotation_.y = XMConvertToRadians(newAngle);

	//// ジャンプ入力（スペースキー）
	//if (input->TriggerKey(DIK_SPACE) && jumpCount_ < maxJumpCount_) {
	//	velocityY_ = jumpPower;
	//	isJumping_ = true;
	//	jumpCount_++; // ジャンプ回数を加算
	//}

	// 重力・落下処理
	if (isJumping_) {
		velocityY_ -= gravity;
		worldTransform_.translation_.y += velocityY_;

		// 着地判定
		if (worldTransform_.translation_.y <= groundY) {
			worldTransform_.translation_.y = groundY;
			isJumping_ = false;
			velocityY_ = 0.0f;
			jumpCount_ = 0; // 着地したらジャンプ回数リセット
		}
	}

	worldTransform_.UpdateMatrix();
}

void Player::Draw(const Camera& camera) {

	if (model_) {
		model_->Draw(worldTransform_, camera);
	}
}

void Player::DrawImGui() {

	ImGui::Begin("Player");
	ImGui::DragFloat3("transform", &worldTransform_.translation_.x, 0.01f);
	ImGui::End();
}

void Player::MoveInput() {
	if (input->PushKey(DIK_A)) {
		worldTransform_.translation_.x -= speed;
		targetAngleY_ = -90.0f; // 左向き
	}
	if (input->PushKey(DIK_D)) {
		worldTransform_.translation_.x += speed;
		targetAngleY_ = 90.0f; // 右向き
	}
	if (input->TriggerKey(DIK_SPACE) && jumpCount_ < maxJumpCount_) {
		velocityY_ = jumpPower;
		isJumping_ = true;
		jumpCount_++; // ジャンプ回数を加算
	}
}

KamataEngine::Vector3 Player::GetWorldPos() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

KamataEngine::Vector3 Player::CornerPosition(const KamataEngine::Vector3& center, Corner corner) {
	Vector3 offsetTable[kNumCorner] = {
	    {+playerData_.blockSize.x / 2.0f, -playerData_.blockSize.y / 2.0f, 0.0f},
        {-playerData_.blockSize.x / 2.0f, -playerData_.blockSize.y / 2.0f, 0.0f},
        {+playerData_.blockSize.x / 2.0f, +playerData_.blockSize.y / 2.0f, 0.0f},
        {-playerData_.blockSize.x / 2.0f, +playerData_.blockSize.y / 2.0f, 0.0f}
    };

	return offsetTable[static_cast<int>(corner)] + center;
}

//void Player::MapCollision(CollisionMapInfo& info) {
//
//}
//
//void Player::MapCollisionTop(CollisionMapInfo& info) {
//
//}
//
//void Player::MapCollisionBottom(CollisionMapInfo& info) {
//
//}
//
//void Player::MapCollisionLeft(CollisionMapInfo& info) {
//
//}
//
//void Player::MapCollisionRight(CollisionMapInfo& info) {
//
//}
//
//void Player::Move(CollisionMapInfo& info) {
//	if (input->PushKey(DIK_A)) {
//		worldTransform_.translation_.x -= speed;
//		targetAngleY_ = -90.0f; // 左向き
//	}
//	if (input->PushKey(DIK_D)) {
//		worldTransform_.translation_.x += speed;
//		targetAngleY_ = 90.0f; // 右向き
//	}
//	if (input->TriggerKey(DIK_SPACE) && jumpCount_ < maxJumpCount_) {
//		velocityY_ = jumpPower;
//		isJumping_ = true;
//		jumpCount_++; // ジャンプ回数を加算
//	}
//}
