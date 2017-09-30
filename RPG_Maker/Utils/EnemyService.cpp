//************************************************/
//* @file  :EnemyService.cpp
//* @brief :�G�֘A�̃T�[�r�X�N���X
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
