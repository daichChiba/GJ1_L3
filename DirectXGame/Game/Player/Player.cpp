#define NOMINMAX
#include "Player.h"
#include "input/Input.h"
#include <DirectXMath.h>
#include <algorithm>

using namespace KamataEngine;
using namespace DirectX;
using namespace MathUtility;

void Player::Initialize(std::vector<std::vector<StageType>> Data_, KamataEngine::Vector2 BlockSize) {

	// FileAccessorの初期化
	fileAccessor_ = nullptr;
	// JSONファイル名を指定してFileAccessorを初期化 (相対パスを使用)
	fileAccessor_ = new FileJson::FileAccessor("Resources/Json/Player.json");

	stage_map_collider_ = new StageMapCollider;
	stage_map_collider_->SetData(Data_);          // StageMapColliderにData_を設定
	stage_map_collider_->SetBlockSize(BlockSize); // StageMapColliderにBlockSizeを設定

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
	// worldTransform_.UpdateMatrix(); // この行は残す
	MoveInput();
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
	ImGui::DragFloat("groundY", &groundY);
	ImGui::End();
}

void Player::MoveInput() {
	KamataEngine::Vector3 nextPosition = worldTransform_.translation_; // 移動先の座標を仮計算

	if (input->PushKey(DIK_A)) {
		nextPosition.x -= speed;
		targetAngleY_ = -90.0f; // 左向き
	}
	if (input->PushKey(DIK_D)) {
		nextPosition.x += speed;
		targetAngleY_ = 90.0f; // 右向き
	}

	// 重力・落下処理
	if (isJumping_) {
		velocityY_ -= gravity;
		worldTransform_.translation_.y += velocityY_;

		float landingThreshold = 0.05f; // 許容範囲
		if (worldTransform_.translation_.y <= groundY + landingThreshold) {
			worldTransform_.translation_.y = groundY;
			isJumping_ = false;
			velocityY_ = 0.0f;
			jumpCount_ = 0;
		}
	}

// MoveInput 関数内
	if (CheckCollisionWithBlocks(nextPosition)) {
		OnCollision();
		for (int i = 0; i < 3; ++i) { // 3回繰り返す
			AdjustPositionForBlockCollision(nextPosition);
			if (!CheckCollisionWithBlocks(nextPosition)) {
				worldTransform_.translation_ = nextPosition;
				return; // 衝突が解消されたら移動を確定して終了
			}
		}
		// それでも衝突する場合は、位置を戻すなどの処理が必要
		// 例：nextPosition = worldTransform_.translation_; // 移動しない
	} else {
		worldTransform_.translation_ = nextPosition;
	}

	// ジャンプ処理
	if (input->TriggerKey(DIK_SPACE) && jumpCount_ < maxJumpCount_) {
		velocityY_ = jumpPower;
		isJumping_ = true;
		jumpCount_++; // ジャンプ回数を加算
	}

	worldTransform_.translation_ = nextPosition;
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

bool Player::CheckCollisionWithBlocks(const KamataEngine::Vector3& nextPosition) {
	if (stage_map_collider_ == nullptr) {
		return false; // Stageが設定されていない場合は衝突しないとする
	}

	// プレイヤーのサイズ（blockSize）を取得
	KamataEngine::Vector2 blockSize = playerData_.blockSize;

	// プレイヤーの四隅の座標を計算
	KamataEngine::Vector3 corners[4] = {
	    CornerPosition(nextPosition, Corner::kRightBottom), // 右下
	    CornerPosition(nextPosition, Corner::kLeftBottom),  // 左下
	    CornerPosition(nextPosition, Corner::kRightTop),    // 右上
	    CornerPosition(nextPosition, Corner::kLeftTop)      // 左上
	};

	// 四隅のいずれかがブロックと衝突していたら、衝突と判定
	for (int i = 0; i < 4; ++i) {
		// 座標に対応するマップチップのインデックスを取得
		StageMapCollider::IndexSet indexSet = stage_map_collider_->GetMapChipIndexSetByPos(corners[i]);

		// インデックスがマップの範囲外の場合は衝突しないとみなす
		if (indexSet.xIndex < 0 || indexSet.xIndex >= playerData_.data[0].size() || indexSet.yIndex < 0 || indexSet.yIndex >= playerData_.data.size()) {
			continue; // 範囲外なので次の角をチェック
		}

		// マップチップの種類を取得
		StageType mapChipType = playerData_.data[indexSet.yIndex][indexSet.xIndex];

		// ブロックの場合は衝突
		if (mapChipType == StageType::kBlock) {
			return true;
		}
	}
	

	// どの角も衝突しなかった場合は、衝突していない
	return false;
}

void Player::OnCollision() {
	// 当たり判定が発生した場合の処理
	isJumping_ = false;
	velocityY_ = 0.0f;
	jumpCount_ = 0;

	//// コールバック関数が設定されている場合は実行
	// if (collisionCallback_) {
	//	collisionCallback_(this);
	// }
}

void Player::AdjustPositionForBlockCollision(KamataEngine::Vector3& position) {
	if (stage_map_collider_ == nullptr) {
		return;
	}

	// プレイヤーのサイズ（blockSize）を取得
	KamataEngine::Vector2 blockSize = playerData_.blockSize;

	// プレイヤーの四隅の座標を計算
	KamataEngine::Vector3 corners[4] = {
	    CornerPosition(position, Corner::kRightBottom), // 右下
	    CornerPosition(position, Corner::kLeftBottom),  // 左下
	    CornerPosition(position, Corner::kRightTop),    // 右上
	    CornerPosition(position, Corner::kLeftTop)      // 左上
	};

	// 各角について、ブロックとの衝突をチェック
	for (int i = 0; i < 4; ++i) {
		// 座標に対応するマップチップのインデックスを取得
		StageMapCollider::IndexSet indexSet = stage_map_collider_->GetMapChipIndexSetByPos(corners[i]);

		// インデックスがマップの範囲外の場合は無視
		if (indexSet.xIndex < 0 || indexSet.xIndex >= playerData_.data[0].size() || indexSet.yIndex < 0 || indexSet.yIndex >= playerData_.data.size()) {
			continue;
		}

		// マップチップの種類を取得
		StageType mapChipType = playerData_.data[indexSet.yIndex][indexSet.xIndex];

		// ブロックの場合は、位置を調整
		if (mapChipType == StageType::kBlock) {
			// ブロックの矩形を取得
			StageMapCollider::Rect blockRect = stage_map_collider_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);

			// どの方向にどれだけめり込んでいるかを計算
			float overlapLeft = blockRect.right - corners[i].x;
			float overlapRight = corners[i].x - blockRect.left;
			float overlapBottom = blockRect.top - corners[i].y;
			float overlapTop = corners[i].y - blockRect.bottom;

			// 最小のめり込み量を計算し、どの方向に調整するかを決定
			float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

			if (minOverlap == overlapLeft) {
				// 左方向に調整
				position.x += overlapLeft;
			} else if (minOverlap == overlapRight) {
				// 右方向に調整
				position.x -= overlapRight;
			} else if (minOverlap == overlapTop) {
				// 上方向に調整
				position.y -= overlapTop;
			} else if (minOverlap == overlapBottom) {
				// 下方向に調整
				position.y += overlapBottom;
			}
		}
	}
}

//// コリジョンコールバックの設定
// void Player::SetCollisionCallback(const CollisionCallback& callback) {
//     collisionCallback_ = callback;
// }