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
#include "../Map/Map.h"
#include "../UI/Editor/UIMenuBar.h"
#include "../UI/Editor/UITileProperty.h"
#include "../UI/Editor/UITileCanvas.h"
#include "../UI/Editor/UIUnderBar.h"
#include "../UI/Editor/UIDataBase.h"
#include "../UI/Editor/UIPlayer.h"
#include "../../Utils/GameLoader.h"
#include "../../Utils/GameSaver.h"
#include "ShortCutKey.h"

#include <memory>

#include "../Player/Player.h"

class Game;

class GameEditor : public AppBase
{
private:
	// 現在開いているファイル名
	std::string m_fileName;

	Game* m_game;

	// UI
	std::unique_ptr<UIMenuBar> m_uiMenu;
	std::unique_ptr<UITileProperty> m_uiTileProperty;
	std::unique_ptr<UITileCanvas> m_uiTileCanvas;
	std::unique_ptr<UIUnderBar> m_uiUnderBar;
	std::unique_ptr<UIDataBase> m_uiDataBase;

	//	TODO:仮実装
	Player * player;

	Map* m_map;

	ShortCutKey m_shortCutKey;

public:
	GameEditor();
	~GameEditor();

	//定番のやつ
	void Initialize()override;
	void Update    ()override;
	void Render    ()override;
	void Finalize  ()override;

	void DataInitialize(const ShunLib::Window& win);

	// ファイル名の設定
	std::string FileName() { return m_fileName; }
	void FileName(std::string fileName) { m_fileName = fileName; }

	// TODO:のちほど専用クラスに移動UI
	void UIChangeActive(UIBase& ui);
	void TilePropertyChangeActive() { UIChangeActive(*m_uiTileProperty.get()); }
	void SelectedCreateTileData();
	// データのロード
	void LoadData() { GameLoader::GetInstance()->LoadGame(this); }
	// データのセーブ
	void SaveDataAs() { GameSaver::GetInstance()->SaveGameFileSelect(this); }
	// データの上書きセーブ
	void SaveDataOverwrite() {
		if (m_fileName != "") GameSaver::GetInstance()->SaveGameCurrentData(this);;
	}

	Map* GetMap() { return m_map; }

private:
	void StartDebug();

	//プレイヤーをスクロールと同期させる
	void PlayerScroll();
};