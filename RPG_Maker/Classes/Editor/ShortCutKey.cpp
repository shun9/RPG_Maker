//************************************************/
//* @file  :ShortCutKey.cpp
//* @brief :ShortCutKey‚ÌƒNƒ‰ƒX
//* @date  :2017/10/01
//* @author:K.Yamamoto
//************************************************/

#include "ShortCutKey.h"

using namespace std;
using namespace ShunLib;

ShortCutKey::ShortCutKey()
{
}

ShortCutKey::~ShortCutKey()
{
}

void ShortCutKey::Add(KEY keyList, std::function<void()> func)
{
	m_shortCutList.push_back(make_unique<pair<KEY, function<void()>>>(keyList, func));
}

bool ShortCutKey::Update()
{
	auto& manager = *KeyManager::GetInstance();

	if (manager.IsPushed(KEY::R_CTRL) ||
		manager.IsPushed(KEY::L_CTRL))
	{
		for each(auto& shortCut in m_shortCutList) {
			if(manager.IsTracker(shortCut.get()->first)) {
				shortCut.get()->second();
				return true;
			}
		}
	}
	return false;
}

