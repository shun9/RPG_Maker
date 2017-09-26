//************************************************/
//* @file  :BUttonBase.h
//* @brief :ボタンの基底クラス
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
	/// コンストラクタ
	/// </summary>
	ButtonBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ButtonBase();

	void Draw(const Vector2& position) const;
};