//************************************************/
//* @file  :UITileWindow.h
//* @brief :UIのタイルウインドウクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <list>
#include <memory>
#include <string>
#include "../../imgui/imgui.h"

#include "UIButton.h"

class UITileWindow :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	std::list<std::shared_ptr<UIBase>> m_buttonList;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UITileWindow(const std::string& name);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UITileWindow() override;

	virtual void DrawUpdate() override;

	void AddUI(std::shared_ptr<UIBase> ui) { m_buttonList.push_back(ui); }

	void UIDrawUpdate();
};