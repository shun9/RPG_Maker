//************************************************/
//* @file  :ShortCutKey.h
//* @brief :ShortCutKey�̃N���X
//* @date  :2017/10/01
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_KeyManager.h>
#include <map>
#include <list>
#include <memory>
#include <functional>

#define KEY_CODE ShunLib::KeyManager::KEY_CODE

class ShortCutKey
{
private:

	std::list<std::unique_ptr<std::pair<KEY_CODE, std::function<void()>>>> m_shortCutList;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ShortCutKey();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~ShortCutKey();

	void Add(KEY_CODE keyList, std::function<void()> func);

	bool Update();
};