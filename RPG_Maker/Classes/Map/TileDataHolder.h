//************************************************/
//* @file  :TileDataHolder.h
//* @brief :�^�C���̏���ێ�����
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_Singleton.h>
#include <SL_Texture.h>
#include <SL_ConstantNumber.h>

class Enemy;
class Tile;

//�^�C���̏��
struct TileData {
	//�^�C���摜
	ShunLib::Texture* texture;

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
	std::vector<TileData> m_tileData;

public:
	TileDataHolder() {}
	~TileDataHolder() {}

	//�f�[�^��ǉ�����
	//
	int AddData(TileData* data) {
		m_tileData.push_back(*data);
		return (int)(m_tileData.size()) - 1;
	}

	TileData* GetData(int id) {
		return	&m_tileData[id];
	}
};