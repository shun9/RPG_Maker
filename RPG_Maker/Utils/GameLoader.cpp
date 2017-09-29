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

	//ファイルが無ければ読み込まない
	if (!file)return false;

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
	std::wstring path;
	int size = 0;
	wchar_t tmpr[256];

	//データ数だけループする
	for (int i = 0; i < containerSize; i++)
	{
		//タイルデータを作成
		std::unique_ptr<TileData> tileData;
		tileData = std::make_unique<TileData>();

		//テクスチャのパス　終端文字があるので+1
		//path = data->texture->GetPath();
		file->read((char*)&size, sizeof(int));
		file->read((char*)tmpr, size);
		tileData->texture = std::make_unique<ShunLib::Texture>(tmpr);

		//エンカウント率
		file->read((char*)&tileData->encountRate, sizeof(int));

		//敵構成の種類
		file->read((char*)&size, sizeof(int));
		tileData->enemyGroup.resize(size);

		//敵構成ID
		for (int i = 0; i < (int)(tileData->enemyGroup.size()); i++)
		{
			file->read((char*)&tileData->enemyGroup[i], sizeof(int));
		}

		//歩けるかどうかのフラグ
		file->read((char*)&tileData->canMove, sizeof(bool));

		//データを追加
		holder->AddData(move(tileData));
	}

	return true;
}

/// <summary>
//マップの情報を読み込む
/// </summary>
bool GameLoader::LoadMapData(ifstream* file)
{
	auto map = m_editor->GetMap()->GetMapData();
	int h = 0;
	int w = 0;

	//マップサイズ
	file->read((char*)&h, sizeof(int));
	file->read((char*)&w, sizeof(int));

	//マップチップ情報
	int id = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			file->read((char*)&id, sizeof(int));
			(*map)[i][j].Id(id);
		}
	}

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
