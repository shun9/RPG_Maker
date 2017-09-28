//************************************************/
//* @file  :UICheckBox.h
//* @brief :UICheckBoxのクラス
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

class UICheckBox :public UIBase
{
	using Vector2 = ShunLib::Vec2;
private:
	bool* m_check;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UICheckBox(const std::string& name, bool* check);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UICheckBox() override;

	virtual void DrawUpdate() override;
};