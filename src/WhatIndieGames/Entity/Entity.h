#pragma once

#include<unordered_map>
#include"../framework.h"
#include"../Utils/Animation.h"
#include"../Utils/Canvas.h"

#define DIRECTION_DOWN 0
#define DIRECTION_LEFT 1
#define DIRECTION_UP 2
#define DIRECTION_RIGHT 3

#define ENTITY_STATIC 0
#define ENTITY_WALKING 1

#define ENTITY_BLANK 0
#define ENTITY_COMMON 1
#define ENTITY_AIRWALL 2
#define ENTITY_ANIM 3


class Entity {
public:
	~Entity();
	Entity();
	Entity(std::string name_, int posx, int posy, RECT c_box,RECT d_box, std::vector<Animation> static_anim, std::vector<Animation> walking_anim);
	Entity(std::string name_, int posx, int posy, RECT c_box, bool pass = false);
	Entity(std::string name_, int posx, int posy, RECT c_box, RECT d_box,Animation anim,bool pass=false);
	RECT getCollisionBox();
	bool isPassable();
	bool isReact();
	bool isCollide();
	bool isOnCollide();
	int getStatus();
	int getType();
	int getDirection();
	void setOnCollide(bool c);
	void setStatus(int state);
	void setSpeedX(int vx);
	void setSpeedY(int vy);
	void setVisible(bool vis = 0);
	void setDirection(int dir);
	void setPassable(bool pass);
	void setPos(Coord pos,bool force=0);
	void setDrawYPrioBias(int ypriobias);
	void setLayer(int layer);
	//type0:react, type1:collide
	void setReaction(std::function<void()> react_func,int type);
	void updatePosition();
	void updateFigure();
	void bindEvent(std::string event, std::string name, std::function<void()> func);
	void delEvent(std::string name);
	void delEvents();
	void createDrawObj();
	Coord getPos();
	void reactRun();
private:
	std::string name;
	bool visible,react,collide,onCollide;
	//it seems like an unused var
	int type;
	int speed,direction;
	int pos_x, pos_y;
	int v_x, v_y;
	int status, passable; 
	

	RECT collision_box,draw_box;
	std::string draw_obj;


	// should have: static down/left/up/right; walking down/left/up/right
	//SHOULD WITH NAME STATIC_i/WALKING_i
	std::unordered_map <std::string, int >localVar;
	std::unordered_map<std::string, Animation> anims;
	std::unordered_map<std::string,std::string> events;
	std::function<void()> reaction;
};