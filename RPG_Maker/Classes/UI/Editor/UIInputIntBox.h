//************************************************/
//* @file  :UIInputIntBox.h
//* @brief :UIInputIntBoxのクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_Vec2.h>
#include "UIBase.h"
#include <list>
#include <memory>
#include <functional>
#include <string>

class UIInputIntBox : public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	 int* m_num;

	 int m_max;
	 int m_min;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIInputIntBox(const std::string& name, int* num);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIInputIntBox() override {}

	virtual void DrawUpdate() override;

	void SetValuWidth(int min, int max) { 
		m_min = min; 
		m_max = max;
	}
};

////デフォルト：0
//ImGuiInputTextFlags_CharsDecimal = 1 << 0、// Allow 0123456789。+ - */
//ImGuiInputTextFlags_CharsHexadecimal = 1 << 1、// Allow 0123456789ABCDEFabcdef
//ImGuiInputTextFlags_CharsUppercase = 1 << 2、// a..zをA..Zに変換する
//ImGuiInputTextFlags_CharsNoBlank = 1 << 3、//空白、タブを除外する
//ImGuiInputTextFlags_AutoSelectAll = 1 << 4、//最初にマウスをフォーカスしたときにテキスト全体を選択する
//ImGuiInputTextFlags_EnterReturnsTrue = 1 << 5、// Enterキーが押されたときに（値が変更されたときとは対照的に）「true」を返します。
//ImGuiInputTextFlags_CallbackCompletion = 1 << 6、// TABを押すとユーザー関数を呼び出します（完了処理のために）
//ImGuiInputTextFlags_CallbackHistory = 1 << 7、//上向き/下向き矢印を押してユーザ機能に電話する（履歴処理用）
//ImGuiInputTextFlags_CallbackAlways = 1 << 8、//毎回ユーザー関数を呼び出します。ユーザコードは、カーソル位置を照会し、テキストバッファを変更することができる。
//ImGuiInputTextFlags_CallbackCharFilter = 1 << 9、//文字をフィルタリングするユーザ関数を呼び出します。 data-> EventCharを変更して入力を置き換えたり、1を返して文字を破棄したりします。
//ImGuiInputTextFlags_AllowTabInput = 1 << 10、// TABを押すと、テキストフィールドに '\ t'文字が入力されます
//ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 11、//複数行モードでは、Enterキーでフォーカスを外し、Ctrl + Enterで新しい行を追加します（デフォルトは逆：Ctrl + Enterで非表示、Enterで行を追加）。
//ImGuiInputTextFlags_NoHorizo​​ntalScroll = 1 << 12、//カーソルを水平方向に移動しない
//ImGuiInputTextFlags_AlwaysInsertMode = 1 << 13、//挿入モード
//ImGuiInputTextFlags_ReadOnly = 1 << 14、//読み取り専用モード
//ImGuiInputTextFlags_Password = 1 << 15、//パスワードモードでは、すべての文字を「*」として表示します。
// [内部]
//ImGuiInputTextFlags_Multiline = 1 << 20 // InputTextMultiline（）による内部使用