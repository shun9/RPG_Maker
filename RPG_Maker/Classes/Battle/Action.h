//************************************************/
//* @file  :Action.h
//* @brief :�퓬���̍s���̊��N���X
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
public:
	Action():m_isSetText(false){}
	virtual ~Action() {}
	virtual bool Execute(BattleSystem* obj) = 0;
	virtual void Start() = 0;
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