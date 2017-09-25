//************************************************/
//* @file  :SL_Command.h
//* @brief :コマンドクラス
//* @date  :2017/07/26
//* @author:S.Katou
//************************************************/
#pragma once

namespace ShunLib
{

	template <class T>
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute(T* obj) = 0;
	};
}