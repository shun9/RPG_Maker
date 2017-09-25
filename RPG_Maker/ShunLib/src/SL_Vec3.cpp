//************************************************/
//* @file  :SL_Vec3.cpp
//* @brief :�R�����x�N�g���p�̃��b�v�N���X
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
/// ���ς�Ԃ�
/// </summary>
float ShunLib::Vec3::Dot(const Vec3 & V, const Vec3 & V2)
{
	float dot = (V.m_x*V2.m_x)
			  + (V.m_y*V2.m_y)
			  + (V.m_z*V2.m_z);

	return dot;
}

/// <summary>
/// �O�ς�Ԃ�
/// </summary>
Vec3 Vec3::Cross(const Vec3 & V, const Vec3 & V2)
{
	Vec3 vec;
	vec.m_x = (V.m_y * V2.m_z) - (V.m_z * V2.m_y);
	vec.m_y = (V.m_z * V2.m_x) - (V.m_x * V2.m_z);
	vec.m_z = (V.m_x * V2.m_y) - (V.m_y * V2.m_x);

	return vec;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�t�H���g�R���X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Vec3::Vec3()
	:m_x(0)
	,m_y(0)
	,m_z(0)
{

}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�l�w��R���X�g���N�^
//�b����  :X,Y,Z(float,float,float)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Vec3::Vec3(float x, float y, float z)
	: m_x(x)
	, m_y(y)
	, m_z(z)
{

}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�l�w��R���X�g���N�^
//�b����  :X,Y,Z(float,float,float)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Vec3::Vec3(float num)
	: m_x(num)
	, m_y(num)
	, m_z(num)
{

}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R�s�[�R���X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Vec3::Vec3(const Vec3& vec)
	: m_x(vec.m_x)
	, m_y(vec.m_y)
	, m_z(vec.m_z)
{
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Vec3::~Vec3()
{

}


/// <summary>
/// �x�N�g���̐��K��
/// </summary>
/// <returns>���K�����ꂽ�x�N�g��</returns>
Vec3 Vec3::Normalize()
{
	float length = std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);

	m_x /= length;
	m_y /= length;
	m_z /= length;

	return *this;
}

/// <summary>
/// �x�N�g���̑傫����Ԃ�
/// </summary>
/// <returns>�x�N�g���̑傫��</returns>
float ShunLib::Vec3::Length()
{
	float lenght = std::sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
	return lenght;
}



/*--[�ȉ��@���Z�q�̃I�[�o�[���[�h]--*/

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