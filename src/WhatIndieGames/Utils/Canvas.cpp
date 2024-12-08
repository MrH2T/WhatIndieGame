#include"Canvas.h"
#include"../Manager/GameManager.h"
#include"../Game.h"
#include<time.h>

DrawableObject::DrawableObject(){
	anim = Animation();
	posX = 0;
	y_priobias = 0;
	posY = 0;
	//clickBox = RECT({ 0,0,0,0 });
	expandBox = RECT({ 0,0,0,0 });
	//onClick = [](void) {};
	priority = 0;
	objectType = TYPE_ANIM;
	state = DRAW_VISIBLE|DRAW_AUTOTICK;
}
DrawableObject::DrawableObject(Animation animation, int x,int y,RECT eBox, int prio,unsigned int st,int type) {
	anim = animation;
	posX = x;
	posY = y;
	y_priobias = 0;
	//clickBox = cBox;
	expandBox = eBox;
	//onClick = func;
	priority = prio;
	objectType =type;
	state = st;
}
DrawableObject::DrawableObject(Text txt, int x, int y, RECT eBox, int prio, unsigned int st) {
	text = txt;
	posX = x;
	posY = y;
	y_priobias = 0;
	expandBox = eBox;
	priority = prio;
	objectType = DrawableObject::TYPE_TEXT;
	state = st;
}

void DrawableObject::setYPrioBias(int yprio) {
	y_priobias = yprio;
}
void DrawableObject::setState(unsigned int st) {
	state = st;
}
void DrawableObject::switchState(unsigned int stbit,int b) {
	if (b)state |= stbit;
	else state &= ~stbit;
}
void DrawableObject::setExpandBox(RECT expandRect) {
	expandBox = expandRect;
}
void DrawableObject::setPriority(int prio) {
	priority = prio;
}
unsigned int DrawableObject::getState() {
	return state;
}


Canvas& Canvas::getInstance() {
	static Canvas instance;
	return instance;
}
//draw single object
void Canvas::drawSingleObject(HDC& membuf, HDC& load, DrawableObject &obj) {
	
	if (obj.objectType == DrawableObject::TYPE_ANIM) {
		SelectObject(load, obj.anim.getFrame());
		if (obj.getState() & DRAW_IGNOREBLANK)
		{
			StretchBlt(membuf, obj.posX, obj.posY, obj.expandBox.right, obj.expandBox.bottom,
				load, 0,0,obj.anim.getWidth(),obj.anim.getHeight(), SRCCOPY);
		}
		else 
		{
			TransparentBlt(
				membuf, obj.posX, obj.posY, obj.expandBox.right, obj.expandBox.bottom,
				load, 0, 0, obj.anim.getWidth(), obj.anim.getHeight(),
				RGB(11, 45, 14));
		}

	}
	if (obj.objectType == DrawableObject::TYPE_TEXT) {
		SelectObject(membuf, obj.text.getFont());
		SetTextColor(membuf, obj.text.getTColor());	// 设置颜色:黑色字体白色背景
		SetBkColor(membuf, obj.text.getBColor());
		RECT rect;
		rect.left = obj.posX;
		rect.top = obj.posY;
		rect.right = obj.posX + obj.expandBox.right;
		rect.bottom = obj.posY + obj.expandBox.bottom;
		DrawTextW(membuf, obj.text.getContent().c_str(), -1, &rect, DT_WORDBREAK);
	}
	//SUSPECT
	if (obj.objectType == DrawableObject::TYPE_BACKGROUND) {
		// now we will change expand_box to the needed portion of the map
		SelectObject(load, obj.anim.getFrame());
		StretchBlt(membuf,0, 0, WINDOW_WIDTH,WINDOW_HEIGHT,
			load, obj.expandBox.left,obj.expandBox.top,obj.expandBox.right,obj.expandBox.bottom,
			SRCCOPY);
	}
}
//paint the whole canvas
void Canvas::renderScene(HWND &hWnd) {
	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	blankBmp = CreateCompatibleBitmap(hdc_window, GameManager::getInstance().getSize().x,GameManager::getInstance().getSize().y);
	SelectObject(hdc_memBuffer, blankBmp);

	static auto comp = [&](const std::string& a, const  std::string& b) {return contents[a].posY+contents[a].y_priobias > contents[b].posY+contents[b].y_priobias; };
	static std::priority_queue < std::string, std::vector<std::string>, decltype(comp) > q(comp);
	for (int layer = MIN_LAYER; layer <= MAX_LAYER; layer++) {
		while (!q.empty())q.pop();
		for (auto obj: layers[layer]) {
			if ((contents[obj.first].getState() & DRAW_VISIBLE) && !(contents[obj.first].getState() & DRAW_ABSOLUTE))
			{
				q.push(obj.first);
			}
		}
		while (!q.empty()) { 
			drawSingleObject(hdc_memBuffer, hdc_loadBmp, contents[q.top()]); 
			q.pop(); 
		}
	}
	// 最后将所有的信息绘制到屏幕上
	HDC hdc_membuf2 = CreateCompatibleDC(hdc_window);
	HBITMAP blankBmp2 = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_membuf2, blankBmp2);
	Coord bias = GameManager::getInstance().getBias();
	BitBlt(hdc_membuf2, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, bias.x, bias.y,SRCCOPY);
	for (int layer = MIN_LAYER; layer <= MAX_LAYER; layer++) {
		for (auto obj : layers[layer]) {
			if ((contents[obj.first].getState() & DRAW_VISIBLE) && (contents[obj.first].getState() & DRAW_ABSOLUTE))
			{
				/*FILE* dbg = NULL;
				fopen_s(&dbg, "debug.txt", "a");
				fprintf(dbg, "AT:%s\n", obj.first.c_str());
				fclose(dbg);*/
				drawSingleObject(hdc_membuf2, hdc_loadBmp, contents[obj.first]);
			}
		}
	}

	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_membuf2,0,0, SRCCOPY);



	// 回收资源所占的内存（非常重要）
	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	DeleteDC(hdc_membuf2);
	DeleteObject(blankBmp2);
	// 结束绘制
	EndPaint(hWnd, &ps);
}
//add an object on the canvas
void Canvas::addObject(std::string identifier, DrawableObject obj) {
	
	contents[identifier] = obj;
	layers[obj.priority][identifier] = 1;
}
//delete an object on the canvas
void Canvas::deleteObject(std::string identifier) {
	if (contents[identifier].objectType == DrawableObject::TYPE_TEXT) {
		DeleteObject(contents[identifier].text.getFont());
	}
	layers[contents[identifier].priority].erase(identifier);
	contents.erase(identifier);
}

//handle all click events
//void Canvas::handleClickEvent(int mouseX, int mouseY) {
//	for (auto KV : contents) {
//		auto obj = KV.second;
//		if(obj.visible){
//			//THERE REMAIN CONFUSION
//			if (obj.posX+obj.clickBox.left <= mouseX && mouseX <= obj.posX+obj.clickBox.right &&
//				obj.posY+obj.clickBox.bottom <= mouseY && mouseY <= obj.posY+obj.clickBox.bottom) {
//				obj.onClick();
//			}
//		}
//	}
//}
//get object
DrawableObject& Canvas::getObject(std::string identifier) {
	if (contents.find(identifier) == contents.end())
	{
		FILE* dbg = NULL;
		fopen_s(&dbg, "debug.txt", "a");
		fprintf(dbg, "%s\n", identifier.c_str());
		fclose(dbg);
		MessageBoxA(NULL, "FUCK111", "FUCK", MB_ICONEXCLAMATION);
	}
	return contents[identifier];
}
//clear all objs
void Canvas::clearObjects() {
	contents.clear();
	layers.clear();
}
//tick frames
void Canvas::tickFrames() {
	for (auto &obj : contents) {
		if ((obj.second.getState() & DRAW_AUTOTICK)&&(obj.second.getState()&DRAW_VISIBLE)&&obj.second.objectType!=obj.second.TYPE_TEXT) {
			obj.second.anim.tickFrame();
		}
	}
}
void Canvas::revealYourself() {
	FILE* dbg = NULL;
	fopen_s(&dbg, "debug.txt", "a");
	for (auto& obj : contents) {
		fprintf(dbg, "%s\n", obj.first.c_str());
	}
	fprintf(dbg, "\n");
	fclose(dbg);
}