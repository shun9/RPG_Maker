//************************************************/
//* @file  :SL_Vec2.cpp
//* @brief :2次元ベクトル用クラス
//* @date  :2017/07/04
//* @author:S.Katou
//************************************************/
#include "SL_Vec2.h"
using namespace ShunLib;

const Vec2 Vec2::Zero  = Vec2(0, 0);
const Vec2 Vec2::One   = Vec2(1, 1);
const Vec2 Vec2::UnitX = Vec2(1, 0);
const Vec2 Vec2::UnitY = Vec2(0, 1);

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デフォルトコンストラクタ
//＋ーーーーーーーーーーーーーー＋
Vec2::Vec2()
	:m_x(0)
	,m_y(0)
{

}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :値指定コンストラクタ
//｜引数  :X,Y,Z(float,float,float)
//＋ーーーーーーーーーーーーーー＋
Vec2::Vec2(float x, float y)
	:m_x(x)
	,m_y(y)
{

}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Vec2::~Vec2()
{

}



/*--[以下　演算子のオーバーロード]--*/

Vec2& Vec2::operator=(const Vec2& V)
{
	this->m_x = V.m_x;
	this->m_y = V.m_y;

	return *this;
}

Vec2 Vec2::operator+(const Vec2& V)
{
	Vec2 vec;

	vec.m_x = this->m_x + V.m_x;
	vec.m_y = this->m_y + V.m_y;

	return vec;
}

Vec2 Vec2::operator-(const Vec2& V)
{
	Vec2 vec;

	vec.m_x = this->m_x - V.m_x;
	vec.m_y = this->m_y - V.m_y;

	return vec;
}

Vec2 Vec2::operator*(int num)
{
	Vec2 vec;

	vec.m_x = this->m_x * num;
	vec.m_y = this->m_y * num;

	return vec;
}

Vec2 ShunLib::Vec2::operator*(float num)
{
	Vec2 vec;

	vec.m_x = this->m_x * num;
	vec.m_y = this->m_y * num;

	return vec;
}

Vec2 ShunLib::Vec2::operator*(double num)
{
	Vec2 vec;

	vec.m_x = this->m_x * static_cast<float>(num);
	vec.m_y = this->m_y * static_cast<float>(num);

	return vec;
}
