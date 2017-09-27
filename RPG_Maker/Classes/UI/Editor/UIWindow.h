//************************************************/
//* @file  :UIWindow.h
//* @brief :UI�̃E�C���h�E�N���X
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
	/// �R���X�g���N�^
	/// </summary>
	UIWindow(const std::string& name, const Vector2& windowSize);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UIWindow() override;

	virtual void DrawUpdate() override;
};