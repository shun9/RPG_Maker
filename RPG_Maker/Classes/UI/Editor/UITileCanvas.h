//************************************************/
//* @file  :UITileCanvas.h
//* @brief :UIのタイルキャンバスクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../../imgui/imgui.h"

#include "UICheckBox.h"
#include "UISlider.h"
#include "UITilePropertyEGroup.h"
#include "../../Map/TileDataHolder.h"
#include <SL_Texture.h>

class UITileCanvas :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	std::unique_ptr<ShunLib::Texture> m_texture;

	//表示位置
	Vector2 m_Pos;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UITileCanvas(const std::string& name);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UITileCanvas() override;

	virtual void DrawUpdate() override;

	// 選択されたタイルを記憶
	void SelectTile();

	void ConvertCanvasPos(const Vector2 & pos, int& bufX, int& bufY);

	// Tileのあたり判定
	bool CollisionTile(const Vector2& pos, int*& id);

};