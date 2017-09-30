//************************************************/
//* @file  :GameSaver.h
//* @brief :ゲーム情報を保存するクラス
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
	bool SaveGame(const std::string& fileName);

	// 現在開いているデータに保存
	bool SaveGameCurrentData(GameEditor* editor);
	// ファイルを選択して保存
	bool SaveGameFileSelect(GameEditor* editor);

private:
	GameSaver() {}
	~GameSaver() {}

	bool SaveTileData      (std::ofstream* file);
	bool SaveMapData       (std::ofstream* file);
	bool SavePlayerData    (std::ofstream* file);
	bool SaveEnemyData     (std::ofstream* file);
	bool SaveEnemyGroupData(std::ofstream* file);
};