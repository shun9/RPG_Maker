//************************************************/
//* @file  :SL_Conversion.h
//* @brief :ShunLibとDirectXTKの変換関数
//* @date  :2017/07/10
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Vec3.h>
#include <SL_Vec2.h>
#include <SL_Matrix.h>
#include <SimpleMath.h>


namespace ShunLib
{
	/*--[２次元ベクトルの変換]--*/
	using Vector2 = DirectX::SimpleMath::Vector2;

	//SL_Vec2 -> DirectXTK Vector2
	inline Vector2 ConvertTK(const Vec2& vec) {
		Vector2 v;
		v.x = vec.m_x;
		v.y = vec.m_y;

		return v;
	}

	//DirectXTK Vector2 -> SL_Vec2
	inline Vec2 ConvertTK(const Vector2& vec) {
		Vec2 v;
		v.m_x = vec.x;
		v.m_y = vec.y;
		return v;
	}


	/*--[３次元ベクトルの変換]--*/
	using Vector3 = DirectX::SimpleMath::Vector3;

	//SL_Vec3 -> DirectXTK Vector3
	inline Vector3 ConvertTK(const Vec3& vec) {
		Vector3 v;
		v.x = vec.m_x;
		v.y = vec.m_y;
		v.z = vec.m_z;

		return v;
	}

	//DirectXTK Vector3 -> SL_Vec3
	inline Vec3 ConvertTK(const Vector3& vec) {
		Vec3 v;
		v.m_x = vec.x;
		v.m_y = vec.y;
		v.m_z = vec.z;
		return v;
	}


	/*--[行列の変換]--*/
	using MatrixD = DirectX::SimpleMath::Matrix;

	//DirectXTK Matrix -> SL_Matrix
	inline MatrixD ConvertTK(const Matrix& mat) {
		MatrixD m;
		m._11 = mat.m_value[0][0];  m._21 = mat.m_value[1][0];  m._31 = mat.m_value[2][0];  m._41 = mat.m_value[3][0];
		m._12 = mat.m_value[0][1];  m._22 = mat.m_value[1][1];  m._32 = mat.m_value[2][1];  m._42 = mat.m_value[3][1];
		m._13 = mat.m_value[0][2];  m._23 = mat.m_value[1][2];  m._33 = mat.m_value[2][2];  m._43 = mat.m_value[3][2];
		m._14 = mat.m_value[0][3];  m._24 = mat.m_value[1][3];  m._34 = mat.m_value[2][3];  m._44 = mat.m_value[3][3];

		return m;
	}

	//SL_Matrix -> DirectXTK Matrix
	inline Matrix ConvertTK(const MatrixD& mat) {
		Matrix m;
		m.m_value[0][0] = mat._11;  m.m_value[1][0] = mat._21;  m.m_value[2][0] = mat._31;  m.m_value[3][0] = mat._41;
		m.m_value[0][1] = mat._12;  m.m_value[1][1] = mat._22;  m.m_value[2][1] = mat._32;  m.m_value[3][1] = mat._42;
		m.m_value[0][2] = mat._13;  m.m_value[1][2] = mat._23;  m.m_value[2][2] = mat._33;  m.m_value[3][2] = mat._43;
		m.m_value[0][3] = mat._14;  m.m_value[1][3] = mat._24;  m.m_value[2][3] = mat._34;  m.m_value[3][3] = mat._44;

		return m;
	}

}