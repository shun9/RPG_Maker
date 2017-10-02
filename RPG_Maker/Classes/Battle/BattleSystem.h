//************************************************/
//* @file  :BattleSystem.h
//* @brief :戦闘の処理をするクラス
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

	//プレイヤーの実行する行動一覧
	std::multimap<int, Action*>m_actionList;
	std::multimap<int, void*>m_charactorList;

	std::vector<int>m_enemyHp;

	//プレイヤーが実行する行動の番号
	int m_actionNum;
	int m_targetNum;

	//実行中の行動
	int m_exeAction;

	//ターゲットを選択中かどうか
	bool m_isSelectTarget;

	//行動を実行中かどうか
	bool m_isExecuteAction;

	//逃走に成功したかどうか
	bool m_succesedEscape;

	//キー入力
	ShunLib::CommandInput<ShunLib::KeyManager::KEY_CODE, BattleSystem>m_commandInput;
	ShunLib::CommandInput<ShunLib::KeyManager::KEY_CODE, BattleSystem>m_targetSelectInput;

	//プレイヤーが勝ったかどうか
	bool m_isWinPlayer;


public:
	BattleSystem();
	~BattleSystem();

	void Start();

	//行動の選択
	bool SelectAction();

	//選択肢を移動する
	void ShiftOption(int num);
	void ShiftTarget(int num);

	//行動を積む
	void StackAction();

	//行動を実行する
	bool ExecuteAction();

	//バトルが終了したかどうか
	bool IsEnded();

	//描画
	void Draw(const ShunLib::Vec2& pos);

	//戦うキャラクターを設定
	void SetPlayer(Player* p) {m_player = p;}
	void SetEnemy(int id) {
		auto& db = DB_Enemy;
		m_enemy = DB_EnemyGroup.GetData(id);
		//HPを保存
		for (int i = 0; i < (int)m_enemy->enemyList.size(); i++)
		{
			m_enemyHp.push_back(db.GetData(m_enemy->enemyList[i].first)->Param[EnemyData::Param::HP]);
		}
	}

	//戦うキャラクターを取得
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


//選択肢を1つ上に移動する
class SelectUpCommand :public ShunLib::Command<BattleSystem>
{
public:
	SelectUpCommand() {}
	~SelectUpCommand() {}
	bool Execute(BattleSystem* obj)override;
};


//選択肢を1つ下に移動する
class SelectDownCommand :public ShunLib::Command<BattleSystem>
{
public:
	SelectDownCommand() {}
	~SelectDownCommand() {}
	bool Execute(BattleSystem* obj)override;
};


//選択肢を決定する
class SelectDecideCommand :public ShunLib::Command<BattleSystem>
{
public:
	SelectDecideCommand() {}
	~SelectDecideCommand() {}
	bool Execute(BattleSystem* obj)override;
};

//選択肢を1つ上に移動する
class SelectUpTarget :public ShunLib::Command<BattleSystem>
{
public:
	SelectUpTarget() {}
	~SelectUpTarget() {}
	bool Execute(BattleSystem* obj)override;
};


//選択肢を1つ下に移動する
class SelectDownTarget :public ShunLib::Command<BattleSystem>
{
public:
	SelectDownTarget() {}
	~SelectDownTarget() {}
	bool Execute(BattleSystem* obj)override;
};


//選択肢を決定する
class SelectDecideTarget :public ShunLib::Command<BattleSystem>
{
public:
	SelectDecideTarget() {}
	~SelectDecideTarget() {}
	bool Execute(BattleSystem* obj)override;
};

