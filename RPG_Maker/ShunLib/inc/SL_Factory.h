//************************************************/
//* @file  :SL_Factory.h
//* @brief :オブジェクト生成クラス
//* @date  :2017/07/20
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_MacroConstants.h>

namespace ShunLib
{
	template<class T>
	class Factory
	{
	private:
		//生成したものを保存しておく(削除するため)
		std::vector<T*>m_createdList;

	public:
		//オブジェクトの生成
		T* Create() {
			//生成コピー
			T* instance = new T;
			m_createdList.emplace_back(instance);
			return instance;
		}

		Factory() { }
		virtual ~Factory() { }

		//指定された要素を削除
		void Delete(T* pointer){
			auto itr = std::find(m_createdList.begin(), m_createdList.end(), pointer);
			DELETE_POINTER((*itr));
			m_createdList.erase(itr);
		}

		//Factoryから生み出されたものをすべて削除
		void AllDelete() {
			for (auto itr = m_createdList.begin(); itr != m_createdList.end(); itr++)
			{
				DELETE_POINTER((*itr));
			}
			m_createdList.clear();
			m_createdList.shrink_to_fit();
		}
	};
}