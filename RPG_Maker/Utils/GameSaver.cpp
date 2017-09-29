//************************************************/
//* @file  :GameSaver.cpp
//* @brief :ゲーム情報を保存するクラス
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include "GameSaver.h"
#include <iostream>
#include <fstream>
#include "../Classes/Editor/GameEditor.h"
#include "../Classes/Map/TileDataHolder.h"

using namespace std;

bool GameSaver::SaveGame(GameEditor* editor)
{
	//保存するデータ
	m_editor = editor;

	//ファイルをバイナリ書き込みモードでオープン
	ofstream file;
	file.open("RPG_Maker.rpgm", ios::out | ios::binary | ios::trunc);


	//先頭のタイトルを書き込む
	char tmp[] = "RPG_Maker";
	file.write(tmp, 10);

	//各データを保存
	if(!SaveTileData      (&file)){return false;}
	if(!SaveMapData       (&file)){return false;}
	if(!SavePlayerData    (&file)){return false;}
	if(!SaveEnemyData     (&file)){return false;}
	if(!SaveEnemyGroupData(&file)){return false;}

	return true;
}


/// <summary>
/// タイル情報の書き込み
/// </summary>
bool GameSaver::SaveTileData(ofstream* file)
{

	//先頭のタイトルを書き込む
	char tmp[] = "Tile";
	file->write(tmp, 5);


	//データ数を書き込み
	auto holder = TileDataHolder::GetInstance();
	int containerSize = holder->GetContainerSize();
	file->write((char*)&containerSize, sizeof(int));

	//データ取得用
	TileData* data;
	std::wstring texture;
	wchar_t* path;
	int size =0;

	//データ数だけループする
	for (int i = 0; i < containerSize; i++)
	{
		data = holder->GetData(i);

		//テクスチャのパス　終端文字があるので+1
		texture = data->texture->GetPath();
		size = (texture.length() + 1) * 2;
		path = const_cast<wchar_t*>(texture.c_str());
		file->write((char*)&size, sizeof(size));
		file->write((char*)path, size);

		//エンカウント率
		file->write((char*)&data->encountRate, sizeof(int));

		//敵構成の種類
		size = data->enemyGroup.size();
		file->write((char*)&size, sizeof(int));

		//敵構成ID
		for (int i = 0; i < size; i++)
		{
			file->write((char*)&data->enemyGroup[i], sizeof(int));
		}

		//歩けるかどうかのフラグ
		file->write((char*)&data->canMove, sizeof(bool));
	}

	return true;
}


/// <summary>
/// マップ情報の書き込み
/// </summary>
bool GameSaver::SaveMapData(ofstream * file)
{
	auto map = m_editor->GetMap()->GetMapData();
	int h = Map::HEIGHT;
	int w = Map::WIDTH;

	//マップサイズ
	file->write((char*)&h, sizeof(int));
	file->write((char*)&w, sizeof(int));

	int id = 0;
	//マップチップ情報
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			id = map[i][j].Id();

			file->write((char*)&id, sizeof(int));
		}
	}

	return true;
}


/// <summary>
/// プレイヤー情報の書き込み
/// </summary>
bool GameSaver::SavePlayerData(ofstream * file)
{
	return true;
}


/// <summary>
/// 敵情報の書き込み
/// </summary>
bool GameSaver::SaveEnemyData(ofstream * file)
{
	return true;
}


/// <summary>
/// 敵構成情報の書き込み
/// </summary>
bool GameSaver::SaveEnemyGroupData(ofstream * file)
{
	return true;
}
