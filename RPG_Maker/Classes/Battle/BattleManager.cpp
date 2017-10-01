//************************************************/
//* @file  :BattleManager.cpp
//* @brief :戦闘シーンを管理するクラス
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#include "BattleManager.h"

void BattleManager::Update()
{
	//行動の選択
	if (!m_isSelected)
	{
		m_isSelected = m_system.SelectAction();
	}

	//行動を実行する
	if (m_isSelected)
	{
		m_isExecuted = m_system.ExecuteAction();
	}

	//ターンが終了したら最初に戻る
	if (m_isExecuted || m_system.Enemy() == nullptr)
	{
		m_isSelected = false;
		m_isExecuted = false;
		m_isEnded = m_system.IsEnded();
	}

	//バトルが終了したら結果を受け取る
	if (m_isEnded)
	{

	}
}

void BattleManager::Draw(const ShunLib::Vec2 & pos)
{
	m_system.Draw(pos);
}
