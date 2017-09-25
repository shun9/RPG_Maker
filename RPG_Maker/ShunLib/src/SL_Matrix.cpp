//************************************************/
//* @file  :Matrix.cpp
//* @brief :行列用のラップクラス
//* @date  :2017/02/22
//* @author:S.Katou
//************************************************/
#include "SL_Matrix.h"

#include <cmath>
#include <functional>

#include <d3d11.h>
#include <DirectXMath.h>
#include <SL_Conversion.h>

using namespace ShunLib;

Matrix Matrix::Identity;

//＋ーーーーーーーーーーーーーー＋
//｜機能  :平行移動行列の作成
//｜引数  :移動後の位置(Vec3)
//｜戻り値:行列(Matrix)
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateTranslation(const Vec3& pos)
{
	Matrix matrix;
	matrix.m_value[3][0] += pos.m_x;
	matrix.m_value[3][1] += pos.m_y;
	matrix.m_value[3][2] += pos.m_z;

	return matrix;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :Ｘ軸回転行列の作成
//｜引数  :角度(float)
//｜戻り値:行列(Matrix)
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateRotationX(float angle)
{

	Matrix matrix;
	matrix.m_value[1][1] =  cos(ToRadian(angle));
	matrix.m_value[1][2] = -sin(ToRadian(angle));
	matrix.m_value[2][1] =  sin(ToRadian(angle));
	matrix.m_value[2][2] =  cos(ToRadian(angle));

	return matrix;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :Ｙ軸回転行列の作成
//｜引数  :角度(float)
//｜戻り値:行列(Matrix)
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateRotationY(float angle)
{
	Matrix matrix;
	matrix.m_value[0][0] =  cos(ToRadian(angle));
	matrix.m_value[0][2] =  sin(ToRadian(angle));
	matrix.m_value[2][0] = -sin(ToRadian(angle));
	matrix.m_value[2][2] =  cos(ToRadian(angle));

	return matrix;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :Ｚ軸回転行列の作成
//｜引数  :角度(float)
//｜戻り値:行列(Matrix)
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateRotationZ(float angle)
{
	Matrix matrix;
	matrix.m_value[0][0] =  cos(ToRadian(angle));
	matrix.m_value[0][1] = -sin(ToRadian(angle));
	matrix.m_value[1][0] =  sin(ToRadian(angle));
	matrix.m_value[1][1] =  cos(ToRadian(angle));

	return matrix;
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :拡大縮小行列の作成
//｜引数  :拡大率(Vec3)
//｜戻り値:行列(Matrix)
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateScale(const Vec3& scale)
{

	Matrix matrix;
	matrix.m_value[0][0] *= scale.m_x;
	matrix.m_value[1][1] *= scale.m_y;
	matrix.m_value[2][2] *= scale.m_z;

	return matrix;
}



//＋ーーーーーーーーーーーーーー＋
//｜機能  :拡大縮小行列の作成
//｜引数  :拡大率(float)
//｜戻り値:行列(Matrix)
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateScale(float scale)
{
	Matrix matrix;
	matrix.m_value[0][0] *= scale;
	matrix.m_value[1][1] *= scale;
	matrix.m_value[2][2] *= scale;

	return matrix;
}

Matrix ShunLib::Matrix::Transpose(const Matrix & m)
{
	Matrix mat;

	mat.m_value[0][0] = m.m_value[0][0];	mat.m_value[1][0] = m.m_value[0][1];	mat.m_value[2][0] = m.m_value[0][2];	mat.m_value[3][0] = m.m_value[0][3];
	mat.m_value[0][1] = m.m_value[1][0];	mat.m_value[1][1] = m.m_value[1][1];	mat.m_value[2][1] = m.m_value[1][2];	mat.m_value[3][1] = m.m_value[1][3];
	mat.m_value[0][2] = m.m_value[2][0];	mat.m_value[1][2] = m.m_value[2][1];	mat.m_value[2][2] = m.m_value[2][2];	mat.m_value[3][2] = m.m_value[2][3];
	mat.m_value[0][3] = m.m_value[3][0];	mat.m_value[1][3] = m.m_value[3][1];	mat.m_value[2][3] = m.m_value[3][2];	mat.m_value[3][3] = m.m_value[3][3];

	return mat;
}

Matrix ShunLib::Matrix::Inverse(const Matrix & m)
{
	Matrix mat = m;
	Matrix identity = Matrix::Identity;
	Matrix inverse;

	float buf; //一時的なデータを蓄える
	int n = 4;  //配列の次数

	//掃き出し法
	for (int i = 0; i<n; i++) 
	{
		buf = 1.0f / mat.m_value[i][i];
		for (int j = 0; j<n; j++) 
		{
			mat.m_value[i][j] *= buf;
			inverse.m_value[i][j] *= buf;
		}

		for (int j = 0; j<n; j++) 
		{
			if (i != j) 
			{
				buf = mat.m_value[j][i];
				for (int k = 0; k<n; k++) 
				{
					mat.m_value[j][k] -= mat.m_value[i][k] * buf;
					inverse.m_value[j][k] -= inverse.m_value[i][k] * buf;
				}
			}
		}
	}

	return inverse;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :射影行列の作成
//｜引数  :視野角　　　　　　(float)
//｜引数  :アスペクト比　　　(float)
//｜引数  :近クリップ面の距離(float)
//｜引数  :遠クリップ面の距離(float)
//｜戻り値:射影行列(Matrix)
//＋ーーーーーーーーーーーーーー＋
Matrix Matrix::CreateProj(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	using namespace DirectX;

	Matrix proj;

	auto projD = XMMatrixPerspectiveFovRH(fov, aspectRatio, nearPlane, farPlane);

	std::function<float(XMVECTOR)> GetX = XMVectorGetX;
	std::function<float(XMVECTOR)> GetY = XMVectorGetY;
	std::function<float(XMVECTOR)> GetZ = XMVectorGetZ;
	std::function<float(XMVECTOR)> GetW = XMVectorGetW;

	proj.m_value[0][0] = GetX(projD.r[0]);	proj.m_value[1][0] = GetX(projD.r[1]);	proj.m_value[2][0] = GetX(projD.r[2]);	proj.m_value[3][0] = GetX(projD.r[3]);
	proj.m_value[0][1] = GetY(projD.r[0]);	proj.m_value[1][1] = GetY(projD.r[1]);	proj.m_value[2][1] = GetY(projD.r[2]);	proj.m_value[3][1] = GetY(projD.r[3]);
	proj.m_value[0][2] = GetZ(projD.r[0]);	proj.m_value[1][2] = GetZ(projD.r[1]);	proj.m_value[2][2] = GetZ(projD.r[2]);	proj.m_value[3][2] = GetZ(projD.r[3]);
	proj.m_value[0][3] = GetW(projD.r[0]);	proj.m_value[1][3] = GetW(projD.r[1]);	proj.m_value[2][3] = GetW(projD.r[2]);	proj.m_value[3][3] = GetW(projD.r[3]);

	return proj;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :ビュー行列の作成
//｜引数  :カメラの位置　　　(Vec3)
//｜引数  :カメラの注視点　　(Vec3)
//｜引数  :カメラの上方向    (Vec3)
//｜戻り値:ビュー行列		 (Matrix)
//＋ーーーーーーーーーーーーーー＋
Matrix ShunLib::Matrix::CreateLookAt(const Vec3& eye, const Vec3& target, const Vec3& up)
{
	
	Vec3 x;
	Vec3 y;
	Vec3 z = eye - target;

	//方向の正規化
	z = z.Normalize();

	//x軸を求める
	x = Vec3::Cross(up, z);
	x = x.Normalize();

	//y軸を求める
	y = Vec3::Cross(z, x);

	Vec3 negEye = eye * -1.0f;

	float tx = Vec3::Dot(x, negEye);
	float ty = Vec3::Dot(y, negEye);
	float tz = Vec3::Dot(z, negEye);

	Matrix view;
	view.m_value[0][0] = x.m_x;	view.m_value[1][0] = x.m_y;	view.m_value[2][0] = x.m_z;	view.m_value[3][0] = tx;
	view.m_value[0][1] = y.m_x;	view.m_value[1][1] = y.m_y;	view.m_value[2][1] = y.m_z;	view.m_value[3][1] = ty;
	view.m_value[0][2] = z.m_x;	view.m_value[1][2] = z.m_y;	view.m_value[2][2] = z.m_z;	view.m_value[3][2] = tz;
	view.m_value[0][3] = 0    ;	view.m_value[1][3] = 0;		view.m_value[2][3] = 0;		view.m_value[3][3] = 1;

	return view;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デフォルトコンストラクタ
//＋ーーーーーーーーーーーーーー＋
Matrix::Matrix()
{

	float matrix[4][4] =
	{
		{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
	};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_value[i][j] = matrix[i][j];
		}
	}

}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :コピーコンストラクタ
//＋ーーーーーーーーーーーーーー＋
Matrix::Matrix(const Matrix& M)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->m_value[i][j] = M.m_value[i][j];
		}
	}
}



//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Matrix::~Matrix()
{

}


/*--[以下演算子のオーバーロード]--*/

Matrix& Matrix::operator=(const Matrix& M)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->m_value[i][j] = M.m_value[i][j];
		}
	}

	return *this;
}


Matrix Matrix::operator+(const Matrix& M)
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.m_value[i][j] = this->m_value[i][j] + M.m_value[i][j];
		}
	}

	return m;

	// TODO: return ステートメントをここに挿入します
}

Matrix Matrix::operator-(const Matrix& M)
{
	Matrix m;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m.m_value[i][j]=this->m_value[i][j] - M.m_value[i][j];
		}
	}
	return m;
}

Matrix Matrix::operator*(const Matrix& M)
{
	Matrix m;

	// １行目の計算
	float x = this->m_value[0][0];
	float y = this->m_value[0][1];
	float z = this->m_value[0][2];
	float w = this->m_value[0][3];
	m.m_value[0][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	m.m_value[0][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	m.m_value[0][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	m.m_value[0][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);

	// ２行目の計算
	x = this->m_value[1][0];
	y = this->m_value[1][1];
	z = this->m_value[1][2];
	w = this->m_value[1][3];
	m.m_value[1][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	m.m_value[1][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	m.m_value[1][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	m.m_value[1][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);

	// ３行目の計算
	x = this->m_value[2][0];
	y = this->m_value[2][1];
	z = this->m_value[2][2];
	w = this->m_value[2][3];
	m.m_value[2][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	m.m_value[2][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	m.m_value[2][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	m.m_value[2][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);

	// ４行目の計算
	x = this->m_value[3][0];
	y = this->m_value[3][1];
	z = this->m_value[3][2];
	w = this->m_value[3][3];
	m.m_value[3][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	m.m_value[3][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	m.m_value[3][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	m.m_value[3][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);

	return m;
}

Matrix Matrix::operator*(int num)
{
	Matrix m;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j  < 4; j ++)
		{
			m.m_value[i][j]=this->m_value[i][j] * num;
		}
	}

	return m;
}

Matrix operator*(const Matrix & M, const Matrix & M2)
{
	Matrix m;

	// １行目の計算
	float x = M2.m_value[0][0];
	float y = M2.m_value[0][1];
	float z = M2.m_value[0][2];
	float w = M2.m_value[0][3];
	m.m_value[0][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	m.m_value[0][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	m.m_value[0][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	m.m_value[0][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);

	// ２行目の計算
	x = M2.m_value[1][0];
	y = M2.m_value[1][1];
	z = M2.m_value[1][2];
	w = M2.m_value[1][3];
	m.m_value[1][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	m.m_value[1][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	m.m_value[1][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	m.m_value[1][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);

	// ３行目の計算
	x = M2.m_value[2][0];
	y = M2.m_value[2][1];
	z = M2.m_value[2][2];
	w = M2.m_value[2][3];
	m.m_value[2][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	m.m_value[2][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	m.m_value[2][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	m.m_value[2][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);

	// ４行目の計算
	x = M2.m_value[3][0];
	y = M2.m_value[3][1];
	z = M2.m_value[3][2];
	w = M2.m_value[3][3];
	m.m_value[3][0] = (M.m_value[0][0] * x) + (M.m_value[1][0] * y) + (M.m_value[2][0] * z) + (M.m_value[3][0] * w);
	m.m_value[3][1] = (M.m_value[0][1] * x) + (M.m_value[1][1] * y) + (M.m_value[2][1] * z) + (M.m_value[3][1] * w);
	m.m_value[3][2] = (M.m_value[0][2] * x) + (M.m_value[1][2] * y) + (M.m_value[2][2] * z) + (M.m_value[3][2] * w);
	m.m_value[3][3] = (M.m_value[0][3] * x) + (M.m_value[1][3] * y) + (M.m_value[2][3] * z) + (M.m_value[3][3] * w);

	return m;
}
