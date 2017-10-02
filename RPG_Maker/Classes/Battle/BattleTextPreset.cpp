#include "BattleTextPreset.h"

std::string GetNumberText(int num)
{
	std::stringstream ss;
	ss << num;
	std::string str = std::to_string(num);
	std::string buf;

	for (int i = 0; i < (int)str.length(); i++) {

		char c = str[i];
		switch (c)
		{
		case '0':
			buf += u8"‚O";
			break;
		case '1':
			buf += u8"‚P";
			break;
		case '2':
			buf += u8"‚Q";
			break;
		case '3':
			buf += u8"‚R";
			break;
		case '4':
			buf += u8"‚S";
			break;
		case '5':
			buf += u8"‚T";
			break;
		case '6':
			buf += u8"‚U";
			break;
		case '7':
			buf += u8"‚V";
			break;
		case '8':
			buf += u8"‚W";
			break;
		case '9':
			buf += u8"‚X";
			break;
		default:
			break;
		}
	}

	return buf;
}