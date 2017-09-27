//************************************************/
//* @file  :Tile.h
//* @brief :�}�b�v�^�C��
//* @date  :2017/09/27
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Vec2.h>

class Enemy;

class Tile
{
public:
	//�^�C����1�ӂ̒���
	static const float SIZE;

private:
	int m_id;

public:
	Tile():m_id(-1) {}
	~Tile() {}

	//�`��
	void Draw(const ShunLib::Vec2& pos, const ShunLib::Vec2& scale);

	void Id(int id) { m_id = id; }
	int Id() { return m_id; };
};
