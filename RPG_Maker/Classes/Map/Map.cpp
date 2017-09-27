//************************************************/
//* @file  :Map.cpp
//* @brief :�}�b�v�i�^�C���̏W���́j
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#include "Map.h"
#include "TileDataHolder.h"

const int Map::WIDTH = 32;
const int Map::HEIGHT = 32;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Map::Map()
{
	m_scrollNum = { 0.0f,0.0f };

	m_map.resize(HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
	{
		m_map[i].resize(WIDTH);
	}
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
			m_map[i][j].Draw(pos - m_scrollNum, Vec2::One);
		}
	}
}

//bool Map::CanMoveSpecifiedDir(ShunLib::ConstantNumber::DIRECTION_2D dir)
//{
//	//�w������̃^�C��
//	Tile* tile = m_contactTile[dir];
//
//	//�^�C����������ΐi�߂Ȃ�
//	if (tile == nullptr)
//	{
//		return false;
//	}
//
//	return tile->CanMove();
//}