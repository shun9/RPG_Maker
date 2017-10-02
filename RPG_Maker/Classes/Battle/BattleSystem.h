//************************************************/
//* @file  :BattleSystem.h
//* @brief :�퓬�̏���������N���X
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#pragma once
#include <map>
#include <SL_CommandInput.h>
#include <SL_KeyManager.h>
#include <SL_Texture.h>
#include "Action.h"
#include "../Data/DataBase.h"
#include "../Enemy/EnemyAction.h"
#include "../Player/Player.h"
struct EnemyData;

class BattleSystem
{
private:
	ShunLib::Texture* m_backGround;
	ShunLib::Texture* m_arrow;
	ShunLib::Vec2 m_arrowPos;

	Player* m_player;

	std::unique_ptr<EnemyGroupData> tmp;
	EnemyGroupData* m_enemy;
	ActionList m_enemyAction;

	//�v���C���[�̎��s����s���ꗗ
	std::multimap<int, Action*>m_actionList;
	std::multimap<int, void*>m_charactorList;

	std::vector<int>m_enemyHp;

	//�v���C���[�����s����s���̔ԍ�
	int m_actionNum;
	int m_targetNum;

	//���s���̍s��
	int m_exeAction;

	//�^�[�Q�b�g��I�𒆂��ǂ���
	bool m_isSelectTarget;

	//�s�������s�����ǂ���
	bool m_isExecuteAction;

	//�����ɐ����������ǂ���
	bool m_succesedEscape;

	//�L�[����
	ShunLib::CommandInput<ShunLib::KeyManager::KEY_CODE, BattleSystem>m_commandInput;
	ShunLib::CommandInput<ShunLib::KeyManager::KEY_CODE, BattleSystem>m_targetSelectInput;

	//�v���C���[�����������ǂ���
	bool m_isWinPlayer;


public:
	BattleSystem();
	~BattleSystem();

	void Start();

	//�s���̑I��
	bool SelectAction();

	//�I�������ړ�����
	void ShiftOption(int num);
	void ShiftTarget(int num);

	//�s����ς�
	void StackAction();

	//�s�������s����
	bool ExecuteAction();

	//�o�g�����I���������ǂ���
	bool IsEnded();

	//�`��
	void Draw(const ShunLib::Vec2& pos);

	//�키�L�����N�^�[��ݒ�
	void SetPlayer(Player* p) {m_player = p;}
	void SetEnemy(int id) {
		auto& db = DB_Enemy;
		m_enemy = DB_EnemyGroup.GetData(id);
		//HP��ۑ�
		for (int i = 0; i < (int)m_enemy->enemyList.size(); i++)
		{
			m_enemyHp.push_back(db.GetData(m_enemy->enemyList[i].first)->Param[EnemyData::Param::HP]);
		}
	}

	//�키�L�����N�^�[���擾
	Player* Player() { return m_player; }
	EnemyGroupData* Enemy() { return m_enemy; }

	void Escape() { m_succesedEscape = true; }
	bool IsEscape() { return m_succesedEscape; }

	int TakeDamageEnemy(int damage);
	EnemyData* GetTarget() {
		return DB_Enemy.GetData(m_enemy->enemyList[m_targetNum].first);
	}
private:
	bool SelectCommand();
	bool SelectTarget();
};


//�I������1��Ɉړ�����
class SelectUpCommand :public ShunLib::Command<BattleSystem>
{
public:
	SelectUpCommand() {}
	~SelectUpCommand() {}
	bool Execute(BattleSystem* obj)override;
};


//�I������1���Ɉړ�����
class SelectDownCommand :public ShunLib::Command<BattleSystem>
{
public:
	SelectDownCommand() {}
	~SelectDownCommand() {}
	bool Execute(BattleSystem* obj)override;
};


//�I���������肷��
class SelectDecideCommand :public ShunLib::Command<BattleSystem>
{
public:
	SelectDecideCommand() {}
	~SelectDecideCommand() {}
	bool Execute(BattleSystem* obj)override;
};

//�I������1��Ɉړ�����
class SelectUpTarget :public ShunLib::Command<BattleSystem>
{
public:
	SelectUpTarget() {}
	~SelectUpTarget() {}
	bool Execute(BattleSystem* obj)override;
};


//�I������1���Ɉړ�����
class SelectDownTarget :public ShunLib::Command<BattleSystem>
{
public:
	SelectDownTarget() {}
	~SelectDownTarget() {}
	bool Execute(BattleSystem* obj)override;
};


//�I���������肷��
class SelectDecideTarget :public ShunLib::Command<BattleSystem>
{
public:
	SelectDecideTarget() {}
	~SelectDecideTarget() {}
	bool Execute(BattleSystem* obj)override;
};

