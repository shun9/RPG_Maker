//************************************************/
//* @file  :UITileProperty.h
//* @brief :UIのタイルプロパティウインドウクラス
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
#include "../../Data/TileData.h"

class UITileProperty :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	int m_currentTileId;

	TileData* m_tileData;

	std::unique_ptr<UISlider> m_encountSlider;

	std::unique_ptr<UICheckBox> m_checkBoxIsMove;

	// スクロール
	std::unique_ptr<UITilePropertyEGroup> m_groupSlider;

	// 画像変更
	std::unique_ptr<UIButton> m_textureChangeButton;

	// 追加ボタン
	std::unique_ptr<UIButton> m_addGroupButton;

	// 削除ボタン
	std::unique_ptr<UIButton> m_removeGroupButton;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UITileProperty(const std::string& name, int id = 0);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UITileProperty() override;

	void SetID(int id);
	void UIUpdate();

	virtual void DrawUpdate() override;

	void UIDrawUpdate();

	void IdObservation();

	void ChangeTexture();
};