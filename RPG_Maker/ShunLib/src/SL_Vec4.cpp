#include <SL_Vec4.h>
#include <cmath>

using namespace ShunLib;


/// <summary>
/// ベクトルの正規化
/// </summary>
/// <returns>正規化されたベクトル</returns>
Vec4 Vec4::Normalize()
{
	float length = std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);

	m_x /= length;
	m_y /= length;
	m_z /= length;
	m_w /= length;

	return *this;
}

Vec4& Vec4::operator=(const Vec4 & V)
{
	this->m_x = V.m_x;
	this->m_y = V.m_y;
	this->m_z = V.m_z;
	this->m_w = V.m_w;

	return *this;
}

Vec4& Vec4::operator+=(const Vec4 & V)
{
	this->m_x += V.m_x;
	this->m_y += V.m_y;
	this->m_z += V.m_z;
	this->m_w += V.m_w;

	return *this;
}

Vec4& Vec4::operator-=(const Vec4 & V)
{
	this->m_x -= V.m_x;
	this->m_y -= V.m_y;
	this->m_z -= V.m_z;
	this->m_w -= V.m_w;

	return *this;
}

Vec4& Vec4::operator*=(float num)
{
	this->m_x *= num;
	this->m_y *= num;
	this->m_z *= num;
	this->m_w *= num;

	return *this;
}

Vec4& Vec4::operator/=(float num)
{
	this->m_x /= num;
	this->m_y /= num;
	this->m_z /= num;
	this->m_w /= num;

	return *this;
}

Vec4& Vec4::operator+()
{
	return *this;
}

Vec4 Vec4::operator-()
{
	Vec4 vec;

	vec = this->m_x * (-1);
	vec = this->m_y * (-1);
	vec = this->m_z * (-1);
	vec = this->m_w * (-1);
	return vec;
}


bool operator==(const ShunLib::Vec4 & V, const ShunLib::Vec4 & V2)
{
	return (V.m_x == V2.m_x
		  &&V.m_y == V2.m_y
		  &&V.m_z == V2.m_z
		  &&V.m_w == V2.m_w);
}

ShunLib::Vec4 operator+(const ShunLib::Vec4 & V, const ShunLib::Vec4 & V2)
{
	Vec4 vec;
	vec.m_x = V.m_x + V2.m_x;
	vec.m_y = V.m_y + V2.m_y;
	vec.m_z = V.m_z + V2.m_z;
	vec.m_z = V.m_w + V2.m_w;
	return vec;
}

ShunLib::Vec4 operator-(const ShunLib::Vec4 & V, const ShunLib::Vec4 & V2)
{
	Vec4 vec;
	vec.m_x = V.m_x - V2.m_x;
	vec.m_y = V.m_y - V2.m_y;
	vec.m_z = V.m_z - V2.m_z;
	vec.m_z = V.m_w - V2.m_w;
	return vec;
}

ShunLib::Vec4 operator*(const ShunLib::Vec4 & V, float num)
{
	Vec4 vec;
	vec.m_x = V.m_x * num;
	vec.m_y = V.m_y * num;
	vec.m_z = V.m_z * num;
	vec.m_z = V.m_w * num;
	return vec;
}

ShunLib::Vec4 operator/(const ShunLib::Vec4 & V, float num)
{
	Vec4 vec;
	vec.m_x = V.m_x / num;
	vec.m_y = V.m_y / num;
	vec.m_z = V.m_z / num;
	vec.m_z = V.m_w / num;
	return vec;
}
