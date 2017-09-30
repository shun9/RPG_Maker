//************************************************/
//* @file  :EnemyGroupDataHolder.h
//* @brief :�^�C���̏���ێ�����
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "EnemyData.h"

// �G�O���[�v�̏��
struct EnemyGroupData :public Data {

	// ��ʕ\�����W��EnemyData�̃��X�g
	std::vector<std::pair<ShunLib::Vec2, EnemyData*>> enemyList;
};
