//************************************************/
//* @file  :GameLoader.h
//* @brief :ƒQ[ƒ€î•ñ‚ğ“Ç‚İ‚ŞƒNƒ‰ƒX
//* @date  :2017/09/29
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_Singleton.h>
#include <iostream>
#include <fstream>

class GameEditor;

class GameLoader :public ShunLib::Singleton<GameLoader>
{
	friend ShunLib::Singleton<GameLoader>;
private:
	GameEditor* m_editor;

public:
	bool LoadGame(GameEditor* editor);

private:
	GameLoader() {}
	~GameLoader() {}

	bool LoadTileData      (std::ifstream* file);
	bool LoadMapData       (std::ifstream* file);
	bool LoadPlayerData    (std::ifstream* file);
	bool LoadEnemyData     (std::ifstream* file);
	bool LoadEnemyGroupData(std::ifstream* file);
};