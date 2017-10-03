//************************************************/
//* @file  :EnemyService.h
//* @brief :�G�֘A�̃T�[�r�X�N���X
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

	// EnemyData�쐬
	std::unique_ptr<EnemyData> CreateEnemyData(const wstring& path = L"");
	// EnemyGroup�쐬
	std::unique_ptr<EnemyGroupData> CreateEnemyGroupData();
	// EnemyGroup�쐬
	std::unique_ptr<EnemyGroupAloneData> CreateEnemyGroupAloneData();
private:
	EnemyService(){}
};