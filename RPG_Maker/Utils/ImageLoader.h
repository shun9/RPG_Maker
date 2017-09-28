//************************************************/
//* @file  :ImageLoader.h
//* @brief :イメージを読み込むクラス
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Singleton.h>
#include <Windows.h>
#include <shlwapi.h>
#include <string>

class ImageLoader : public ShunLib::Singleton<ImageLoader>
{
	friend ShunLib::Singleton<ImageLoader>;
private:

public:
	std::wstring OpenLoadingDialog();

private:
	ImageLoader() {}
	~ImageLoader() {}

	std::wstring GetRelativePath(LPWSTR fPath);
	void Widen(const std::string &src, std::wstring &dest);
	void Narrow(const std::wstring &src, std::string &dest);
};
