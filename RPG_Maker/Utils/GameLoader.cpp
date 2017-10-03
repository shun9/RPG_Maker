//************************************************/
//* @file  :GameLoader.cpp
//* @brief :ゲーム情報を読み込むクラス
//* @date  :2017/09/29
//* @author:S.Katou
//************************************************/
#include "GameLoader.h"

#include <assert.h>
#include "../Classes/Editor/GameEditor.h"
#include "../Classes/Data/DataBase.h"
#include "../Classes/Player/PlayerHolder.h"

using namespace std;

//ゲームを読み込む
bool GameLoader::LoadGame(GameEditor* editor)
{
	//読み込んだデータを適用する用
	m_editor = editor;

	//ファイルをバイナリ読み込みモードでオープン

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
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	GetOpenFileName(&ofn);

	// 開いたpathをマルチバイト文字に変更
	wstring wfullpath = wstring(ofn.lpstrFileTitle);
	string fullpath;
	char *mbs = new char[wfullpath.length() *MB_CUR_MAX + 1];
	wcstombs(mbs, wfullpath.c_str(), wfullpath.length() * MB_CUR_MAX + 1);
	fullpath = mbs;
	delete[]mbs;

	// ファイル名を取得
	int path_i = fullpath.find_last_of("\\") + 1;
	int ext_i = fullpath.find_last_of(".");
	std::string fileName = fullpath.substr(path_i, ext_i - path_i);
	auto openName = fileName + string(".rpgm");	// 拡張子入り
	editor->FileName(fileName);					// 拡張子なしを保存

	// ファイルオープン
	ifstream file;
	file.open(ofn.lpstrFileTitle, ios::in | ios::binary);

	//ファイルが無ければ読み込まない
	if (!file)return false;

	//今あるデータをリセット
	DB->Reset();

	//先頭のタイトルを読み込む
	char tmp[10];
	file.read(tmp, 10);

	//各データを読み込む
	if(!LoadTileData      (&file)) { return false; }
	if(!LoadMapData       (&file)) { return false; }
	if(!LoadEnemyData     (&file)) { return false; }
	if(!LoadEnemyGroupData(&file)) { return false; }
	if (!LoadPlayerData(&file)) { return false; }

	return true;
}

/// <summary>
//マップタイルの情報を読み込む
/// </summary>
bool GameLoader::LoadTileData(ifstream * file)
{
	auto& holder = DB_Tile;

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
		holder.AddData(move(tileData));
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

/// <summary>
//敵の情報を読み込む
/// </summary>
bool GameLoader::LoadEnemyData(ifstream * file)
{
	//先頭のタイトルを読み込む
	char tmp[6];
	file->read(tmp, 6);

	auto& holder = DB_Enemy;
	int containerSize;
	file->read((char*)&containerSize, sizeof(int));

	std::wstring texture;
	wchar_t path[255];
	int size = 0;
	char nameBuf[255];

	bool isTexture = true;
	for (int i = 0; i < containerSize; i++)
	{
		//敵データを作成
		std::unique_ptr<EnemyData> data;
		data = std::make_unique<EnemyData>();

		//敵の名前
		file->read((char*)&size, sizeof(size));
		file->read((char*)nameBuf, size);
		data->Name = nameBuf;

		//テクスチャがあれば読み込み
		file->read((char*)&isTexture, sizeof(isTexture));
		if (isTexture)
		{
			//テクスチャのパス
			file->read((char*)&size, sizeof(size));
			file->read((char*)path, size);
			data->Texture = std::make_unique<ShunLib::Texture>(path);
		}

		//能力値
		data->Param.resize(EnemyData::Param::length);
		for (int j = 0; j < (int)data->Param.size(); j++)
		{
			file->read((char*)&data->Param[j], sizeof(int));
		}

		holder.AddData(move(data));
	}

	return true;
}


/// <summary>
/// 敵の構成を読み込む
/// </summary>
bool GameLoader::LoadEnemyGroupData(ifstream * file)
{
	auto& holder = DB_EnemyGroup;
	int containerSize;
	file->read((char*)&containerSize, sizeof(int));

	int groupSize = 0;
	int size = 0;
	char nameBuf[255];
	int id = 0;
	ShunLib::Vec2 pos;
	for (int i = 0; i < containerSize; i++)
	{
		//敵グループデータを作成
		std::unique_ptr<EnemyGroupData> data;
		data = std::make_unique<EnemyGroupData>();

		//名前
		file->read((char*)&size, sizeof(size));
		file->read(nameBuf, size);
		data->Name = nameBuf;

		//構成
		file->read((char*)&groupSize, sizeof(int));

		for (int j = 0; j < groupSize; j++)
		{
			file->read((char*)&id, sizeof(int));
			file->read((char*)&pos, sizeof(ShunLib::Vec2));
			data->enemyList.GetList().at(j)->Id = id;
			data->enemyList.GetList().at(j)->Pos = pos;
		}

		holder.AddData(move(data));
	}

	return true;
}


/// /// <summary>
//プレイヤーの情報を読み込む
/// </summary>
bool GameLoader::LoadPlayerData(ifstream * file)
{
	auto player = PlayerHolder::GetInstance()->Get();

	//位置
	ShunLib::Vec2 pos;
	file->read((char*)&(pos.m_x), sizeof(float));
	file->read((char*)&(pos.m_y), sizeof(float));
	player->PosOnMap(pos);

	for (int i = 0; i < Player::PARAM::length; i++)
	{
		file->read((char*)&(player->GetParam()[i]), sizeof(int));
	}

	return true;
}
