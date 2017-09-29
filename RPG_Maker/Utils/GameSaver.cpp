//************************************************/
//* @file  :GameSaver.cpp
//* @brief :ゲーム情報を保存するクラス
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include "GameSaver.h"
#include "../Classes/Map/TileDataHolder.h"

bool GameSaver::SaveGame(GameEditor* editor)
{
	//ファイルをバイナリ書き込みモードでオープン
	FILE* file;
	fopen_s(&file," ", "rb");

	if(!SaveTileData      (file)){fclose(file);return false;}
	if(!SaveMapData       (file)){fclose(file);return false;}
	if(!SavePlayerData    (file)){fclose(file);return false;}
	if(!SaveEnemyData     (file)){fclose(file);return false;}
	if(!SaveEnemyGroupData(file)){fclose(file);return false;}

	//ファイルを閉じる
	fclose(file);
	return true;
}


/// <summary>
/// タイル情報の書き込み
/// </summary>
bool GameSaver::SaveTileData(FILE * file)
{
	auto holder = TileDataHolder::GetInstance();

	//データ数を書き込み
	int size = holder->GetContainerSize();
	fwrite(&size, sizeof(int), 1, file);

	//データ取得用
	TileData* data;

	//データ数だけループする
	for (int i = 0; i < size; i++)
	{
		data = holder->GetData(i);

	}

	return true;
}


/// <summary>
/// タイル情報の書き込み
/// </summary>
bool GameSaver::SaveMapData(FILE * file)
{
	return true;
}


/// <summary>
/// タイル情報の書き込み
/// </summary>
bool GameSaver::SavePlayerData(FILE * file)
{
	return true;
}


/// <summary>
/// タイル情報の書き込み
/// </summary>
bool GameSaver::SaveEnemyData(FILE * file)
{
	return true;
}


/// <summary>
/// 敵構成情報の書き込み
/// </summary>
bool GameSaver::SaveEnemyGroupData(FILE * file)
{
	return true;
}
