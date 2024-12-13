#include"Entity.h"
#include"../Manager/Managers.h"
Entity::Entity() {
	visible = 0; type = ENTITY_BLANK; passable = 0;
	status = ENTITY_STATIC;
	direction = DIRECTION_DOWN;
	react = false;
	collide = false;
	speed = pos_x = pos_y = v_x = v_y = 0;
	collision_box = { 0,0,0,0 };
	draw_box = { 0,0,0,0 };
	draw_obj = "";
	pos_x = pos_y = 0;
}
Entity::Entity(std::string name_, int posx,int posy, RECT c_box,RECT d_box, std::vector<Animation> static_anim, std::vector<Animation> walking_anim) {
	name = name_;
	visible = 0; type = ENTITY_COMMON; passable = 0;
	status = ENTITY_STATIC;
	direction = DIRECTION_DOWN;
	speed = pos_x = pos_y = v_x = v_y = 0;
	react = false;
	collide = false;
	pos_x = posx, pos_y = posy;
	collision_box = c_box;
	draw_box = d_box;
	draw_obj =name_+"_drawobj";
	for (int i = 0; i < 4; i++) {
		std::string ids = "STATIC_", idw = "WALKING_";
		ids += char(i+48), idw += char(i+48);
		anims[ids] = static_anim[i];
		anims[idw] = walking_anim[i];
	}
	createDrawObj();
}
Entity::Entity(std::string name_, int posx, int posy, RECT c_box,bool pass) {
	name = name_;
	visible = 0; type = ENTITY_AIRWALL; passable = pass;
	react = false;
	collide = false;
	status = ENTITY_STATIC;
	direction = DIRECTION_DOWN;
	speed = pos_x = pos_y = v_x = v_y = 0;
	pos_x = posx, pos_y = posy;
	draw_box=collision_box = c_box;

}
Entity::Entity(std::string name_, int posx, int posy, RECT c_box, RECT d_box, Animation anim,bool pass) {
	name = name_;
	visible = 0; type = ENTITY_ANIM; passable = pass;
	status = ENTITY_STATIC;
	direction = DIRECTION_DOWN;
	react = false;
	collide = false;
	speed = v_x = v_y = 0;
	pos_x = posx, pos_y = posy;
	collision_box = c_box;
	draw_box = d_box;
	draw_obj = name_ + "_drawobj";
	anims["STATIC_0"] = anim;
	createDrawObj();
}
void Entity::setReaction(std::function<void()> react_func,int type) {
	if (react_func == NULL) { if (type == 0)react = false; if (type == 1)collide = false; return; }
	reaction = react_func;
	if(type==0)react = true;
	if (type == 1)collide = true;
}
std::string Entity::getName() {
	return name;
}
Coord Entity::getPos() {
	return { pos_x,pos_y };
}
bool Entity::isVisible() {
	return visible;
}
int Entity::getType() {
	return type;
}
int Entity::getDirection() {
	return direction;
}
bool Entity::isPassable() {
	return passable;
}
bool Entity::isReact() {
	return react;
}
bool Entity::isCollide() {
	return collide;
}
void Entity::reactRun() {
	reaction();
}
void Entity::createDrawObj() {
	
	Canvas::getInstance().addObject(draw_obj, DrawableObject(anims["STATIC_0"],pos_x,pos_y,draw_box,LAYER_ENTITY,DRAW_AUTOTICK));
}
Entity::~Entity() {
	delEvents();
	Canvas::getInstance().deleteObject(draw_obj);
}
RECT Entity::getCollisionBox() {
	return collision_box;
}
int Entity::getStatus() {
	return status;
}
void Entity::resizeDrawbox(RECT d_box) {
	draw_box = d_box;
	Canvas::getInstance().getObject(draw_obj).expandBox = d_box;
}
void Entity::setSpeedX(int vx) {
	v_x = vx;
}
void Entity::setSpeedY(int vy) {
	v_y = vy;
}
void Entity::setLayer(int layer) {
	Canvas::getInstance().setLayer(draw_obj,layer);
}
void Entity::setPos(Coord pos,bool force) {
	pos_x = pos.x;
	pos_y = pos.y;
	if(!force)updatePosition();
	if (force) {
		Canvas::getInstance().getObject(draw_obj).posX = pos_x,
			Canvas::getInstance().getObject(draw_obj).posY = pos_y;
	}
}
void Entity::setDirection(int dir) {
	if (dir != direction) {
		direction = dir;
		updateFigure();
	}
	/*if (status == ENTITY_STATIC) {
		Canvas::getInstance().getObject(draw_obj).anim = anims["STATIC_" + std::to_string(direction)];
	}
	else if (status == ENTITY_WALKING) {
		Canvas::getInstance().getObject(draw_obj).anim = anims["WALKING_" + std::to_string(direction)];
	}*/
}
void Entity::setDrawYPrioBias(int ypriobias){
	Canvas::getInstance().getObject(draw_obj).setYPrioBias(ypriobias);
}
void Entity::setStatus(int state) {
	if(status!=state)
	{
		status = state;
		updateFigure();
	}
}
void Entity::setPassable(bool pass) {
	passable = pass;
}
void Entity::updateFigure() {
	if (status == ENTITY_STATIC) {
		Canvas::getInstance().getObject(draw_obj).anim = anims["STATIC_" + std::to_string(direction)];
	}
	else if (status == ENTITY_WALKING) {
		Canvas::getInstance().getObject(draw_obj).anim = anims["WALKING_" + std::to_string(direction)];
	}
}
void Entity::setVisible(bool vis) {
	visible = vis;
	Canvas::getInstance().getObject(draw_obj).switchState(DRAW_VISIBLE, vis);
}
void Entity::updatePosition() {
	if (type != ENTITY_COMMON) return;
	if (GameManager::getInstance().globalVar[GLOBAL_PAUSED])return;
	if (v_x > 0)setDirection(DIRECTION_RIGHT);
	else if (v_x < 0) setDirection(DIRECTION_LEFT);
	else {
		if (v_y < 0)setDirection(DIRECTION_UP);
		if (v_y > 0)setDirection(DIRECTION_DOWN);
	}
	if (v_x == 0 && v_y == 0)setStatus(ENTITY_STATIC);
	else setStatus(ENTITY_WALKING);
	int nx = pos_x + v_x, ny = pos_y + v_y;
	if (GameManager::getInstance().checkWalkable(name,nx, ny, collision_box))pos_x = nx, pos_y = ny;

	Canvas::getInstance().getObject(draw_obj).posX = pos_x;
	Canvas::getInstance().getObject(draw_obj).posY = pos_y;
}
void Entity::bindEvent(std::string event, std::string ename, std::function<void()> func) {
	EventManager::getInstance().subscribe(event, ename, func);
	events[ename] = event;
}
void Entity::delEvent(std::string ename) {
	EventManager::getInstance().unsubscribe(events[ename], ename);
	events.erase(ename);
}
void Entity::delEvents() {
	for (auto& i : events) {
		EventManager::getInstance().unsubscribe(i.second, i.first);
	}
	events.clear();
}
bool Entity::isOnCollide() {
	return onCollide;
}
void Entity::setOnCollide(bool c) {
	onCollide = c;
}