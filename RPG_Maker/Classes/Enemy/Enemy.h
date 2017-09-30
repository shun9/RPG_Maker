//************************************************/
//* @file  :Enemy.h
//* @brief :“G
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once
#include <wrl.h>

#include <windef.h>
#include <SL_Vec2.h>

class Enemy
{
public:

private:
	int m_id;

public:
	Enemy(){}
	~Enemy() {}

	//•`‰æ
	void Draw(const ShunLib::Vec2& pos, const ShunLib::Vec2& scale, RECT* rect = nullptr);

	void Id(int id) { m_id = id; }
	int Id() { return m_id; };
};
