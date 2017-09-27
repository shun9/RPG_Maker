//************************************************/
//* @file  :UIWindow.h
//* @brief :UI�̃E�C���h�E�N���X
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include "UIBase.h"
#include <list>
#include <memory>

#include "UIButton.h"

class UIWindow : public UIBase
{
	using Vector2 = ShunLib::Vec2;

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