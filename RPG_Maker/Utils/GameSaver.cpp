//************************************************/
//* @file  :GameSaver.cpp
//* @brief :ゲーム情報を保存するクラス
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include "GameSaver.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../Classes/Editor/GameEditor.h"
#include "../Classes/Data/DataBase.h"
#include "../SL_Window.h"
#include "../Classes/Player/PlayerHolder.h"

using namespace std;
using namespace ShunLib;

bool GameSaver::SaveGame(const string & fileName)
{
	if (fileName == "")return false;

	//ファイルをバイナリ書き込みモードでオープン
	ofstream file;
	auto openName = fileName + string(".rpgm");
	file.open(openName.c_str(), ios::out | ios::binary | ios::trunc);

	const auto tmp = fileName.c_str();

	file.write(tmp, 10);

	//各データを保存
	if (!SaveTileData(&file)) { return false; }
	if (!SaveMapData(&file)) { return false; }
	if (!SaveEnemyData(&file)) { return false; }
	if (!SaveEnemyGroupData(&file)) { return false; }
	if (!SavePlayerData(&file)) { return false; }

	return true;
}

bool GameSaver::SaveGameCurrentData(GameEditor * editor)
{
	m_editor = editor;
	auto fileName = editor->FileName();

	return SaveGame(fileName);
}

bool GameSaver::SaveGameFileSelect(GameEditor * editor)
{
	//保存するデータ
	m_editor = editor;
	OPENFILENAME ofn;
	char szFile[MAX_PATH] = "";
	char szFileTitle[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter =
		TEXT("RPGM(*.rpgm)\0*.rpgm\0");
	ofn.lpstrFileTitle = (LPWSTR)szFileTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrFile = (LPWSTR)szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST
		| OFN_OVERWRITEPROMPT;

	if(GetSaveFileName(&ofn))
	MessageBox(Window::GetInstance()->WindouHandle(Window::EDITOR),(LPWSTR) szFile, TEXT("Save as"), MB_OK);

	// 開いたファイル名をマルチバイト文字に変更
	wstring wfullpath = wstring(ofn.lpstrFile);
	string fullpath;
	char *mbs = new char[wfullpath.length() *MB_CUR_MAX + 1];
	wcstombs(mbs, wfullpath.c_str(), wfullpath.length() * MB_CUR_MAX + 1);
	fullpath = mbs;
	delete[]mbs;

	int path_i = fullpath.find_last_of("\\") + 1;
	int ext_i = fullpath.find_last_of(".");

	// ファイル名を取得
	std::string fileName = fullpath.substr(path_i, ext_i - path_i);

	editor->FileName(fileName);

	return SaveGame(fileName);
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
	const auto& holder = DB_Tile;
	int containerSize = holder.GetContainerSize();
	file->write((char*)&containerSize, sizeof(int));

	//データ取得用
	std::wstring texture;
	wchar_t* path;
	int size =0;
	TileData* data;

	//データ数だけループする
	for (int i = 0; i < containerSize; i++)
	{
		data = holder.GetData(i);

		//テクスチャのパス　終端文字があるので+1
		texture = data->texture->GetPath();
		size = (texture.length() + 1) * 2;
		path = const_cast<wchar_t*>(texture.c_str());
		file->write((char*)&size, sizeof(size));
		file->write((char*)path, size);

		//エンカウント率
		file->write((char*)&data->encountRate, sizeof(int));

		//敵構成の種類
		size = (int)(data->enemyGroup.size());
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
			id = (*map)[i][j].Id();

			file->write((char*)&id, sizeof(int));
		}
	}

	return true;
}


/// <summary>
/// 敵情報の書き込み
/// </summary>
bool GameSaver::SaveEnemyData(ofstream * file)
{
	//先頭のタイトルを書き込む
	char tmp[] = "Enemy";
	file->write(tmp, 6);

	const auto& holder = DB_Enemy;
	auto containerSize = holder.GetContainerSize();
	file->write((char*)&containerSize, sizeof(int));

	EnemyData* data;
	std::wstring texture;
	wchar_t* path;
	int size = 0;
	bool isTexture = true;
	std::string buf;
	for (int i = 0; i < containerSize; i++)
	{
		data = holder.GetData(i);

		//敵の名前
		size = (data->Name.length() + 1) * 2;
		buf = data->Name;
		buf += '\0';
		file->write((char*)&size, sizeof(size));
		file->write(buf.c_str(), size);

		//テクスチャがあれば書き込み
		if (data->Texture && data->Texture->GetPath() != L"")
		{
			isTexture = true;
			file->write((char*)&isTexture, sizeof(isTexture));

			//テクスチャのパス　終端文字があるので+1
			texture = data->Texture->GetPath();
			size = (texture.length() + 1) * 2;
			path = const_cast<wchar_t*>(texture.c_str());
			file->write((char*)&size, sizeof(size));
			file->write((char*)path, size);
		}
		else {
			isTexture = false;
			file->write((char*)&isTexture, sizeof(isTexture));
		}

		//能力値
		for (int j = 0; j < (int)data->Param.size(); j++)
		{
			file->write((char*)&data->Param[j], sizeof(int));
		}
	}
	return true;
}


/// <summary>
/// 敵構成情報の書き込み
/// </summary>
bool GameSaver::SaveEnemyGroupData(ofstream * file)
{
	auto& holder = DB_EnemyGroup;
	int containerSize = holder.GetContainerSize();
	file->write((char*)&containerSize, sizeof(int));

	int groupSize = 0;
	int size = 0;
	EnemyGroupData* group;
	std::string buf;
	for (int i = 0; i < containerSize; i++)
	{
		group = holder.GetData(i);

		//敵の名前
		size = (group->Name.length() + 1) * 2;
		buf = group->Name;
		buf += '\0';
		file->write((char*)&size, sizeof(size));
		file->write(buf.c_str(), size);

		//構成
		groupSize = (int)group->enemyList.size();
		file->write((char*)&groupSize, sizeof(int));

		for (int j = 0; j < groupSize; j++)
		{
			file->write((char*)&group->enemyList[j].first, sizeof(int));
			file->write((char*)&group->enemyList[j].second, sizeof(ShunLib::Vec2));
		}
	}
	return true;
}

/// <summary>
/// プレイヤー情報の書き込み
/// </summary>
bool GameSaver::SavePlayerData(ofstream * file)
{
	auto player = PlayerHolder::GetInstance()->Get();

	//位置
	auto pos = player->PosOnMap();
	file->write((char*)&(pos.m_x), sizeof(float));
	file->write((char*)&(pos.m_y), sizeof(float));

	for (int i = 0; i < Player::PARAM::length; i++)
	{
		file->write((char*)&(player->GetParam()[i]), sizeof(int));
	}
	return true;
}