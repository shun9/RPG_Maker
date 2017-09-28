//************************************************/
//* @file  :UIMenu.h
//* @brief :UIMenuのクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_Vec2.h>
#include "UIBase.h"
#include <map>
#include <memory>
#include <string>

#include "UIMenuItem.h"

class UIMenu :public UIBase
{
	using Vector2 = ShunLib::Vec2;
private:
	std::shared_ptr<std::map<std::string, std::shared_ptr<UIMenuItem>>> m_itemList;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIMenu(const std::string& name);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIMenu() override;

	virtual void DrawUpdate() override;

	std::map<std::string, std::shared_ptr<UIMenuItem>>& GetItemList() { return *m_itemList.get(); }
};