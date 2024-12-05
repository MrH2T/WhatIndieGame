#pragma once

#include<unordered_map>
#include<string>
#include"../framework.h"

HBITMAP subBitmap(const HBITMAP&  src, RECT rect);
std::vector<HBITMAP> decomposeBitmap(const HBITMAP &src, int rows, int cols, int width, int height);

class ResourceManager {
public:
	static ResourceManager& getInstance();
	void loadResource(const std::string& name, LPCWSTR filePath, HWND hWnd, WPARAM wParam, LPARAM lParam);
	void loadResource(const std::string& name, HBITMAP content);
	HBITMAP getResource(const std::string& name);
private:
	ResourceManager(){}
	std::unordered_map<std::string, HBITMAP> resources;
	ResourceManager(const ResourceManager&) = delete;
	void operator=(const ResourceManager&) = delete;
};