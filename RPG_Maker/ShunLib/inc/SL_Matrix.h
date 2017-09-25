//************************************************/
//* @file  :Matrix.h
//* @brief :行列用のラップクラス
//* @date  :2017/02/21
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Vec3.h>

namespace ShunLib
{
	class Matrix
	{
		/*--[静的なやつら]--*/
	public:
		//単位行列
		static Matrix Identity;

	public:
		//平行移動行列
		static Matrix CreateTranslation(const Vec3& pos);

		//回転行列
		static Matrix CreateRotationX(float angle);
		static Matrix CreateRotationY(float angle);
		static Matrix CreateRotationZ(float angle);

		//拡大縮小行列
		static Matrix CreateScale(const Vec3& scale);
		static Matrix CreateScale(float scale);

		//転置行列を返す
		static Matrix Transpose(const Matrix& m);

		//逆行列を返す
		static Matrix Inverse(const Matrix& m);

		//射影行列
		static Matrix CreateProj(float fov,
								 float aspectRatio,
							     float nearPlane,
							     float farPlane);

		// ビュー行列の作成
		static Matrix CreateLookAt(
			const Vec3& eye,
			const Vec3& target,
			const Vec3& up);


		/*--[静的ではないやつら]--*/
	public:
		float m_value[4][4];

	public:
		Matrix();
		Matrix(const Matrix& M);
		~Matrix();


		/*--[演算子のオーバーロード]--*/
		Matrix& operator=(const Matrix& M);
		Matrix operator+(const Matrix& M);
		Matrix operator-(const Matrix& M);
		Matrix operator*(const Matrix& M);
		Matrix operator*(int num);
	};
}	
ShunLib::Matrix operator*(const ShunLib::Matrix& M, const ShunLib::Matrix& M2);
