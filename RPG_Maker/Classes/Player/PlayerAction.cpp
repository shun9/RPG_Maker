//************************************************/
//* @file  :PlayerAction.cpp
//* @brief :プレイヤーの行動一覧
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#include "PlayerAction.h"
#include "../Battle/BattleSystem.h"
#include "../Battle/BattleText.h"
#include "../Battle/BattleTextPreset.h"

/// <summary>
/// 攻撃
/// </summary>
bool PlayerAttackAction::Execute(BattleSystem * obj)
{
	auto text = BattleText::GetInstance();
	bool isEnded = false;

	//攻撃
	if (!m_isSetText)
	{
		text->Reset();
		m_isSetText = true;
		std::string str = u8"プレイヤー";
		text->SetString(ATTACK_TEXT(str));
	}
	else
	{
		isEnded = text->IsEnded();
	}

	return isEnded;
}


/// <summary>
/// 防御
/// </summary>
bool PlayerDefenseAction::Execute(BattleSystem * obj)
{
	auto text = BattleText::GetInstance();
	bool isEnded = false;

	//防御
	if (!m_isSetText)
	{
		text->Reset();
		m_isSetText = true;
		std::string str = u8"プレイヤー";
		text->SetString(DEFENCE_TEXT(str));
	}
	else
	{
		isEnded = text->IsEnded();
	}
	return isEnded;
}


/// <summary>
/// 逃げる
/// </summary>
bool PlayerEscapeAction::Execute(BattleSystem * obj)
{
	auto text = BattleText::GetInstance();
	bool isEnded = false;

	//逃げる
	if (!m_isSetText)
	{
		text->Reset();
		m_isSetText = true;
		std::string str = u8"プレイヤー";
		text->SetString(ESCAPE_TEXT(str));
	}
	else
	{
		isEnded = text->IsEnded();
	}
	return isEnded;
}

