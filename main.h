#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Windows.h>
#include <fstream>
#include <map>
#include <chrono>
#include <future>
#include <ctime>
#include "include\curl\curl.h"
#include <iostream>
#include <string>
#pragma comment(lib,"ws2_32.lib")

#ifdef _DEBUG
#pragma comment (lib, "lib/libcurl_a_debug.lib")
#else
#pragma comment (lib, "lib/libcurl_a.lib")
#endif
