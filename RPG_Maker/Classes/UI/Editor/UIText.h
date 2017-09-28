//************************************************/
//* @file  :UIText.h
//* @brief :UIText�̃N���X
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
	/// �R���X�g���N�^
	/// </summary>
	UIText(const std::string& name);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UIText() override;

	template <typename T = int>
	void DrawUpdate(const char * fmt, ...);
};

// TODO:�@�s���S�Ȃ��߂̂��قǏC���iint �͉\�j
template<typename T>
inline void UIText::DrawUpdate(const char * fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	ImGui::Text(fmt, va_arg(args, T));
	va_end(args);
}
