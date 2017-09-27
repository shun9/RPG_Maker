//************************************************/
//* @file  :Tile.h
//* @brief :マップタイル
//* @date  :2017/09/27
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Vec2.h>

class Enemy;

class Tile
{
public:
	//タイルの1辺の長さ
	static const float SIZE;

private:
	int m_id;

public:
	Tile():m_id(-1) {}
	~Tile() {}

	//描画
	void Draw(const ShunLib::Vec2& pos, const ShunLib::Vec2& scale);

	void Id(int id) { m_id = id; }
	int Id() { return m_id; };
};
