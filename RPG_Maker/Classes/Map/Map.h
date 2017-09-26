//************************************************/
//* @file  :Map.h
//* @brief :マップ（タイルの集合体）
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>

#include "Tile.h"

class Map
{
	//マップサイズ
	static const int WIDTH;
	static const int HEIGHT;

private:
	std::vector<std::vector<Tile>>m_map;

public:
	Map();
	~Map();

	//描画
	void Draw();
};