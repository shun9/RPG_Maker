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

class Player;
struct EnemyData;

class BattleSystem
{
private:
	ShunLib::Texture* m_backGround;
	ShunLib::Texture* m_arrow;
	ShunLib::Vec2 m_arrowPos;

	Player* m_player;
	EnemyGroupData* m_enemy;
	ActionList m_enemyAction;

	//�v���C���[�̎��s����s���ꗗ
	std::multimap<int, Action*>m_actionList;

	//�v���C���[�����s����s���̔ԍ�
	int m_actionNum;

	//���s���̍s��
	int m_exeAction;

	//�����ɐ����������ǂ���
	bool m_succesedEscape;

	//�L�[����
	ShunLib::CommandInput<ShunLib::KeyManager::KEY_CODE, BattleSystem>m_commandInput;

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

	//�s����ς�
	void StackAction();

	//�s�������s����
	bool ExecuteAction();

	//�o�g�����I���������ǂ���
	bool IsEnded();

	//�`��
	void Draw(const ShunLib::Vec2& pos);

	//�키�L�����N�^�[��ݒ�
	void SetPlayer(Player* p) { m_player = p; }
	void SetEnemy(int id) { m_enemy = DB_EnemyGroup.GetData(id); }

	//�키�L�����N�^�[���擾
	Player* Player() { return m_player; }
	EnemyGroupData* Enemy() { return m_enemy; }

private:
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

