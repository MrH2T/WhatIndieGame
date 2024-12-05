// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include<mmsystem.h>
#include<Digitalv.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>    // 可选
#include <SFML/Network.hpp>  // 可选

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <thread>
#include <vector>
#include <string>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include<unordered_map>
#include<fstream>

struct Coord {
	int x, y;
};