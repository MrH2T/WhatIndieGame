#pragma once
#include<unordered_map>
#include"Animation.h"
#include"Text.h"
#include<windows.h>
#include<string>
#include<functional>
#include<queue>
#pragma comment(lib,"Msimg32.lib")

#define DRAW_VISIBLE (1<<0)
#define DRAW_AUTOTICK (1<<1)
#define DRAW_IGNOREBLANK (1<<2)
#define DRAW_ABSOLUTE (1<<3)

#define LAYER_BACKGROUND 0
#define LAYER_ITEM 1
#define LAYER_ENTITY 2 


class DrawableObject {
public:
	static const int TYPE_ANIM = 0, TYPE_TEXT = 1, TYPE_BACKGROUND = 2;

	int posX, posY;
	int priority,y_priobias;
	unsigned int state;
	int objectType; //0: animation; 1: text; 2: background

	Animation anim;
	Text text;


	//RECT clickBox;
	RECT expandBox;
	//std::function<void()> onClick;
	DrawableObject();
	//DrawableObject(Animation animation, int x,int y, RECT cBox, RECT eBox, std::function<void()> func, int prio=0, int type=TYPE_ANIM, unsigned int st=DRAW_VISIBLE);
	DrawableObject(Animation animation, int x, int y, RECT eBox, int prio = 0, unsigned int st = DRAW_VISIBLE|DRAW_AUTOTICK, int type=TYPE_ANIM);
	DrawableObject(Text txt, int x, int y, RECT eBox, int prio = 0, unsigned int st=DRAW_VISIBLE);
	void setState(unsigned int st);
	void switchState(unsigned int stbit, int b=1);
	unsigned int getState();
	void setExpandBox(RECT expandRect);
	void setPriority(int prio);
	void setYPrioBias(int yprio);
};

class Canvas {
public:
	static const int MIN_LAYER = 0, MAX_LAYER = 10;
	static Canvas& getInstance();
	//draw single object
	void drawSingleObject(HDC& membuf, HDC& load, DrawableObject &obj);
	//paint the whole canvas
	void renderScene(HWND &hWnd);
	//add an object on the canvas
	void addObject(std::string identifier, DrawableObject obj);	
	//delete an object on the canvas
	void deleteObject(std::string identifier);	
	//get an obj and modify
	DrawableObject& getObject(std::string identifier);
	
	//handle all click events
	//void handleClickEvent(int mouseX,int mouseY);
	//clear all objs
	void clearObjects();
	//tick frames
	void tickFrames();
private:
	Canvas() {}
	std::unordered_map<std::string, DrawableObject> contents;	//storing all paintable objects
	std::unordered_map<int, std::unordered_map<std::string, bool> >layers;
};