#pragma once
#include"Room.h"
#include"../Game.h"
#include"../Manager/Managers.h"

#define ROOM_TEST 114514
#define ROOM_TEST_2 114515
#define ROOM_TEST_1 114516
#define ROOM_GAMEOVER 1919810

#define ROOM_MAINMENU 1
#define ROOM_HELP	2
#define ROOM_FIRST 3
#define ROOM_FALLDOWN 4
#define ROOM_RUINS_BATTLE 5
#define ROOM_RUINS_CANDY  6
#define ROOM_RUINS_PUZZLE 7
#define ROOM_RUINS_TORIEL 8
#define ROOM_RUINS_HOME 9
#define ROOM_RUINS_PUZZLE_2 10

#define ROOM_SNOW_TOWN 11
#define ROOM_SNOW_CROSSROADS 12
#define ROOM_SNOW_PLAIN 13
#define ROOM_SNOW_INN 21
#define ROOM_SNOW_HOUSE 22
#define ROOM_SNOW_SANSHOUSE 23
#define ROOM_SNOW_LIBRARY 24
#define ROOM_SNOW_SNOWMAN 25
#define ROOM_FIRE_CORRIDOR 14
#define ROOM_WATER_BATTLE 15
#define ROOM_WATER_BOSS 16
#define ROOM_LAB_TALK 17
#define ROOM_LAB_FIGHT 18
#define ROOM_PORTAL 19
#define ROOM_FINAL 20

#define ROOM_RUINS_SECRET 101
#define ROOM_SNOW_SECRET 102
#define ROOM_WATER_SECRET 103

#define CUTSCENE_FALLING 201



class Room_Test :public Room{
public:
	Room_Test();
	~Room_Test();
	virtual void roomInit();
};
class Room_Test_2 :public Room {
public:
	Room_Test_2();
	~Room_Test_2();
	virtual void roomInit();
};
class Room_Test_1 :public Room {
public:
	Room_Test_1();
	~Room_Test_1();
	virtual void roomInit();
};
class Room_Gameover : public Room {
public:
	Room_Gameover();
	~Room_Gameover();
	virtual void roomInit();
};
class Room_Mainmenu :public Room {
public:
	Room_Mainmenu();
	~Room_Mainmenu();
	virtual void roomInit();
	virtual void roomUpdate();
};
class Room_Help : public Room {
public:
	Room_Help();
	~Room_Help();
	virtual void roomInit();
};
class Room_Ruins_Puzzle :public Room {
public:
	Room_Ruins_Puzzle();
	~Room_Ruins_Puzzle();
	virtual void roomInit();
	virtual void roomUpdate();
};
class Room_Falldown :public Room {
public:
	Room_Falldown();
	~Room_Falldown();
	virtual void roomInit();
};
class Room_Ruins_Battle :public Room {
public:
	Room_Ruins_Battle();
	~Room_Ruins_Battle();
	virtual void roomInit();
};
class Room_Ruins_Candy :public Room {
public:
	Room_Ruins_Candy();
	~Room_Ruins_Candy();
	virtual void roomInit();
};
class Room_First : public Room {
public:
	Room_First();
	~Room_First();
	virtual void roomInit();
};
class Cutscene_Falling : public Room {
public:
	Cutscene_Falling();
	~Cutscene_Falling();
	virtual void roomInit();
	virtual void roomUpdate();
};

class Room_Ruins_Toriel :public Room {
public:
	Room_Ruins_Toriel();
	~Room_Ruins_Toriel();
	virtual void roomInit();
	virtual void roomUpdate();
};
class Room_Ruins_Home :public Room {
public:
	Room_Ruins_Home();
	~Room_Ruins_Home();
	virtual void roomInit();
};
class Room_Ruins_Puzzle_2 :public Room {
public:
	Room_Ruins_Puzzle_2();
	~Room_Ruins_Puzzle_2();
	virtual void roomInit();
	virtual void roomUpdate();
};
class Room_Ruins_Secret :public Room {
public:
	Room_Ruins_Secret();
	~Room_Ruins_Secret();
	virtual void roomInit();
};
class Room_Snow_Town :public Room {
public:
	Room_Snow_Town();
	~Room_Snow_Town();
	virtual void roomInit();
	virtual void roomUpdate();
};
class Room_Snow_House :public Room {
public:
	Room_Snow_House();
	~Room_Snow_House();
	virtual void roomInit();
};
class Room_Snow_Inn :public Room {
public:
	Room_Snow_Inn();
	~Room_Snow_Inn();
	virtual void roomInit();
};
class Room_Snow_Sanshouse : public Room {
public:
	Room_Snow_Sanshouse();
	~Room_Snow_Sanshouse();
	virtual void roomInit();
};

class Room_Snow_Library :public Room {
public:
	Room_Snow_Library();
	~Room_Snow_Library();
	virtual void roomInit();
};
class Room_Snow_Snowman :public Room {
public:
	Room_Snow_Snowman();
	~Room_Snow_Snowman();
	virtual void roomInit();
};



Room* getRoom(int roomid);