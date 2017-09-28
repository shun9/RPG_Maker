//************************************************/
//* @file  :UIText.h
//* @brief :UITextのクラス
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

class UIText :public UIBase
{
	using Vector2 = ShunLib::Vec2;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIText(const std::string& name);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIText() override;

	template <typename T = int>
	void DrawUpdate(const char * fmt, ...);
};

// TODO:　不完全なためのちほど修正（int は可能）
template<typename T>
inline void UIText::DrawUpdate(const char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	ImGui::Text(fmt, va_arg(args, T));
	va_end(args);
}
