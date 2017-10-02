//************************************************/
//* @file  :BattleManager.h
//* @brief :戦闘シーンを管理するクラス
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Singleton.h>
#include <SL_Vec2.h>
#include "BattleSystem.h"

class Player;
struct EnemyData;

class BattleManager:public ShunLib::Singleton<BattleManager>
{
	friend ShunLib::Singleton<BattleManager>;

private:

	//バトル進行用
	BattleSystem m_system;

	bool m_isSelected;
	bool m_isTurnEnd;

	//戦闘が終わったかどうか
	bool m_isEnded;

	bool m_result;

public:
	void SetPlayer(Player* p) { m_system.SetPlayer(p); }
	void SetEnemy(int id) {m_system.SetEnemy(id); }

	void BattleStart() {
		m_isSelected  = false; //選択肢終わったらtrue
		m_isEnded   = false;
		m_isTurnEnd = true;//最初の初期化のためtrue
		m_system.Start();
	}
	void Update();
	bool IsEnded() { return m_isEnded; }

	void Draw(const ShunLib::Vec2& pos);

	bool Result() { return m_result; }

private:
	BattleManager() {}
	~BattleManager() {}

};
