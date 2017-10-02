//************************************************/
//* @file  :UIInputStringBox.h
//* @brief :UIInputStringBoxのクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_Vec2.h>
#include "UIBase.h"
#include <list>
#include <memory>
#include <functional>
#include <string>

class UIInputStringBox : public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	 std::string* m_text;
	 std::size_t m_size;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIInputStringBox(const std::string& name, std::string* text,std::size_t size);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIInputStringBox() override;

	virtual void DrawUpdate() override;
};