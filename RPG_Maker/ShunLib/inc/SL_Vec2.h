//************************************************/
//* @file  :SL_Vec2.h
//* @brief :2次元ベクトル用クラス
//* @date  :2017/07/04
//* @author:S.Katou
//************************************************/

// 多重インクルード防止
#pragma once

// 名前空間使用
namespace ShunLib
{
	// Vec2クラス
	class Vec2
	{
	public:
		static const Vec2 Zero;	 //(0,0)
		static const Vec2 One;   //(1,1)
		static const Vec2 UnitX; //(1,0)
		static const Vec2 UnitY; //(0,1)

	public:
		float m_x;
		float m_y;

	public:
		Vec2();
		Vec2(float x, float y);
		~Vec2();

		/*--[演算子のオーバーロード]--*/
		Vec2& operator=(const Vec2& V);
		Vec2 operator+ (const Vec2& V);
		Vec2 operator- (const Vec2& V);
		Vec2 operator* (int num      );
		Vec2 operator* (float num    );
		Vec2 operator* (double num   );
	};
}