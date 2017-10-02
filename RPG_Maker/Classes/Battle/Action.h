//************************************************/
//* @file  :Action.h
//* @brief :í“¬’†‚Ìs“®‚ÌŠî’êƒNƒ‰ƒX
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <string>
#include <SL_MacroConstants.h>

class BattleSystem;

class Action
{
protected:
	bool m_isSetText;
	bool m_shouldSelectTarget;
	int m_target;

public:
	Action():m_isSetText(false), m_shouldSelectTarget(false){}
	virtual ~Action() {}
	virtual bool Execute(BattleSystem* obj,void* own) = 0;
	virtual void Start() = 0;

	bool ShouldSelectTarget() { return m_shouldSelectTarget; }
	void Target(int tar) { m_target = tar; }
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