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

class Enemy;

// �G�̏��
struct EnemyGroupAloneData :public Data{
	int Id;
	ShunLib::Vec2 Pos;
};