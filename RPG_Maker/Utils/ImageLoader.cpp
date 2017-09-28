//************************************************/
//* @file  :ImageLoader.cpp
//* @brief :イメージを読み込むクラス
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#pragma once
#include "ImageLoader.h"

std::wstring ImageLoader::OpenLoadingDialog()
{
	//CString setting = "実行ファイル（*.exe)|*.exe|全て(*.*)|*.*||";
	//CFileDialog dlg(TRUE, "*.exe", "", OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, setting, this);

	OPENFILENAME ofn;
	char szFile[MAX_PATH] = "";
	char szFileTitle[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter =
		TEXT("PNG(*.png)\0*.png\0")
		TEXT("BMP(*.bmp)\0*.bmp\0")
		TEXT("JPG(*.jpg)\0*.jpg\0");
	ofn.lpstrFileTitle = (LPWSTR)szFileTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrFile = (LPWSTR)szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	GetOpenFileName(&ofn);

	char szPath[MAX_PATH] = "";
	std::wstring tmp = L"Image\\";
	tmp += ofn.lpstrFileTitle;
	tmp.push_back(*L"\0");

	//std::wstring tmp = GetRelativePath(ofn.lpstrFile);
	return tmp;
}

std::wstring ImageLoader::GetRelativePath(LPWSTR fullPath)
{
	char path[_MAX_PATH] ="";
	char szPath[_MAX_PATH]="";
	DWORD dwRet;

	dwRet = GetModuleFileName(NULL, (LPWSTR)szPath, sizeof(szPath));

	if (dwRet == 0) {
		//失敗
		return NULL;
	}

	LPWSTR szpath = (LPWSTR)szPath;
	PathRelativePathTo((LPWSTR)path, szpath, FILE_ATTRIBUTE_DIRECTORY, fullPath, FILE_ATTRIBUTE_ARCHIVE);

	LPWSTR tmp = (LPWSTR)path;
	std::wstring relativePathW = tmp;
	wchar_t* end = L"\0";
	relativePathW.push_back(*end);
	//Widen(relativePath, relativePathW);
	return relativePathW;
}

//ワイド文字列からマルチバイト文字列
//ロケール依存
void ImageLoader::Narrow(const std::wstring &src, std::string &dest) {
	char *mbs = new char[src.length() * MB_CUR_MAX + 1];
	wcstombs(mbs, src.c_str(), src.length() * MB_CUR_MAX + 1);
	dest = mbs;
	delete[] mbs;
}

//マルチバイト文字列からワイド文字列
//ロケール依存
void ImageLoader::Widen(const std::string &src, std::wstring &dest) {
	wchar_t *wcs = new wchar_t[src.length() + 1];
	mbstowcs(wcs, src.c_str(), src.length() + 1);
	dest = wcs;
	delete[] wcs;
}