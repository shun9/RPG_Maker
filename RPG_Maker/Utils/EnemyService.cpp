//************************************************/
//* @file  :EnemyService.cpp
//* @brief :敵関連のサービスクラス
//* @date  :2017/09/26
//* @author:K,Yamamoto
//************************************************/
#include "EnemyService.h"

using namespace ShunLib;
using namespace std;

std::unique_ptr<EnemyData> EnemyService::CreateEnemyData(const wstring & path)
{
	auto data = make_unique<EnemyData>();

	// パラメータ用サイズ確保
	data->Param.resize(EnemyData::Param::length);

	{
		// 初期値
		data->Param[EnemyData::Param::HP] = 10;
		data->Param[EnemyData::Param::MP] = 10;
		data->Param[EnemyData::Param::ATK] = 1;
		data->Param[EnemyData::Param::DEF] = 1;
		data->Param[EnemyData::Param::DEX] = 100;
		data->Param[EnemyData::Param::EVA] = 0;
		data->Param[EnemyData::Param::EXP] = 10;
		data->Param[EnemyData::Param::MONEY] = 10;
	}

	data->Name = string(u8"スライム");

	if (path != L"") data->Texture = make_unique<Texture>(path.c_str());
	else data->Texture = nullptr;

	return move(data);
}

std::unique_ptr<EnemyGroupData> EnemyService::CreateEnemyGroupData()
{
	auto data = make_unique<EnemyGroupData>();

	data->Name = string(u8"未設定グループ");

	data->enemyList.GetList().resize(0);

	return move(data);
}

std::unique_ptr<EnemyGroupAloneData> EnemyService::CreateEnemyGroupAloneData(int id)
{
	auto data = make_unique<EnemyGroupAloneData>();

	data->Pos = Vec2(0.0f, 0.0f);
	data->Id = id;
	auto enemy = DB_Enemy.GetData(data->Id);
	if (enemy)data->Name = enemy->Name;
	else data->Name = "";
	return move(data);
}
