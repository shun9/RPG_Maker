//************************************************/
//* @file  :UIWindow.h
//* @brief :UIのウインドウクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <simplemath.h>
#include "UIBase.h"
#include <list>
#include <memory>


#include "UIButton.h"

namespace {
	using Vector2 = DirectX::SimpleMath::Vector2;
}

class UIWindow : public UIBase
{
private:
	std::list<std::shared_ptr<UIBase>> m_buttonList;

	std::shared_ptr<ImVec2> m_windowSize;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIWindow(const std::string& name, const Vector2& windowSize);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIWindow() override;

	virtual void DrawUpdate() override;
};