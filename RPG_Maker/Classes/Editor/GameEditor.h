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
#include "../UI/Editor/UITileWindow.h"
#include "../UI/Editor/UIMenuBar.h"
#include "../UI/Editor/UITileProperty.h"
#include "../Map/Map.h"

#include <memory>

#include "../Player/Player.h"

class Game;

class GameEditor : public AppBase
{
private:
	Game* m_game;
	std::shared_ptr<UITileWindow> m_uiWindow;
	std::shared_ptr<UIMenuBar> m_uiMenu;
	std::shared_ptr<UITileProperty> m_uiTileProperty;
	ShunLib::Texture* m_tmp;
	ShunLib::Texture* m_tmp2;

	//	TODO:仮実装
	Player * player;

	Map* m_map;
public:
	GameEditor();
	~GameEditor();

	//定番のやつ
	void Initialize()override;
	void Update    ()override;
	void Render    ()override;
	void Finalize  ()override;

	void UIChangeActive(UIBase& ui);
	void TileWindowChangeActive() { UIChangeActive(*m_uiWindow.get()); }
	void TilePropertyChangeActive() { UIChangeActive(*m_uiTileProperty.get()); }

private:
	void StartDebug();
};