#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"


GameScene::GameScene() {}

GameScene::~GameScene() 
{
	delete model_;
	delete debugCamera_;

	delete Stage_;
	delete StageModel_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	//プレイヤー
	TextureHandel_ = TextureManager::Load("mario.jpg");
	model_ = Model::Create();

	#pragma region ステージ関係
	//ステージ
	StageTextureHandle_ = TextureManager::Load("black.png");
	StageModel_ = Model::Create();

	//青ブロックのテクスチャ
	BlueStageTextureHandle_ = TextureManager::Load("blue.png");
	BlueStageModel_ = Model::Create();

	#pragma endregion

	#pragma region ブロック初期化
	//黒ブロック
	Stage_ = new MapChip();
	Stage_->Initialize(StageModel_, StageTextureHandle_);

	//青ブロック
	BlueStage_ = new MapChip();
	BlueStage_->BlueInitialize(BlueStageModel_, BlueStageTextureHandle_);

	#pragma endregion

	// デバッグカメラ
	debugCamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() 
{

	Stage_->Update();
	BlueStage_->Update();

	debugCamera_->Update();

	#ifdef _DEBUG

	if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;

		// debugCamera->Update();
	} else if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == true) {
		isDebugCameraActive_ = false;
	}

#endif // DEBUG

	// Cameraの処理
	if (isDebugCameraActive_) {

		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();

	} 
	else 
	{
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
}



void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>



	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	//プレイヤー
	model_->Draw(worldTransform_, viewProjection_, TextureHandel_);

	//model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), TextureHandel_);


	//ステージ
	Stage_->Draw(viewProjection_);

	BlueStage_->Draw(viewProjection_);

	


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
