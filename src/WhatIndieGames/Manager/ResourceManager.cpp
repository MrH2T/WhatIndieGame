#include"ResourceManager.h"


HBITMAP subBitmap(const HBITMAP &src, RECT rect) {
	HDC hdcSrc = CreateCompatibleDC(NULL);
	HDC hdcDest = CreateCompatibleDC(NULL);

	SelectObject(hdcSrc, src);

	HBITMAP hNewBitmap = CreateCompatibleBitmap(hdcSrc, rect.right-rect.left, rect.bottom-rect.top);
	SelectObject(hdcDest, hNewBitmap);
	BitBlt(hdcDest, 0, 0, rect.right - rect.left, rect.bottom - rect.top, hdcSrc,rect.left, rect.top, SRCCOPY);

	DeleteDC(hdcSrc);
	DeleteDC(hdcDest);
	return hNewBitmap;
}
std::vector<HBITMAP> decomposeBitmap(const HBITMAP& src, int rows, int cols, int width, int height) {
	std::vector<HBITMAP> vec; vec.clear();
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			vec.push_back(subBitmap(src, { c * width,r * height,c * width + width,r * height * height }));
		}
	}
	return vec;
}

ResourceManager& ResourceManager::getInstance() {
	static ResourceManager instance;
	return instance;
}
void ResourceManager::loadResource(const std::string& name, LPCWSTR filePath, HWND hWnd, WPARAM wParam, LPARAM lParam) {
	resources[name] = (HBITMAP)LoadImage(((LPCREATESTRUCT)lParam)->hInstance, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}
void ResourceManager::loadResource(const std::string& name, HBITMAP content) {
	resources[name] = content;
}
//return the file path of the resource
HBITMAP ResourceManager::getResource(const std::string& name) {
	if (resources.find(name) == resources.end())MessageBoxA(NULL, "FUCK", "FUCK", NULL);
	return resources[name];
}

