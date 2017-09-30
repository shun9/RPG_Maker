//************************************************/
//* @file  :Tile.h
//* @brief :�}�b�v�^�C��
//* @date  :2017/09/27
//* @author:S.Katou
//************************************************/
#pragma once
#include <wrl.h>

#include <windef.h>
#include <SL_Vec2.h>

class Enemy;

class Tile
{
public:
	//�^�C����1�ӂ̒���
	static const float SIZE;

	//�����Ȃ��^�C��
	static const int NONE;

	// �p�X
	static const wchar_t* PATH;

private:
	int m_id;

public:
	Tile():m_id(Tile::NONE) {}
	~Tile() {}

	//�`��
	void Draw(const ShunLib::Vec2& pos, const ShunLib::Vec2& scale, RECT* rect = nullptr);

	void Id(int id) { m_id = id; }
	int Id() { return m_id; };
};
