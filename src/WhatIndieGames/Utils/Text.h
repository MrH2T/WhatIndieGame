#pragma once

#include<windows.h>
#include<string>

#define TEXT_ITALIC (1<<1)
#define TEXT_UNDERLINE (1<<2)
#define TEXT_BOLD (1<<3)
#define TEXT_DELETE (1<<4)

const HFONT defaultFont = CreateFontW(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"SimSun");
std::wstring to_wide_string(const std::string &str);

class Text {
public:
	Text();
	Text(std::wstring text, COLORREF t_color = RGB(255, 255, 255), COLORREF b_color = RGB(0, 0, 0), std::wstring fname = L"SimSun", int ht = 25, int wd = 0, unsigned int st = 0);
	void setContent(std::wstring text);
	void setTColor(COLORREF color);
	void setBColor(COLORREF bcolor);
	void setState(unsigned int st);
	void setHeight(int ht);
	//HFONT getFont();
	HFONT interpreteFont();
	COLORREF getTColor();
	COLORREF getBColor();
	int getHeight();
	unsigned int getState();
	std::wstring getContent();
private:
	unsigned int state;
	int height,width;
	//HFONT font;
	std::wstring content,fontname;
	COLORREF text_color, bg_color;
};