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
/// ターンごとの初期化
/// </summary>
void BattleSystem::Start()
{
	m_actionNum = 0;
	m_exeAction = 0;
	m_isExecuteAction = false;
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
	m_isExecuteAction = false;
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
	m_actionList.clear();

	auto list = m_player->GetActionList().List();
	int spd = m_player->GetParam()[Player::PARAM::SPD];
	m_actionList.insert(std::make_pair(spd, list[m_actionNum]));

	for (int i = 0; i < (int)(2); i++)
	{
		m_actionList.insert(std::make_pair(0, m_enemyAction.List()[0]));
	}

	//ターンごとに初期化
	for (auto itr = m_actionList.begin(); itr != m_actionList.end(); itr++)
	{
		(*itr).second->Start();
	}

	m_isExecuteAction = true;
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
			auto next = (++action);

			//次の行動があるなら初期化
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
/// バトルが終了したかどうか
/// </summary>
/// <returns></returns>
bool BattleSystem::IsEnded()
{
	return false;
}


/// <summary>
/// 描画
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
