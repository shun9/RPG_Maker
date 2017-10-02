//************************************************/
//* @file  :BattleTextPreset.h
//* @brief :�퓬���̕�����̈ꗗ
//* @date  :2017/10/02
//* @author:S.Katou
//************************************************/
#pragma once
#include <string>
#include <sstream>

#define ATTACK_TEXT(name) name + std::string(u8"�̂��������I�I")
#define DEFENCE_TEXT(name) name + std::string(u8"�݂͂��܂����Ă���")
#define TAKE_DAMEGE_TEXT(name,damege) name + std::string(u8"��") + damege + std::string(u8"�̃_���[�W���������I�I")
#define KILL_MONSTER_TEXT(name) name + std::string(u8"�����������I�I")
#define LOSE_TEXT(name) name + std::string(u8"�͂���Ă��܂���")
#define ESCAPE_TEXT(name) name + std::string(u8"�͂ɂ�������")


/// <summary>
/// ���l�̃e�L�X�g�𓾂�
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
std::string GetNumberText(int num);