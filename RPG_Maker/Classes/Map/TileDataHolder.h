//************************************************/
//* @file  :TileDataHolder.h
//* @brief :�^�C���̏���ێ�����
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include "../Map/Tile.h"

class Enemy;

//�^�C���̏��
struct TileData {
	//�^�C���摜
	ShunLib::Texture* m_texture;

	//�G�̃G���J�E���g��
	int m_encountRate;

	//�o������G�̍\���ꗗ
	Enemy** m_enemyGroup;

	//�ڂ��Ă���^�C���@�㉺���E
	Tile* m_contactTile[ShunLib::ConstantNumber::DIRECTION_2D::num];

	//�v���C���[���������Ƃ��o���邩�ǂ���
	//������Ȃ� true
	bool m_canMove;
};

//�^�C���̏���ێ�����
class TileDataHolder
{
private:
	//�^�C���ꗗ
	std::vector<TileData*> m_tileData;

public:
	TileDataHolder() {}
	~TileDataHolder() {}

	TileData* TileData(int id) { return m_tileData[id]; }
};
