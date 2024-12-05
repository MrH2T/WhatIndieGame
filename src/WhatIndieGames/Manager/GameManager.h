#pragma once
#include<string>
#include<unordered_map>
#include"../Entity/Entity.h"
#include"../Room/AllRooms.h"
#include"../Battle/Battle.h"
#include"ItemManager.h"
#include"../Game.h"

#define GLOBAL_GAME_STATE "GLOBAL_GAME_STATE_VARIABLE"
#define GAME_STATE_COMMON 0
#define GAME_STATE_MAINMENU 1
#define GAME_STATE_CUTSCENE 2
//#define GAME_STATE_CONVERSATION 3
#define GAME_STATE_SHOP 4
#define GAME_STATE_BATTLE 5
#define GAME_STATE_OTHER 6
#define GAME_STATE_DYING 7

#define GLOBAL_ROOM_ID "GLOBAL_ROOM_ID_VARIABLE"

#define GLOBAL_PAUSED "GLOBAL_ISPAUSED_VARIABLE"
#define GLOBAL_MENUING "GLOBAL_ISMENUING_VARIABLE"
#define GLOBAL_INCONVERSATION "GLOBAL_INCONVERSATION_VARIABLE"

#define GLOBAL_BATTLE_PREPARING	"GLOBAL_BATTLE_PREPARING_VARIABLE"
#define ENTITY_MAIN_PLAYER "MainPlayer"

#define ROOM_ENTRANCE "ROOM_ENTRANCE_POS_VARIABLE"

#define GLOBAL_PLAYER_HP "GLOBAL_PLAYER_HP_VARIABLE"
#define GLOBAL_PLAYER_MAXHP "GLOBAL_PLAYER_MAXHP_VARIABLE"
#define GLOBAL_PLAYER_DEF "GLOBAL_PLAYER_DEF_VARIABLE"
#define GLOBAL_PLAYER_ATK "GLOBAL_PLAYER_ATK_VARIABLE"
#define GLOBAL_PLAYER_LV "GLOBAL_PLAYER_LV_VARIABLE"
#define GLOBAL_PLAYER_EXP "GLOBAL_PLAYER_EXP_VARIABLE"
#define GLOBAL_PLAYER_GOLD "GLOBAL_PLAYER_GOLD_VARIABLE"

class GameManager {
public:
	static GameManager& getInstance();
	void gameUpdate();
	bool checkWalkable(std::string identifier, int x, int y, RECT c_box);
	void updateEntityPositions();

	void goMainMenu();
	void addEntity(std::string entname, Entity* ent);
	void deleteEntity(std::string entname);
	Entity* getEntity(std::string entname);

	void setRoom(int roomid,int stat=GAME_STATE_COMMON);
	
	Coord getSize();
	Coord getBias();

	void reactCheck();

	void runWaiting();
	void addWaiting(std::function<void()> func,int delay=0);

	std::vector<std::pair<std::function<void()>,int> > waitingList;
	std::unordered_map<std::string, int> globalVar,savingVar;
	std::unordered_map<std::string, Entity*> entities;

	std::vector<std::string> inventory;

	void addItem(std::string name);
	void eraseItem(std::string name);

	void addHP(int v);

	void gameSaving();

	bool readSaving();

	void gameOver();

	void newGame();
	void helpRoom();
	void gameEscape();

private:
	Room* curRoom;
	GameManager();
};