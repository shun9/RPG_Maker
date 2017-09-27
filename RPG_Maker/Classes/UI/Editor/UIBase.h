//************************************************/
//* @file  :UIBase.h
//* @brief :UI�̊��N���X
//* @date  :2017/09/26
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <simplemath.h>
#include <list>
#include <string>

namespace {
	using Vector2 = DirectX::SimpleMath::Vector2;
}

class UIBase
{
protected:
	std::string m_name;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UIBase(const std::string& name);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UIBase();

	virtual void DrawUpdate();
};