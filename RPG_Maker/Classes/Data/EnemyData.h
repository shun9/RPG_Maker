//************************************************/
//* @file  :EnemyDataHolder.h
//* @brief :�^�C���̏���ێ�����
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <SL_Texture.h>
#include "Data.h"
#include "../Battle/Action.h"

class Enemy;

// �G�̏��
struct EnemyData :public Data{
public:
	enum Param {
		HP,
		MP,
		ATK,
		DEF,
		DEX,
		EVA,
		EXP,
		MONEY,
		length
	};

	// �G�摜
	std::unique_ptr<ShunLib::Texture> Texture;

	std::vector<int> Param;
};