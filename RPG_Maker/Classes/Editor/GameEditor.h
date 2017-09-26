//************************************************/
//* @file  :GameEditor.h
//* @brief :�G�f�B�^�[
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "../AppBase/AppBase.h"
#include "../../SL_Window.h"
#include "../UI/Editor/UIBase.h"
#include <memory>

class Game;

class GameEditor : public AppBase
{
private:
	Game* m_game;
	std::shared_ptr<UIBase> m_button;

public:
	GameEditor();
	~GameEditor();

	//��Ԃ̂��
	void Initialize()override;
	void Update    ()override;
	void Render    ()override;
	void Finalize  ()override;

private:
	void StartDebug();
};