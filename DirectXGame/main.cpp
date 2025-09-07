#include "Scene/manager/SceneID.h"
#include "Scene/manager/SceneManager.h"
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

	// シーンマネージャー
	SceneManager sceneManager_;
	sceneManager_.ChangeScene(SceneID::Reset); // 最初は GameScene

#pragma region 汎用機能初期化
	// ImGuiManagerインスタンスの取得
	ImGuiManager* imguiManager_ = ImGuiManager::GetInstance();

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

		sceneManager_.Update();

		// ImGui受付開始
		imguiManager_->Begin();

		sceneManager_.DrawImGui();

		// ImGui受付開始
		imguiManager_->End();

		// 描画開始
		dxCommon->PreDraw();


		sceneManager_.Draw();

		// ImGui描画
		imguiManager_->Draw();

		// 描画終了
		dxCommon->PostDraw();
	}

	// エンジンの終了処理
	Finalize();

	return 0;
}