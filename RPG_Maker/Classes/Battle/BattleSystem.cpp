//************************************************/
//* @file  :BattleSystem.cpp
//* @brief :�퓬�̏���������N���X
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#include "BattleSystem.h"
#include <SL_MacroConstants.h>
#include <SL_RandomNumber.h>
#include "../../Utils/EnemyService.h"
#include "../Player/Player.h"
#include "../Data/EnemyData.h"
#include "BattleText.h"
#include "../Data/DataBase.h"

using namespace ShunLib;

BattleSystem::BattleSystem() :
	m_player(nullptr),
	m_succesedEscape(false),
	m_isExecuteAction(false)
{
	m_backGround = new ShunLib::Texture(L"Image\\Prairie.png");
	m_arrow = new ShunLib::Texture(L"Image\\arrow.png");

	m_commandInput.SetCommand(KeyManager::KEY_CODE::UP, new SelectUpCommand);
	m_commandInput.SetCommand(KeyManager::KEY_CODE::DOWN, new SelectDownCommand);
	m_commandInput.SetCommand(KeyManager::KEY_CODE::SPACE, new SelectDecideCommand);

	m_targetSelectInput.SetCommand(KeyManager::KEY_CODE::RIGHT, new SelectUpTarget);
	m_targetSelectInput.SetCommand(KeyManager::KEY_CODE::LEFT, new SelectDownTarget);
	m_targetSelectInput.SetCommand(KeyManager::KEY_CODE::SPACE, new SelectDecideTarget);


	m_enemyAction.List().push_back(new EnemyAttackAction);

	m_arrowPos = { 0.0f,60.0f };
}


BattleSystem::~BattleSystem()
{
	DELETE_POINTER(m_backGround);
	DELETE_POINTER(m_arrow);
}


/// <summary>
/// �^�[�����Ƃ̏�����
/// </summary>
void BattleSystem::Start()
{
	m_actionNum = 0;
	m_exeAction = 0;
	m_targetNum = 0;
	m_isExecuteAction = false;
	m_succesedEscape = false;
	m_isSelectTarget = false;
}


/// <summary>
/// �s���̑I��
/// </summary>
/// <returns>�s�������܂�����true</returns>
bool BattleSystem::SelectAction()
{
	auto key = ShunLib::KeyManager::GetInstance();

	//���肵�����ǂ���
	bool isDecided = false;
	m_isExecuteAction = false;
	if (!m_isSelectTarget)
	{
		isDecided = SelectCommand();
	}
	else if (m_isSelectTarget)
	{
		isDecided = SelectTarget();
	}

	return isDecided;
}


/// <summary>
/// �I�������ړ�����
/// </summary>
/// <param name="num">�ړ�����l</param>
void BattleSystem::ShiftOption(int num)
{
	m_actionNum += num;
	int listSize = (int)(m_player->GetActionList().List().size()) - 1;

	if (m_actionNum < 0) {
		m_actionNum = listSize;
	}
	else if (m_actionNum > listSize) {
		m_actionNum = 0;
	}
}


/// <summary>
/// �^�[�Q�b�g��ύX
/// </summary>
/// <param name="num">�ړ�����l</param>
void BattleSystem::ShiftTarget(int num)
{
	m_targetNum += num;

	int listSize = (int)(m_enemy->enemyList.GetList().size()) - 1;

	if (m_targetNum < 0) {
		m_targetNum = listSize;
	}
	else if (m_targetNum > listSize) {
		m_targetNum = 0;
	}

	while (m_enemyHp[m_targetNum] <= 0)
	{
		m_targetNum += num;

		if (m_targetNum < 0) {
			m_targetNum = listSize;
		}
		else if (m_targetNum > listSize) {
			m_targetNum = 0;
		}
	}
}


/// <summary>
/// �s����ς�
/// </summary>
void BattleSystem::StackAction()
{
	m_actionList.clear();
	m_charactorList.clear();

	auto list = m_player->GetActionList().List();
	int spd = -1;// m_player->GetParam()[Player::PARAM::SPD];
	m_actionList.insert(std::make_pair(spd, list[m_actionNum]));
	m_charactorList.insert(std::make_pair(spd, m_player));
	m_isSelectTarget = list[m_actionNum]->ShouldSelectTarget();

	auto& db = DB_Enemy;
	ShunLib::RandomNumber rn;
	EnemyData* enemy;
	for (int i = 0; i < (int)(m_enemy->enemyList.GetList().size()); i++)
	{
		//����ł�G�̍s���͐ς܂Ȃ�
		if (m_enemyHp[i] > 0)
		{
			enemy = db.GetData(m_enemy->enemyList.GetList().at(i)->Id);
			int num = rn(0, m_enemyAction.List().size() - 1);
			m_actionList.insert(std::make_pair(enemy->Param[EnemyData::Param::DEX], m_enemyAction.List()[num]));
			m_charactorList.insert(std::make_pair(enemy->Param[EnemyData::Param::DEX], enemy));
		}
	}

	//�^�[�����Ƃɏ�����
	for (auto itr = m_actionList.begin(); itr != m_actionList.end(); itr++)
	{
		(*itr).second->Start();
	}

	m_isExecuteAction = true;
}


/// <summary>
/// �s�������s����
/// </summary>
/// <returns>���s���I�������true</returns>
bool BattleSystem::ExecuteAction()
{
	auto action = m_actionList.rbegin();
	auto charactor = m_charactorList.rbegin();

	//���ݎ��s���̍s���܂Ői�߂�
	for (int i = 0; i < m_exeAction; i++)
	{
		action++;
		charactor++;
	}

	//�s���̎��s
	bool isEnded = true;
	if (action != m_actionList.rend())
	{
		isEnded = action->second->Execute(this, (charactor)->second);

		//�s�����I������玟�̍s���Ɉڂ�
		if (isEnded)
		{
			//�v���C���[������ł�����I��
			if (m_player->IsDead())
			{
				return true;
			}

			auto next = (++action);
			//���̍s��������Ȃ珉����
			if (next != m_actionList.rend())
			{
				next->second->Start();
				isEnded = false;
				m_exeAction++;
			}
		}
	}

	return isEnded;
}

/// <summary>
/// �o�g�����I���������ǂ���
/// </summary>
/// <returns></returns>
bool BattleSystem::IsEnded()
{
	if (m_succesedEscape)
	{
		return true;
	}

	if (m_player->IsDead())
	{
		return true;
	}

	for (int i = 0; i < (int)m_enemyHp.size(); i++)
	{
		if (m_enemyHp[i] > 0)
		{
			return false;
		}
	}

	return true;
}


/// <summary>
/// �`��
/// </summary>
void BattleSystem::Draw(const ShunLib::Vec2 & pos)
{
	m_backGround->Draw(pos, ShunLib::Vec2(0.94f, 0.94f));

	auto text = BattleText::GetInstance();

	auto& ds = DB_Enemy;
	ShunLib::Vec2 enemyPos;
	EnemyData* enemy;

	int posNum[] = { 1,0,2 };
	int viewNum[] = { 0,1,2 };
	for (int i = 0; i < (int)(m_enemy->enemyList.GetList().size()); i++)
	{
		enemy = DB_Enemy.GetData(m_enemy->enemyList.GetList().at(posNum[i])->Id);
		if (m_enemyHp[i] > 0)
		{
			enemyPos = Vec2(50.0f+(200.0f*viewNum[i]), 100.0f);
			//enemyPos = m_enemy->enemyList.GetList().at(i)->Pos;
			enemy->Texture->Draw(enemyPos, Vec2(0.6f, 0.6f));
		}
	}

	if (m_isExecuteAction)
	{
		text->Draw(pos);
	}
	else {
		text->CommandDraw(pos);
		if (!m_isSelectTarget)
		{
			m_arrow->Draw(m_arrowPos*m_actionNum + ShunLib::Vec2(pos.m_x, 405.0f), ShunLib::Vec2(2.0f, 2.0f));
		}
		else
		{
			auto tarPos = m_enemy->enemyList.GetList().at(m_targetNum)->Pos;
			m_arrow->Draw(tarPos + ShunLib::Vec2(-50.0f, 0.0f), ShunLib::Vec2(2.0f, 2.0f));
		}
	}
}


/// <summary>
/// �G�Ƀ_���[�W��^����
/// </summary>
int BattleSystem::TakeDamageEnemy(int damage)
{
	int d = damage;
	d -= DB_Enemy.GetData(m_enemy->enemyList[m_targetNum].first)->Param[EnemyData::Param::DEF];
	if (d < 0) { d = 0; }
	m_enemyHp[m_targetNum] -= d;
	return d;
}

/// <summary>
/// �R�}���h�̑I��
/// </summary>
bool BattleSystem::SelectCommand()
{
	auto key = ShunLib::KeyManager::GetInstance();

	//���肵�����ǂ���
	bool isDecided = false;
	m_isExecuteAction = false;
	auto keyList = m_commandInput.GetKeyList();
	for (int i = 0; i < (int)keyList.size(); i++)
	{
		//�L�[��������Ă�������s
		if (key->IsTracker(keyList[i]))
		{
			isDecided = m_commandInput.HandleInput(keyList[i])->Execute(this);
		}

		//�s�������肵����true
		if (isDecided)
		{
			//�s����ς�
			StackAction();

			if (m_isSelectTarget)isDecided = false;
			break;
		}
	}
	return isDecided;
}

/// <summary>
/// �^�[�Q�b�g�I��
/// </summary>
bool BattleSystem::SelectTarget()
{
	auto key = ShunLib::KeyManager::GetInstance();

	//���肵�����ǂ���
	bool isDecided = false;
	m_isExecuteAction = false;
	auto keyList = m_targetSelectInput.GetKeyList();

	for (int i = 0; i < (int)keyList.size(); i++)
	{
		//�L�[��������Ă�������s
		if (key->IsTracker(keyList[i]))
		{
			isDecided = m_targetSelectInput.HandleInput(keyList[i])->Execute(this);
		}

		//���肵����^�[�Q�b�g��ݒ�
		if (isDecided)
		{
			auto list = m_player->GetActionList().List();
			list[m_actionNum]->Target(m_targetNum);
			m_isExecuteAction = true;
			break;
		}
	}
	return isDecided;
}




//�I������1��Ɉړ�����
bool SelectUpCommand::Execute(BattleSystem * obj)
{
	obj->ShiftOption(-1);
	return false;
}

//�I������1���Ɉړ�����
bool SelectDownCommand::Execute(BattleSystem * obj)
{
	obj->ShiftOption(+1);
	return false;
}

//�I���������肷��
bool SelectDecideCommand::Execute(BattleSystem * obj)
{
	return true;
}

//�^�[�Q�b�g��1��Ɉړ�����
bool SelectUpTarget::Execute(BattleSystem * obj)
{
	obj->ShiftTarget(+1);
	return false;
}

//�^�[�Q�b�g��1���Ɉړ�����
bool SelectDownTarget::Execute(BattleSystem * obj)
{
	obj->ShiftTarget(-1);
	return false;
}

//�^�[�Q�b�g������
bool SelectDecideTarget::Execute(BattleSystem * obj)
{
	return true;
}
