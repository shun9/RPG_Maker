//************************************************/
//* @file  :GameSaver.h
//* @brief :ƒQ[ƒ€î•ñ‚ğ•Û‘¶‚·‚éƒNƒ‰ƒX
//* @date  :2017/09/29
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_Singleton.h>
#include <iostream>
#include <fstream>

class GameEditor;
class GameSaver :public ShunLib::Singleton<GameSaver>
{
	friend ShunLib::Singleton<GameSaver>;
private:
	GameEditor* m_editor;

public:
	bool SaveGame(GameEditor* editor);

private:
	GameSaver() {}
	~GameSaver() {}

	bool SaveTileData      (std::ofstream* file);
	bool SaveMapData       (std::ofstream* file);
	bool SavePlayerData    (std::ofstream* file);
	bool SaveEnemyData     (std::ofstream* file);
	bool SaveEnemyGroupData(std::ofstream* file);
};