//************************************************/
//* @file  :Action.h
//* @brief :í“¬’†‚Ìs“®‚ÌŠî’êƒNƒ‰ƒX
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_MacroConstants.h>

class BattleSystem;
class Action
{
public:
	Action() {}
	virtual ~Action() {}
	virtual bool Execute(BattleSystem* obj) = 0;
};

class ActionList
{
private:
	std::vector<Action*>m_actionList;

public:
	~ActionList() {
		for (int i = 0; i < (int)m_actionList.size(); i++)
		{
			DELETE_POINTER(m_actionList[i]);
		}
	}

	std::vector<Action*>& List() { return m_actionList; }
};