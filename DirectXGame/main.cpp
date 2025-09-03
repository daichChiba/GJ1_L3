#include "scene/scenes/GameScene.h"
#include <KamataEngine.h>
#include <Windows.h>
#include <map>

using namespace KamataEngine;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	// エンジンの初期化
	Initialize(L"3048");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

#pragma region 汎用機能初期化
	// ImGuiManagerインスタンスの取得
	ImGuiManager* imguiManager_ = ImGuiManager::GetInstance();

	// ゲームシーンのインスタンス生成
	GameScene* gameScene = new GameScene();
	// ゲームシーンの初期化
	gameScene->Initialize();

#pragma endregion
	// メインループ
	while (true) {
		// エンジンの更新
		if (Update()) {
			break;
		}

		if (Input::GetInstance()->PushKey(DIK_ESCAPE)) {
			break;
		}

		// 更新処理
		gameScene->Update();

		// ImGui受付開始
		imguiManager_->Begin();

		// ImGui受付開始
		imguiManager_->End();

		// 描画開始
		dxCommon->PreDraw();

		// ここに描画処理を記述する
		gameScene->Draw();

		// ImGui描画
		imguiManager_->Draw();

		// 描画終了
		dxCommon->PostDraw();
	}

	// ゲームシーンの解放
	delete gameScene;
	// nullptrの代入
	gameScene = nullptr;

	// エンジンの終了処理
	Finalize();

	return 0;
}
