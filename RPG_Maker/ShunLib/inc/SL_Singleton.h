//************************************************/
//* @file  :Singleton.h
//* @brief :シングルトン
//* @date  :2017/06/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_MacroConstants.h>

namespace ShunLib
{
	template<class T>
	class Singleton
	{
	private:
		//実体
		static T* m_instance;

	public:
		/// <summary>
		/// 実体の取得
		/// </summary>
		/// <returns>実体</returns>
		static T* GetInstance() {
			//無ければ作成
			if (m_instance == nullptr) {
				m_instance = new T();
			}
			return m_instance;
		}


		/// /// <summary>
		/// 実体の破棄
		/// </summary>
		static void Destroy() {
			DELETE_POINTER(m_instance);
		}


	protected:
		//派生クラス以外から作成できないようにする
		Singleton() {}
		virtual ~Singleton() {}

	private:
		//コピーできないように
		Singleton(const Singleton& single);

		//代入できないように
		const Singleton& operator = (const Singleton& single) {};
	};

	template<class T>
	T* ShunLib::Singleton<T>::m_instance = nullptr;
}
