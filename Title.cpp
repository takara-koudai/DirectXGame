﻿#include "Title.h"
#include "TextureManager.h"

Title::Title() {}

Title::~Title() 
{
	delete titleSprite; }

void Title::Initialize() 
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// タイトル
	//TitleTextureHandle = TextureManager::Load("TitleScene.png");

	titleSprite = Sprite::Create(TitleTextureHandle, {0, 0});

	// デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void Title::Update() 
{
	if (input_->TriggerKey(DIK_SPACE)) 
	{
		isSceneEnd = true;
	}
}

void Title::Draw() 
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	///< summary>
	/// ここに背景スプライトの描画処理を追加できる
	///</summary>

	titleSprite->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	///< summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	///</summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();

	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	///< summary>
	/// ここに前景スプライトの描画処理を追加できる
	///</summary>

	// スプライト描画後処理
	Sprite::PostDraw();
}

