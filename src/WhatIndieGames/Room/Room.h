#pragma once
#include"../framework.h"
#include"../Entity/Entity.h"

#define TILE_GAME_SIZE 40
#define TILE_FILE_SIZE 20

#define ROOM_ENTRY_SAVING 114514

class Room {
public:
	Room(int id, HBITMAP pic, int width_, int height_);
	Room(int id, HBITMAP tiles, int setrows,int setcols,std::vector<std::vector<int>> tile_info);
	virtual ~Room() { clearEntities(); }
	virtual void roomUpdate() { }
	void loadMap(HBITMAP pic,int width_,int height_);
	void calculateMap(HBITMAP tiles, int setrows,int setcols,std::vector<std::vector<int>> tile_info,int size=TILE_FILE_SIZE);
	virtual void roomInit() {};
	int getWidth();
	int getHeight();
	void addEntity(std::string entname, Entity* ent);
	void addEntity(Entity* ent);
	void deleteEntity(std::string entname);
	Entity* getEntity(std::string entname);
	std::unordered_map<std::string, int> localVar;
	const int roomId();
	
protected:
	int room_id;

	int width, height;
	//std::function<void()> initFunc;
	HBITMAP map;
	void clearEntities();
	std::unordered_map<std::string, Entity*> entities;
};