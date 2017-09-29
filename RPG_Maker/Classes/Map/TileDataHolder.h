//************************************************/
//* @file  :TileDataHolder.h
//* @brief :�^�C���̏���ێ�����
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <SL_Singleton.h>
#include <SL_Texture.h>
#include <SL_ConstantNumber.h>
#include "Tile.h"

class Enemy;
class Tile;

//�^�C���̏��
struct TileData {
	//�^�C���摜
	std::unique_ptr<ShunLib::Texture> texture;

	//�G�̃G���J�E���g��
	int encountRate;

	//�o������G�̍\���ꗗ
	Enemy** enemyGroup;

	//�v���C���[���������Ƃ��o���邩�ǂ���
	//������Ȃ� true
	bool canMove;
};


//�^�C���̏���ێ�����
class TileDataHolder:public ShunLib::Singleton<TileDataHolder>
{
	friend ShunLib::Singleton<TileDataHolder>;

private:
	//�^�C����ވꗗ
	std::vector<std::unique_ptr<TileData>> m_tileData;

public:
	TileDataHolder() {}
	~TileDataHolder() {}

	//�f�[�^��ǉ�����
	int AddData(std::unique_ptr<TileData> data) {
		m_tileData.push_back(move(data));
		return (int)(m_tileData.size()) - 1;
	}

	//�f�[�^����Ԃ�
	//�������nullptr
	TileData* GetData(int id) {
		if (id > (int)(m_tileData.size()) - 1)return nullptr;
		if (id == Tile::NONE)return nullptr;
		return	m_tileData[id].get();
	}

	// �S�f�[�^�擾
	const std::vector<std::unique_ptr<TileData>>& GetTileList() {
		return m_tileData;
	}
};
