//************************************************/
//* @file  :Map.cpp
//* @brief :�}�b�v�i�^�C���̏W���́j
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#include "Map.h"

const int Map::WIDTH = 128;
const int Map::HEIGHT = 128;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Map::Map()
{
	m_map.resize(HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
	{
		m_map[i].resize(WIDTH);
	}
	int a = 0;
	a++;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Map::~Map()
{

}

/// <summary>
/// �`��
/// </summary>
void Map::Draw()
{
	using namespace ShunLib;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			Vec2 pos(i*Tile::SIZE, j*Tile::SIZE);
			m_map[i][j].Draw(pos,Vec2::One);
		}
	}
}
