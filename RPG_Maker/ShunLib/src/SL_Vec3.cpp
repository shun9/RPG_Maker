//************************************************/
//* @file  :SL_Vec3.cpp
//* @brief :３次元ベクトル用のラップクラス
//* @date  :2017/07/04
//* @author:S.Katou
//************************************************/
#include "SL_Vec3.h"

#include <cmath>

using namespace ShunLib;

const Vec3 Vec3::Zero     = Vec3( 0 );
const Vec3 Vec3::One      = Vec3( 1 );
const Vec3 Vec3::UnitX    = Vec3( 1,  0,  0);
const Vec3 Vec3::UnitY    = Vec3( 0,  1,  0);
const Vec3 Vec3::UnitZ    = Vec3( 0,  0,  1);
const Vec3 Vec3::Up       = Vec3( 0,  1,  0);
const Vec3 Vec3::Down     = Vec3( 0, -1,  0);
const Vec3 Vec3::Right    = Vec3( 1,  0,  0);
const Vec3 Vec3::Left     = Vec3(-1,  0,  0);
const Vec3 Vec3::Forward  = Vec3( 0,  0, -1);
const Vec3 Vec3::Backward = Vec3( 0,  0,  1);


/// <summary>
/// 内積を返す
/// </summary>
float ShunLib::Vec3::Dot(const Vec3 & V, const Vec3 & V2)
{
	float dot = (V.m_x*V2.m_x)
			  + (V.m_y*V2.m_y)
			  + (V.m_z*V2.m_z);

	return dot;
}

/// <summary>
/// 外積を返す
/// </summary>
Vec3 Vec3::Cross(const Vec3 & V, const Vec3 & V2)
{
	Vec3 vec;
	vec.m_x = (V.m_y * V2.m_z) - (V.m_z * V2.m_y);
	vec.m_y = (V.m_z * V2.m_x) - (V.m_x * V2.m_z);
	vec.m_z = (V.m_x * V2.m_y) - (V.m_y * V2.m_x);

	return vec;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デフォルトコンストラクタ
//＋ーーーーーーーーーーーーーー＋
Vec3::Vec3()
	:m_x(0)
	,m_y(0)
	,m_z(0)
{

}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :値指定コンストラクタ
//｜引数  :X,Y,Z(float,float,float)
//＋ーーーーーーーーーーーーーー＋
Vec3::Vec3(float x, float y, float z)
	: m_x(x)
	, m_y(y)
	, m_z(z)
{

}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :値指定コンストラクタ
//｜引数  :X,Y,Z(float,float,float)
//＋ーーーーーーーーーーーーーー＋
Vec3::Vec3(float num)
	: m_x(num)
	, m_y(num)
	, m_z(num)
{

}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :コピーコンストラクタ
//＋ーーーーーーーーーーーーーー＋
Vec3::Vec3(const Vec3& vec)
	: m_x(vec.m_x)
	, m_y(vec.m_y)
	, m_z(vec.m_z)
{
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Vec3::~Vec3()
{

}


/// <summary>
/// ベクトルの正規化
/// </summary>
/// <returns>正規化されたベクトル</returns>
Vec3 Vec3::Normalize()
{
	float length = std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);

	m_x /= length;
	m_y /= length;
	m_z /= length;

	return *this;
}

/// <summary>
/// ベクトルの大きさを返す
/// </summary>
/// <returns>ベクトルの大きさ</returns>
float ShunLib::Vec3::Length()
{
	float lenght = std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
	return lenght;
}



/*--[以下　演算子のオーバーロード]--*/

Vec3& Vec3::operator=(const Vec3& V)
{
	this->m_x = V.m_x;
	this->m_y = V.m_y;
	this->m_z = V.m_z;

	return *this;
}


Vec3& Vec3::operator+=(const Vec3& V)
{
	this->m_x += V.m_x;
	this->m_y += V.m_y;
	this->m_z += V.m_z;
	return *this;
}

Vec3& Vec3::operator-=(const Vec3& V)
{
	this->m_x -= V.m_x;
	this->m_y -= V.m_y;
	this->m_z -= V.m_z;
	return *this;
}

Vec3& Vec3::operator*=(float num)
{
	this->m_x *= num;
	this->m_y *= num;
	this->m_z *= num;
	return *this;
}

Vec3& Vec3::operator/=(float num)
{
	this->m_x /= num;
	this->m_y /= num;
	this->m_z /= num;
	return *this;
}

Vec3& ShunLib::Vec3::operator+()
{
	return *this;
}

Vec3 ShunLib::Vec3::operator-()
{
	Vec3 vec;

	vec = this->m_x * (-1);
	vec = this->m_y * (-1);
	vec = this->m_z * (-1);
	return vec;
}


bool  operator==(const ShunLib::Vec3& V, const ShunLib::Vec3& V2)
{
	return (V.m_x == V2.m_x
		&&V.m_y == V2.m_y
		&&V.m_z == V2.m_z);
}

Vec3 operator+(const Vec3 & V, const Vec3 & V2)
{
	Vec3 vec;
	vec.m_x = V.m_x + V2.m_x;
	vec.m_y = V.m_y + V2.m_y;
	vec.m_z = V.m_z + V2.m_z;
	return vec;
}

Vec3 operator-(const Vec3 & V, const Vec3 & V2)
{
	Vec3 vec;
	vec.m_x = V.m_x - V2.m_x;
	vec.m_y = V.m_y - V2.m_y;
	vec.m_z = V.m_z - V2.m_z;
	return vec;
}

Vec3 operator*(const Vec3 & V, float num)
{
	Vec3 vec;
	vec.m_x = V.m_x * num;
	vec.m_y = V.m_y * num;
	vec.m_z = V.m_z * num;
	return vec;
}

Vec3 operator/(const Vec3 & V, float num)
{
	Vec3 vec;
	vec.m_x = V.m_x / num;
	vec.m_y = V.m_y / num;
	vec.m_z = V.m_z / num;
	return vec;
}
