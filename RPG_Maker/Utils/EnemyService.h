//************************************************/
//* @file  :EnemyService.h
//* @brief :敵関連のサービスクラス
//* @date  :2017/09/26
//* @author:K,Yamamoto
//************************************************/
#pragma once
#include <memory>
#include <SL_Singleton.h>
#include <SL_Vec2.h>
#include <SL_Texture.h>
#include "../Classes/Data/DataBase.h"

namespace {
	using namespace ShunLib;
	using namespace std;
}

class EnemyService : public Singleton<EnemyService>
{
	friend ShunLib::Singleton<EnemyService>;

public:
	~EnemyService(){}

	// EnemyData作成
	std::unique_ptr<EnemyData> CreateEnemyData(const std::wstring& path = L"Image\\enemy\\Slime.png");
	// EnemyGroup作成
	std::unique_ptr<EnemyGroupData> CreateEnemyGroupData();
	// EnemyGroup作成
	std::unique_ptr<EnemyGroupAloneData> CreateEnemyGroupAloneData(int id = -1);
private:
	EnemyService(){}
};