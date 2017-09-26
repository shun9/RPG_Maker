//************************************************/
//* @file  :BUttonBase.h
//* @brief :�{�^���̊��N���X
//* @date  :2017/09/26
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <simplemath.h>

namespace {
	using Vector2 = DirectX::SimpleMath::Vector2;
}

class ButtonBase
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ButtonBase();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ButtonBase();

	void Draw(const Vector2& position) const;
};