//************************************************/
//* @file  :UIButton.h
//* @brief :UIButton�̃N���X
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