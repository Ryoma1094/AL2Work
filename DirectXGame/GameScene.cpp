#include "GameScene.h"
#include "2d/ImGuiManager.h"

using namespace KamataEngine;

void GameScene::Intialize() {
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("uvChecker.png");

	// スプライトインスタンスの生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	textureHandle_ = TextureManager::Load("kamata.ico");

	// 3Dモデルの生成
	model_ = Model::Create();

	// サウンドデータの読み込み
	soundDataHandle_ = Audio::GetInstance()->LoadWave("fanfare.wav");

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 音声再生
	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, true);

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// カメラの初期化
	camera_.Initialize();

	// ライン描画が参照するカメラを指定する（アドレス渡し）
	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

		// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロダクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());

}

void GameScene::Update() {
	// スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();

	// 座標を｛ 2, 1 ｝移動
	position.x += 2.0f;
	position.y += 1.0f;

	// 移動した座標をスプライトに反映
	sprite_->SetPosition(position);
	
	// スペースキーを押した瞬間
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		// 音声停止
		Audio::GetInstance()->StopWave(voiceHandle_);
	}

	// デバックカメラの更新
	debugCamera_->Update();

	#ifdef _DEBUG 
	ImGui::Begin("Debug1");
	// デバックテキストの表示
	ImGui::Text("Kawamura Ryoma %d.%d.%d", 2050, 12, 31);
	// float3入力ボックス
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	// float3スライダー
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	ImGui::End();
	// デモウィンドウの表示を有効化
	ImGui::ShowDemoWindow();
	#endif
}

void GameScene::Draw() {
	// スプライト描画前処理
	Sprite::PreDraw();

	// スプライトインスタンスの描画
	sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

	// 3Dモデル描画前処理
	Model::PreDraw();

	// 3Dモデル描画
	model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);

	// 3Dモデル描画後処理
	Model::PostDraw();

	// ラインを描画する
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});
}

GameScene::~GameScene() { 
	delete sprite_; 
	delete model_;
	delete debugCamera_;
}
