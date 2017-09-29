//************************************************/
//* @file  :GameSaver.h
//* @brief :ƒQ[ƒ€î•ñ‚ğ•Û‘¶‚·‚éƒNƒ‰ƒX
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_Singleton.h>
#include "../Classes/Editor/GameEditor.h"

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

	bool SaveTileData      (FILE* file);
	bool SaveMapData       (FILE* file);
	bool SavePlayerData    (FILE* file);
	bool SaveEnemyData     (FILE* file);
	bool SaveEnemyGroupData(FILE* file);
};