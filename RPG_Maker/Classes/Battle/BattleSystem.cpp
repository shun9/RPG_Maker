//************************************************/
//* @file  :BattleSystem.cpp
//* @brief :戦闘の処理をするクラス
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

BattleSystem::BattleSystem():
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

	auto& db = DB_Enemy;
	int id = db.AddData(EnemyService::GetInstance()->CreateEnemyData(L"Image\\cute-slime-Pixel.png"));

	tmp = std::make_unique<EnemyGroupData>();

	tmp->enemyList.push_back(std::make_pair(ShunLib::Vec2(150.0f, 300.0f), db.GetData(id)));
	tmp->enemyList.push_back(std::make_pair(ShunLib::Vec2(350.0f, 300.0f), db.GetData(id)));
	tmp->enemyList.push_back(std::make_pair(ShunLib::Vec2(550.0f, 300.0f), db.GetData(id)));

	id = DB_EnemyGroup.AddData(move(tmp));
	m_enemy = *DB_EnemyGroup.GetData(id);

	m_enemyAction.List().push_back(new EnemyAttackAction);

	auto& db2 = DB_Enemy;
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
	m_targetNum = 0;
	m_isExecuteAction = false;
	m_succesedEscape = false;
	m_isSelectTarget = false;
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
	if (!m_isSelectTarget)
	{
		isDecided = SelectCommand();
	}

	if (m_isSelectTarget)
	{
		isDecided = SelectTarget();
	}

	return isDecided;
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
/// ターゲットを変更
/// </summary>
/// <param name="num">移動する値</param>
void BattleSystem::ShiftTarget(int num)
{
	m_targetNum += num;
	int listSize = (int)(m_enemy.enemyList.size()) - 1;

	if (m_targetNum < 0) {
		m_targetNum = listSize;
	}
	else if (m_targetNum > listSize) {
		m_targetNum = 0;
	}
}


/// <summary>
/// 行動を積む
/// </summary>
void BattleSystem::StackAction()
{
	m_actionList.clear();
	m_charactorList.clear();

	auto list = m_player->GetActionList().List();
	int spd = m_player->GetParam()[Player::PARAM::SPD];
	m_actionList.insert(std::make_pair(spd, list[m_actionNum]));
	m_charactorList.insert(std::make_pair(spd, m_player));
	m_isSelectTarget = list[m_actionNum]->ShouldSelectTarget();

	for (int i = 0; i < (int)(m_enemy.enemyList.size()); i++)
	{
		ShunLib::RandomNumber rn;
		int num = rn(0, m_enemyAction.List().size() - 1);
		m_actionList.insert(std::make_pair(0, m_enemyAction.List()[num]));
		m_charactorList.insert(std::make_pair(0,m_enemy.enemyList[i].second));
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
	auto charactor = m_charactorList.rbegin();

	//現在実行中の行動まで進める
	for (int i = 0; i < m_exeAction; i++)
	{
		action++;
		charactor++;
	}

	//行動の実行
	bool isEnded = true;
	if (action != m_actionList.rend())
	{
		isEnded = action->second->Execute(this, (charactor)->second);

		//行動が終わったら次の行動に移る
		if (isEnded)
		{
			//プレイヤーが死んでいたら終了
			if (m_player->IsDead())
			{
				return true;
			}

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
	if (m_succesedEscape)
	{
		return true;
	}

	if (m_player->IsDead())
	{
		return true;
	}
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
		if (!m_isSelectTarget)
		{
			m_arrow->Draw(m_arrowPos*m_actionNum + ShunLib::Vec2(pos.m_x, 405.0f), ShunLib::Vec2(2.0f, 2.0f));
		}
		else
		{
			auto tarPos = m_enemy.enemyList[m_targetNum].first;
			m_arrow->Draw(tarPos + ShunLib::Vec2(0.0f, 50.0f), ShunLib::Vec2(2.0f, 2.0f));
		}
	}

	ShunLib::Vec2 enemyPos;
	auto& ds = DB_Enemy;

	for (int i = 0; i < (int)(m_enemy.enemyList.size()); i++)
	{
		if (m_enemy.enemyList[i].second->Param[EnemyData::HP] > 0)
		{
			enemyPos = m_enemy.enemyList[i].first;
			m_enemy.enemyList[i].second->Texture->Draw(enemyPos, ShunLib::Vec2::One);
		}
	}
}

/// <summary>
/// コマンドの選択
/// </summary>
bool BattleSystem::SelectCommand()
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

			if (m_isSelectTarget)isDecided = false;
			break;
		}
	}
	return isDecided;
}

/// <summary>
/// ターゲット選択
/// </summary>
bool BattleSystem::SelectTarget()
{
	auto key = ShunLib::KeyManager::GetInstance();

	//決定したかどうか
	bool isDecided = false;
	m_isExecuteAction = false;
	auto keyList = m_targetSelectInput.GetKeyList();

	for (int i = 0; i < (int)keyList.size(); i++)
	{
		//キーが押されていたら実行
		if (key->IsTracker(keyList[i]))
		{
			isDecided = m_targetSelectInput.HandleInput(keyList[i])->Execute(this);
		}

		//決定したらターゲットを設定
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

//ターゲットを1つ上に移動する
bool SelectUpTarget::Execute(BattleSystem * obj)
{
	obj->ShiftTarget(+1);
	return false;
}

//ターゲットを1つ下に移動する
bool SelectDownTarget::Execute(BattleSystem * obj)
{
	obj->ShiftTarget(-1);
	return false;
}

//ターゲットを決定
bool SelectDecideTarget::Execute(BattleSystem * obj)
{
	return true;
}
