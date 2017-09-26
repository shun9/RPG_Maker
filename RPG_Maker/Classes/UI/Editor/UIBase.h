//************************************************/
//* @file  :UIBase.h
//* @brief :UIの基底クラス
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
	/// コンストラクタ
	/// </summary>
	UIBase(const std::string& name);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIBase();

	virtual void DrawUpdate();
};