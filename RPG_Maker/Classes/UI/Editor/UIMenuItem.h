//************************************************/
//* @file  :UIMenuItem.h
//* @brief :UIMenuItemのクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_Vec2.h>
#include "UIBase.h"
#include <list>
#include <memory>
#include <string>
#include <functional>

class UIMenuItem :public UIBase
{
	using Vector2 = ShunLib::Vec2;
private:
	std::function<void()> m_func;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIMenuItem(const std::string& name, std::function<void()> func = nullptr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIMenuItem() override;

	/// <summary>
	/// 押されたときのイベント
	/// </summary>
	/// <param name="func"></param>
	void SetPressEvent(std::function<void()> func) { m_func = func; }

	virtual void DrawUpdate() override;
};