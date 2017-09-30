//************************************************/
//* @file  :TileDataHolder.h
//* @brief :�^�C���̏���ێ�����
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <SL_Texture.h>
#include "Data.h"

//�^�C���̏��
struct TileData :public Data{
	//�^�C���摜
	std::unique_ptr<ShunLib::Texture> texture;

	//�G�̃G���J�E���g��
	int encountRate;

	//�o������G�̍\���ꗗ ID
	std::vector<int> enemyGroup;

	//�v���C���[���������Ƃ��o���邩�ǂ���
	//������Ȃ� true
	bool canMove;
};