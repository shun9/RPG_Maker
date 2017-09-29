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

	return move(data);
}
