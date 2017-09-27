//************************************************/
//* @file  :UIButton.h
//* @brief :UIButton�̃N���X
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_Vec2.h>
#include "UIBase.h"
#include <list>
#include <memory>
#include <functional>

class UIButton : public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	 std::function<void()> m_func;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UIButton(const std::string& name, std::function<void()> func = nullptr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UIButton() override;

	/// <summary>
	/// �����ꂽ�Ƃ��̃C�x���g
	/// </summary>
	/// <param name="func"></param>
	void SetPressEvent(std::function<void()> func) { m_func = func;  }

	virtual void DrawUpdate() override;
};