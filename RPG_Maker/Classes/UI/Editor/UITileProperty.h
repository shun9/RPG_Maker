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
#include "UIText.h"

class UITileProperty :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	std::shared_ptr<UIText> m_text;
	// TODO:ゲージ
//	std::shared_ptr<UIGage> m_text;

	std::shared_ptr<UICheckBox> m_checkBoxIsMove;

	// TODO:スクロール


	bool m_isView;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UITileProperty(const std::string& name);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UITileProperty() override;

	virtual void DrawUpdate() override;

	void UIDrawUpdate();
};