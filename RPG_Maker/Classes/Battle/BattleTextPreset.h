//************************************************/
//* @file  :BattleTextPreset.h
//* @brief :戦闘中の文字列の一覧
//* @date  :2017/10/02
//* @author:S.Katou
//************************************************/
#pragma once
#include <string>
#include <sstream>

#define ATTACK_TEXT(name) name + std::string(u8"のこうげき！！")
#define DEFENCE_TEXT(name) name + std::string(u8"はみをまもっている")
#define TAKE_DAMEGE_TEXT(name,damege) name + std::string(u8"は") + damege + std::string(u8"のダメージをうけた！！")
#define KILL_MONSTER_TEXT(name) name + std::string(u8"をたおした！！")
#define LOSE_TEXT(name) name + std::string(u8"はやられてしまった")
#define ESCAPE_TEXT(name) name + std::string(u8"はにげだした")


/// <summary>
/// 数値のテキストを得る
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
std::string GetNumberText(int num);