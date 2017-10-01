//************************************************/
//* @file  :SL_CommandInput.h
//* @brief :コマンドクラス
//* @date  :2017/07/26
//* @author:S.Katou
//************************************************/
#pragma once

#include <map>
#include <vector>
#include <SL_Command.h>
#include <SL_MacroConstants.h>

namespace ShunLib
{
	template <class _KEY, class T>
	class CommandInput
	{
	private:
		std::map<_KEY, Command<T>*>m_commandList;

	public:
		//引数のキーが設定されていたらコマンドを返す
		Command<T>* HandleInput(const _KEY& key) {
			auto itr = m_commandList.find(key);
			if (itr != m_commandList.end()) {
				return (itr)->second;
			}
			else {
				return nullptr;
			}
		}

		//コマンドの設定
		void SetCommand(const _KEY& key, Command<T>* command){
			m_commandList[key] = command;
		}

		//キーのリストを返す
		std::vector<_KEY> GetKeyList() {
			std::vector<_KEY>keyList;
			for (auto itr = m_commandList.begin(); itr != m_commandList.end(); itr++){
				keyList.push_back((itr)->first);
			}
			return keyList;
		}

		~CommandInput() {
			for (auto itr = m_commandList.begin(); itr != m_commandList.end(); itr++)
			{
				DELETE_POINTER((itr)->second);
			}
			//m_commandList.clear();
			//m_commandList.shrink_to_fit();
		}
	};
}
