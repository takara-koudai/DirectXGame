#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "Player.h"
#include "Matrix.h"
#include "MapChip.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	bool isDebugCameraActive_ = false;

	//ワールドトランスフォームとビュープロジェクション
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	//プレイヤー
	uint32_t TextureHandel_ = 0;
	Model* model_ = nullptr;
	Player* player_ = nullptr;

	//ステージ
	uint32_t StageTextureHandle_ = 0;
	Model* StageModel_ = nullptr;
	MapChip* Stage_ = nullptr;

	//青のブロック
	uint32_t BlueStageTextureHandle_ = 0; 
	Model* BlueStageModel_ = nullptr;
	MapChip* BlueStage_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
