#pragma once
#include "Scene.h"
#include"Sprite.h"
#include "Input.h"
#include<cassert>
#include "DirectXCommon.h"
#include "ViewProjection.h"
#include "AxisIndicator.h"

class Explanation 
{
public:

	Explanation();

	~Explanation();

	void Initialize();

	void Update();

	void Draw();

	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene() { return SceneType::kGameScene; }

	void Reset() { isSceneEnd = false; }

private:

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// ゲームオーバーのテクスチャ
	uint32_t explanationTextureHandle = 0u;

	Sprite* explanationSprite_ = nullptr;

	uint32_t explanation = 0;

	// シーン遷移
	bool isSceneEnd = false;

};
