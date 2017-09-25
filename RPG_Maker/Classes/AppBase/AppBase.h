//************************************************/
//* @file  :AppBase.h
//* @brief :アプリケーションの基底クラス
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
class AppBase
{
public:
	AppBase() {}
	virtual ~AppBase() {}

	//定番のやつ
	virtual void Initialize() = 0;
	virtual void Update    () = 0;
	virtual void Render    () = 0;
	virtual void Finalize  () = 0;

private:

};
