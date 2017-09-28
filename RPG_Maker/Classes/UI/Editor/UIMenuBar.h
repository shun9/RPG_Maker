//************************************************/
//* @file  :UIMenuBar.h
//* @brief :UIMenuBarのクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_Vec2.h>
#include "UIBase.h"
#include <map>
#include <memory>
#include <string>

#include "UIMenu.h"

class UIMenuBar:public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	std::shared_ptr<std::map<std::string,std::shared_ptr<UIMenu>>> m_menuList;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIMenuBar(const std::string& name);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIMenuBar() override;

	void SetMenuItemFunc(std::string menuKey, std::string itemKey, std::function<void()> func = nullptr);

	virtual void DrawUpdate() override;
};