//************************************************/
//* @file  :EnemyGroupDataHolder.h
//* @brief :�^�C���̏���ێ�����
//* @date  :2017/09/26
//* @author:K.Yamamoto
//************************************************/
#pragma once
#include "EnemyGroupAloneData.h"
#include <memory>
#include "DataHolder.h"

static const int GROUP_ENEMY_MAX = 3;

// �G�O���[�v�̏��
struct EnemyGroupData :public Data {

	// ��ʕ\�����W��EnemyData�̃��X�g
	DataHolder<EnemyGroupAloneData> enemyList;
};