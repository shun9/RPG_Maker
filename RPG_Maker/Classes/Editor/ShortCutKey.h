//************************************************/
//* @file  :ShortCutKey.h
//* @brief :ShortCutKeyのクラス
//* @date  :2017/10/01
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_KeyManager.h>
#include <map>
#include <list>
#include <memory>
#include <functional>

#define KEY ShunLib::KeyManager::KEY_CODE

class ShortCutKey
{
private:

	std::list<std::unique_ptr<std::pair<KEY, std::function<void()>>>> m_shortCutList;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ShortCutKey();

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ShortCutKey();

	void Add(KEY keyList, std::function<void()> func);

	bool Update();
};