//************************************************/
//* @file  :UITilePropertyEGroup.h
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

class UITilePropertyEGroup :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	//std::shared_ptr<std::list<int, std::shared_ptr<UIButton>>> m_groupList;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UITilePropertyEGroup(const std::string& name);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UITilePropertyEGroup() override;

	void AddGroup(int id);

	virtual void DrawUpdate() override;

	void UIDrawUpdate();
};