//************************************************/
//* @file  :BattleSystem.cpp
//* @brief :戦闘の処理をするクラス
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#include "BattleSystem.h"
#include <SL_MacroConstants.h>
#include "../Player/Player.h"
#include "../Data/EnemyData.h"

using namespace ShunLib;

BattleSystem::BattleSystem():
	m_player(nullptr),
	m_enemy(nullptr),
	m_succesedEscape(false)
{
	m_backGround = new ShunLib::Texture(L"Image\\Prairie.png");
	m_arrow = new ShunLib::Texture(L"Image\\arrow.png");

	m_commandInput.SetCommand(KeyManager::KEY_CODE::UP, new SelectUpCommand);
	m_commandInput.SetCommand(KeyManager::KEY_CODE::DOWN, new SelectDownCommand);
	m_commandInput.SetCommand(KeyManager::KEY_CODE::SPACE, new SelectDecideCommand);

	m_enemyAction.List().push_back(new EnemyAttackAction);
	m_arrowPos = { 0.0f,100.0f };
}

BattleSystem::~BattleSystem()
{
	DELETE_POINTER(m_backGround);
	DELETE_POINTER(m_arrow);
}

void BattleSystem::Start()
{
	m_actionNum = 0;
	m_exeAction = 0;
	m_succesedEscape = false;
}

/// <summary>
/// 行動の選択
/// </summary>
/// <returns>行動が決まったらtrue</returns>
bool BattleSystem::SelectAction()
{
	auto key = ShunLib::KeyManager::GetInstance();

	//決定したかどうか
	bool isDecided = false;

	auto keyList = m_commandInput.GetKeyList();
	for (int i = 0; i < (int)keyList.size(); i++)
	{
		//キーが押されていたら実行
		if (key->IsTracker(keyList[i]))
		{
			isDecided = m_commandInput.HandleInput(keyList[i])->Execute(this);
		}

		//行動が決定したらtrue
		if (isDecided)
		{
			//行動を積む
			StackAction();
			return true;
		}
	}
	return false;
}

/// <summary>
/// 選択肢を移動する
/// </summary>
/// <param name="num">移動する値</param>
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
/// 行動を積む
/// </summary>
void BattleSystem::StackAction()
{
	auto list = m_player->GetActionList().List();
	int spd = m_player->GetParam()[Player::PARAM::SPD];
	m_actionList.insert(std::make_pair(spd, list[m_actionNum]));

	//auto enemyList = m_enemy->enemyList;
	for (int i = 0; i < (int)(2); i++)
	{
		m_actionList.insert(std::make_pair(0, m_enemyAction.List()[0]));
	}
}

/// <summary>
/// 行動を実行する
/// </summary>
/// <returns>実行が終わったらtrue</returns>
bool BattleSystem::ExecuteAction()
{
	auto action = m_actionList.rbegin();

	//現在実行中の行動まで進める
	for (int i = 0; i < m_exeAction; i++)
	{
		action++;
	}

	//行動の実行
	bool isEnded = true;
	if (action != m_actionList.rend())
	{
		isEnded = action->second->Execute(this);

		//行動が終わったら次の行動に移る
		if (isEnded)
		{
			m_exeAction++;
			isEnded = false;
		}
	}
	return isEnded;
}

/// <summary>
/// バトルが終了したかどうか
/// </summary>
/// <returns></returns>
bool BattleSystem::IsEnded()
{
	return true;
}

/// <summary>
/// 描画
/// </summary>
void BattleSystem::Draw(const ShunLib::Vec2 & pos)
{
	m_backGround->Draw(pos, ShunLib::Vec2(0.8f, 0.8f));
	m_arrow->Draw(m_arrowPos*m_actionNum+pos, ShunLib::Vec2(2.0f, 2.0f));
}


//選択肢を1つ上に移動する
bool SelectUpCommand::Execute(BattleSystem * obj)
{
	obj->ShiftOption(-1);
	return false;
}

//選択肢を1つ下に移動する
bool SelectDownCommand::Execute(BattleSystem * obj)
{
	obj->ShiftOption(+1);
	return false;
}

//選択肢を決定する
bool SelectDecideCommand::Execute(BattleSystem * obj)
{
	return true;
}
