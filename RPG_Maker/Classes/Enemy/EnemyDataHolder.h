//************************************************/
//* @file  :EnemyDataHolder.h
//* @brief :タイルの情報を保持する
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <string>
#include <SL_Singleton.h>
#include <SL_Texture.h>
#include <SL_ConstantNumber.h>

class Enemy;

// 敵の情報
struct EnemyData {

	enum Param {
		HP,
		MP,
		ATK,
		DEF,
		DEX,
		EVA,
		EXP,
		MONEY,
		length
	};

	int Id;

	std::string Name;

	// 敵画像
	std::unique_ptr<ShunLib::Texture> Texture;

	std::vector<int> Param;
};


// TODO:テンプレートクラスにできそう
// 敵の情報を保持する
class EnemyDataHolder :public ShunLib::Singleton<EnemyDataHolder>
{
	friend ShunLib::Singleton<EnemyDataHolder>;

private:
	//敵種類一覧
	std::vector<std::unique_ptr<EnemyData>> m_enemyData;

public:
	EnemyDataHolder() {}
	~EnemyDataHolder() {}

	//データを追加する
	int AddData(std::unique_ptr<EnemyData> data) {
		m_enemyData.push_back(move(data));
		return (int)(m_enemyData.size()) - 1;
	}

	//データ情報を返す
	//無ければnullptr
	EnemyData* GetData(int id) {
		if (id > (int)(m_enemyData.size()) - 1)return nullptr;
		return	m_enemyData[id].get();
	}

	// 全データ取得
	const std::vector<std::unique_ptr<EnemyData>>& GetTileList() {
		return m_enemyData;
	}
};
