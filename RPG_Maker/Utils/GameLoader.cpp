//************************************************/
//* @file  :GameLoader.cpp
//* @brief :ゲーム情報を読み込むクラス
//* @date  :2017/09/29
//* @author:S.Katou
//************************************************/
#include "GameLoader.h"

#include <assert.h>
#include "../Classes/Editor/GameEditor.h"
#include "../Classes/Map/TileDataHolder.h"

using namespace std;

//ゲームを読み込む
bool GameLoader::LoadGame(GameEditor* editor)
{
	//読み込んだデータを適用する用
	m_editor = editor;

	//ファイルをバイナリ読み込みモードでオープン
	ifstream file;
	file.open("RPG_Maker.rpgm", ios::in | ios::binary);

	assert(file);

	//先頭のタイトルを読み込む
	char tmp[10];
	file.read(tmp, 10);

	//各データを読み込む
	if(!LoadTileData      (&file)) { return false; }
	if(!LoadMapData       (&file)) { return false; }
	if(!LoadPlayerData    (&file)) { return false; }
	if(!LoadEnemyData     (&file)) { return false; }
	if(!LoadEnemyGroupData(&file)) { return false; }

	return true;
}

/// <summary>
//マップタイルの情報を読み込む
/// </summary>
bool GameLoader::LoadTileData(ifstream * file)
{
	auto holder = TileDataHolder::GetInstance();

	//先頭のタイトルを書き込む
	char tmp[5];
	file->read(tmp, 5);

	//データ数を読み込み
	int containerSize = 0;
	file->read((char*)&containerSize, sizeof(int));

	//データ保存用
	TileData data;
	std::wstring path;
	int size = 0;
	wchar_t tmpr[256];

	//データ数だけループする
	for (int i = 0; i < containerSize; i++)
	{
		//テクスチャのパス　終端文字があるので+1
		//path = data->texture->GetPath();
		file->read((char*)&size, sizeof(int));
		file->read((char*)tmpr, size);

		//エンカウント率
		file->read((char*)&data.encountRate, sizeof(int));

		holder->AddData(&data);
	}

	return true;
}

/// <summary>
//マップの情報を読み込む
/// </summary>
bool GameLoader::LoadMapData(ifstream * file)
{
	return true;
}


/// /// <summary>
//プレイヤーの情報を読み込む
/// </summary>
bool GameLoader::LoadPlayerData(ifstream * file)
{
	return true;
}


/// <summary>
//敵の情報を読み込む
/// </summary>
bool GameLoader::LoadEnemyData(ifstream * file)
{
	return true;
}


/// <summary>
/// 敵の構成を読み込む
/// </summary>
bool GameLoader::LoadEnemyGroupData(ifstream * file)
{
	return true;
}
