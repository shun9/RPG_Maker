#pragma once

namespace ShunLib
{
	class Vec4
	{
	public:
		float m_x;
		float m_y;
		float m_z;
		float m_w;

	public:
		Vec4()                                  :m_x(0.0f),m_y(0.0f),m_z(0.0f),m_w(0.0f) {}
		Vec4(float x, float y, float z,float w) :m_x(x), m_y(y), m_z(z), m_w(w) {}
		Vec4(float num)                         :m_x(num), m_y(num), m_z(num), m_w(num) {}
		Vec4(const Vec4& vec)                   :m_x(vec.m_x), m_y(vec.m_y), m_z(vec.m_z), m_w(vec.m_w) {}

		~Vec4() {}

		Vec4 Normalize();

		/*--[演算子のオーバーロード]--*/
		Vec4& operator= (const Vec4& V);
		Vec4& operator+=(const Vec4& V);
		Vec4& operator-=(const Vec4& V);
		Vec4& operator*=(float num);
		Vec4& operator/=(float num);

		Vec4& operator+();
		Vec4 operator-();
	};
}

//演算子のオーバーロード
bool  operator==(const ShunLib::Vec4& V, const ShunLib::Vec4& V2);
ShunLib::Vec4 operator+(const ShunLib::Vec4& V, const ShunLib::Vec4& V2);
ShunLib::Vec4 operator-(const ShunLib::Vec4& V, const ShunLib::Vec4& V2);
ShunLib::Vec4 operator*(const ShunLib::Vec4& V, float num);
ShunLib::Vec4 operator/(const ShunLib::Vec4& V, float num);
