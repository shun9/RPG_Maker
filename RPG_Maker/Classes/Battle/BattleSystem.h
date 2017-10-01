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

class Player;
struct EnemyData;

class BattleSystem
{
private:
	ShunLib::Texture* m_backGround;
	ShunLib::Texture* m_arrow;

	Player* m_player;
	EnemyGroupData* m_enemy;
	ActionList m_enemyAction;

	//プレイヤーの実行する行動一覧
	std::multimap<int, Action*>m_actionList;

	//プレイヤーが実行する行動の番号
	int m_actionNum;

	//実行中の行動
	int m_exeAction;

	//逃走に成功したかどうか
	bool m_succesedEscape;

	//キー入力
	ShunLib::CommandInput<ShunLib::KeyManager::KEY_CODE, BattleSystem>m_commandInput;

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

	//行動を積む
	void StackAction();

	//行動を実行する
	bool ExecuteAction();

	//バトルが終了したかどうか
	bool IsEnded();

	//描画
	void Draw(const ShunLib::Vec2& pos);

	//戦うキャラクターを設定
	void SetPlayer(Player* p) { m_player = p; }
	void SetEnemy(int id) { m_enemy = DB_EnemyGroup.GetData(id); }

	//戦うキャラクターを取得
	Player* Player() { return m_player; }
	EnemyGroupData* Enemy() { return m_enemy; }

private:
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

