//************************************************/
//* @file  :EnemyGroupDataHolder.h
//* @brief :�^�C���̏���ێ�����
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "EnemyData.h"
#include <map>

// �G�O���[�v�̏��
struct EnemyGroupData :public Data {

	// ��ʕ\�����W��EnemyData�̃��X�g
	std::vector<std::map<int, ShunLib::Vec2>> enemyList;
};
