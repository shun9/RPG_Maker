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
#include "../UI/Editor/UIMenuBar.h"
#include "../UI/Editor/UITileProperty.h"
#include "../UI/Editor/UITileCanvas.h"
#include "../UI/Editor/EnemyData/UIEnemyTable.h"
#include "../Map/Map.h"

#include <memory>

#include "../Player/Player.h"

class Game;

class GameEditor : public AppBase
{
private:
	Game* m_game;

	// UI
	std::unique_ptr<UIMenuBar> m_uiMenu;
	std::unique_ptr<UITileProperty> m_uiTileProperty;
	std::unique_ptr<UITileCanvas> m_uiTileCanvas;
	std::unique_ptr<UIEnemyTable> m_uiEnemyTable;

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

	// TODO:のちほど専用クラスに移動UI
	void UIChangeActive(UIBase& ui);
	void TilePropertyChangeActive() { UIChangeActive(*m_uiTileProperty.get()); }
	void EnemyTableChangeActive() { UIChangeActive(*m_uiEnemyTable.get()); }
	void SelectedCreateTileData();

	Map* GetMap() { return m_map; }

private:
	void StartDebug();

	//プレイヤーをスクロールと同期させる
	void PlayerScroll();
};