//************************************************/
//* @file  :BattleSystem.cpp
//* @brief :�퓬�̏���������N���X
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#include "BattleSystem.h"
#include <SL_MacroConstants.h>
#include "../Player/Player.h"
#include "../Data/EnemyData.h"
#include "BattleText.h"

using namespace ShunLib;

BattleSystem::BattleSystem():
	m_player(nullptr),
	m_enemy(nullptr),
	m_succesedEscape(false),
	m_isExecuteAction(false)
{
	m_backGround = new ShunLib::Texture(L"Image\\Prairie.png");
	m_arrow = new ShunLib::Texture(L"Image\\arrow.png");

	m_commandInput.SetCommand(KeyManager::KEY_CODE::UP, new SelectUpCommand);
	m_commandInput.SetCommand(KeyManager::KEY_CODE::DOWN, new SelectDownCommand);
	m_commandInput.SetCommand(KeyManager::KEY_CODE::SPACE, new SelectDecideCommand);

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
	m_isExecuteAction = false;
	m_succesedEscape = false;
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
			return true;
		}
	}
	return false;
}

/// <summary>
/// �I�������ړ�����
/// </summary>
/// <param name="num">�ړ�����l</param>
void BattleSystem::ShiftOption(int num)
{
	m_actionNum += num;
	int listSize = (int)(m_player->GetActionList().List().size()) - 1;

	if (m_actionNum < 0){
		m_actionNum = listSize;
	}
	else if (m_actionNum > listSize){
		m_actionNum = 0;
	}
}

/// <summary>
/// �s����ς�
/// </summary>
void BattleSystem::StackAction()
{
	m_actionList.clear();

	auto list = m_player->GetActionList().List();
	int spd = m_player->GetParam()[Player::PARAM::SPD];
	m_actionList.insert(std::make_pair(spd, list[m_actionNum]));

	for (int i = 0; i < (int)(2); i++)
	{
		m_actionList.insert(std::make_pair(0, m_enemyAction.List()[0]));
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

	//���ݎ��s���̍s���܂Ői�߂�
	for (int i = 0; i < m_exeAction; i++)
	{
		action++;
	}

	//�s���̎��s
	bool isEnded = true;
	if (action != m_actionList.rend())
	{
		isEnded = action->second->Execute(this);

		//�s�����I������玟�̍s���Ɉڂ�
		if (isEnded)
		{
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
	return false;
}


/// <summary>
/// �`��
/// </summary>
void BattleSystem::Draw(const ShunLib::Vec2 & pos)
{
	m_backGround->Draw(pos, ShunLib::Vec2(0.94f, 0.94f));

	auto text = BattleText::GetInstance();

	if (m_isExecuteAction)
	{
		text->Draw(pos);
	}
	else {
		text->CommandDraw(pos);
		m_arrow->Draw(m_arrowPos*m_actionNum + ShunLib::Vec2(pos.m_x, 405.0f), ShunLib::Vec2(2.0f, 2.0f));
	}

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
