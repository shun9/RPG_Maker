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
#include "../Classes/Enemy/EmeyGroupDataHolder.h"
#include "../Classes/Enemy/EnemyDataHolder.h"

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
	std::unique_ptr<EnemyData> CreateEnemyData(const wstring& path);

	// EnemyGroup作成
	std::unique_ptr<EnemyGroupData> CreateEnemyGroupData(const wstring& path);

private:
	EnemyService(){}
};