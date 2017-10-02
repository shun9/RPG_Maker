//************************************************/
//* @file  :BattleManager.h
//* @brief :�퓬�V�[�����Ǘ�����N���X
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

	//�o�g���i�s�p
	BattleSystem m_system;

	bool m_isSelected;
	bool m_isTurnEnd;

	//�퓬���I��������ǂ���
	bool m_isEnded;

	bool m_result;

public:
	void SetPlayer(Player* p) { m_system.SetPlayer(p); }
	void SetEnemy(int id) {m_system.SetEnemy(id); }

	void BattleStart() {
		m_isSelected  = false; //�I�����I�������true
		m_isEnded   = false;
		m_isTurnEnd = true;//�ŏ��̏������̂���true
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
