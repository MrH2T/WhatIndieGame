#include"Text.h"


std::wstring to_wide_string(const std::string& str)
{
	LPCSTR pszSrc = str.c_str();
	int nLen = MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, NULL, 0);
	if (nLen == 0)
		return std::wstring(L"");

	wchar_t* pwszDst = new wchar_t[nLen];
	if (!pwszDst)
		return std::wstring(L"");

	MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, pwszDst, nLen);
	std::wstring wstr(pwszDst);
	delete[] pwszDst;
	pwszDst = NULL;

	return wstr;
}

Text::Text() {
	state = 0;
	content = L"";
	fontname = L"";
	text_color = RGB(255,255,255);
	bg_color = RGB(0, 0, 0);
	font = NULL;
	height = 25;
}
void Text::interpreteFont() {
	font = CreateFontW(height, width, 0, 0, (state & TEXT_BOLD) ? FW_BOLD : FW_NORMAL,
		(state & TEXT_ITALIC) ? TRUE : FALSE,
		(state & TEXT_UNDERLINE) ? TRUE : FALSE,
		(state & TEXT_DELETE) ? TRUE : FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		fontname.c_str());
}
Text::Text(std::wstring text, COLORREF t_color, COLORREF b_color, std::wstring fname, int ht, int wd, unsigned int st) {
	content = text;
	text_color = t_color;
	bg_color = b_color;
	state = st;
	height = ht;
	width = wd;
	fontname = fname;
	if (ht == 25 && wd == 0 && st == 0&&fname==L"SimSun") {
		font = defaultFont;
	}
	else interpreteFont();
}
void Text::setTColor(COLORREF color) {
	text_color = color;
	//interpreteFont();
}
void Text::setBColor(COLORREF color) {
	bg_color = color;
	//interpreteFont();
}
void Text::setContent(std::wstring text) {
	content = text;
	//interpreteFont();
}
void Text::setHeight(int ht) {
	height = ht;
	//interpreteFont();
}
void Text::setState(unsigned int st){
	state = st;
	//interpreteFont();
}
HFONT Text::getFont() {
	//interpreteFont();
	return font;
}
COLORREF Text::getTColor() {
	return text_color;
}
COLORREF Text::getBColor() {
	return bg_color;
}
int Text::getHeight() {
	return height;
}
unsigned int Text::getState() {
	return state;
}
std::wstring Text::getContent() {
	return content;
}