//************************************************/
//* @file  :GameEditor.h
//* @brief :エディター
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Texture.h>
#include "../AppBase/AppBase.h"
#include "../../SL_Window.h"
#include "../UI/Editor/UIBase.h"
#include "../Map/Map.h"

#include <memory>

class Game;

class GameEditor : public AppBase
{
private:
	Game* m_game;
	std::shared_ptr<UIBase> m_button;

	ShunLib::Texture* m_tmp;

	Map* m_map;
public:
	GameEditor();
	~GameEditor();

	//定番のやつ
	void Initialize()override;
	void Update    ()override;
	void Render    ()override;
	void Finalize  ()override;

private:
	void StartDebug();
};