//************************************************/
//* @file  :EnemyGroupDataHolder.h
//* @brief :�^�C���̏���ێ�����
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <SL_Singleton.h>
#include <SL_Texture.h>
#include <SL_ConstantNumber.h>
#include "EnemyDataHolder.h"
#include <SL_Vec2.h>

class Enemy;

// �G�O���[�v�̏��
struct EnemyGroupData {
	int Id;

	std::string Name;

	// ��ʕ\�����W��EnemyData�̃��X�g
	std::vector<std::pair<ShunLib::Vec2, EnemyData*>> enemyList;
};


// �G�O���[�v�̏���ێ�����
class EnemyGroupDataHolder :public ShunLib::Singleton<EnemyGroupDataHolder>
{
	friend ShunLib::Singleton<EnemyGroupDataHolder>;

private:
	// �G�O���[�v��ވꗗ
	std::vector<std::unique_ptr<EnemyGroupData>> m_enemyGroupData;

public:
	EnemyGroupDataHolder() {}
	~EnemyGroupDataHolder() {}

	//�f�[�^��ǉ�����
	int AddData(std::unique_ptr<EnemyGroupData> data) {
		m_enemyGroupData.push_back(move(data));
		return (int)(m_enemyGroupData.size()) - 1;
	}

	//�f�[�^����Ԃ�
	//�������nullptr
	EnemyGroupData* GetData(int id) {
		if (id > (int)(m_enemyGroupData.size()) - 1)return nullptr;
		return	m_enemyGroupData[id].get();
	}

	// �S�f�[�^�擾
	const std::vector<std::unique_ptr<EnemyGroupData>>& GetTileList() {
		return m_enemyGroupData;
	}
};
