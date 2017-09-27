//************************************************/
//* @file  :Map.h
//* @brief :�}�b�v�i�^�C���̏W���́j
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>

#include "Tile.h"

class Map
{
	//�}�b�v�T�C�Y
	static const int WIDTH;
	static const int HEIGHT;

private:
	std::vector<std::vector<Tile>>m_map;

public:
	Map();
	~Map();

	//�`��
	void Draw();
};