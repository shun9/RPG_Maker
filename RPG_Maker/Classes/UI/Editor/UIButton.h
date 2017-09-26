//************************************************/
//* @file  :UIButton.h
//* @brief :UIButtonのクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <simplemath.h>
#include "UIBase.h"
#include <list>
#include <memory>
#include <functional>

namespace {
	using Vector2 = DirectX::SimpleMath::Vector2;
}

class UIButton : public UIBase
{
private:
	 std::function<void()> m_func;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIButton(const std::string& name, std::function<void()> func = nullptr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIButton() override;

	/// <summary>
	/// 押されたときのイベント
	/// </summary>
	/// <param name="func"></param>
	void SetPressEvent(std::function<void()> func) { m_func = func;  }

	virtual void DrawUpdate() override;
};