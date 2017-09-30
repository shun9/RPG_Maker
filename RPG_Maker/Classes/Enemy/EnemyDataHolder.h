//************************************************/
//* @file  :EnemyDataHolder.h
//* @brief :�^�C���̏���ێ�����
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <string>
#include <SL_Singleton.h>
#include <SL_Texture.h>
#include <SL_ConstantNumber.h>

class Enemy;

// �G�̏��
struct EnemyData {

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

	int Id;

	std::string Name;

	// �G�摜
	std::unique_ptr<ShunLib::Texture> Texture;

	std::vector<int> Param;
};


// TODO:�e���v���[�g�N���X�ɂł�����
// �G�̏���ێ�����
class EnemyDataHolder :public ShunLib::Singleton<EnemyDataHolder>
{
	friend ShunLib::Singleton<EnemyDataHolder>;

private:
	//�G��ވꗗ
	std::vector<std::unique_ptr<EnemyData>> m_enemyData;

public:
	EnemyDataHolder() {}
	~EnemyDataHolder() {}

	//�f�[�^��ǉ�����
	int AddData(std::unique_ptr<EnemyData> data) {
		m_enemyData.push_back(move(data));
		return (int)(m_enemyData.size()) - 1;
	}

	//�f�[�^����Ԃ�
	//�������nullptr
	EnemyData* GetData(int id) {
		if (id > (int)(m_enemyData.size()) - 1)return nullptr;
		return	m_enemyData[id].get();
	}

	// �S�f�[�^�擾
	const std::vector<std::unique_ptr<EnemyData>>& GetTileList() {
		return m_enemyData;
	}
};
