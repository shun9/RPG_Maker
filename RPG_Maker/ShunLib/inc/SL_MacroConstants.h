//************************************************/
//* @file  :MacroConstants.h
//* @brief :自作マクロ定数まとめ
//* @date  :2017/05/10
//* @author:S.Katou
//************************************************/
#pragma once

namespace ShunLib
{
	//ポインター消去用
#define DELETE_POINTER(p) if (p!=nullptr){delete p; p = nullptr;}
#define DELETE_ARRAY(p) if (p!=nullptr){delete[] p; p = nullptr;}

#define SAFE_DELETE(p) if (p!=nullptr){delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p) if (p!=nullptr){delete[] p; p = nullptr;}
#define SAFE_RELEASE(x) if (x!=NULL){x->Release(); x = NULL;}

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
}