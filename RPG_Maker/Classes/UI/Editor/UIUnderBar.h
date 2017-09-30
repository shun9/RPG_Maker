//************************************************/
//* @file  :UIUnderBar.h
//* @brief :画面下部のバーUIクラス
//* @date  :2017/10/01
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../../imgui/imgui.h"
#include <SL_Vec2.h>
#include "UIBase.h"

class UIUnderBar :public UIBase
{
	using Vector2 = ShunLib::Vec2;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIUnderBar(const std::string& name);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIUnderBar() override;

	void DataSetting(const std::string fileName, int x, int y);

	virtual void DrawUpdate(const std::string& fileName, int x, int y);
};