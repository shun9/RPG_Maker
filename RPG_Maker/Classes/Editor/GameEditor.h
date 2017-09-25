//************************************************/
//* @file  :GameEditor.h
//* @brief :エディター
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "../AppBase/AppBase.h"

class GameEditor : public AppBase
{
public:
	GameEditor();
	~GameEditor();

	//定番のやつ
	void Initialize()override;
	void Update    ()override;
	void Render    ()override;
	void Finalize  ()override;
private:

};