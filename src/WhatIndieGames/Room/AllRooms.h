#pragma once
#include"Room.h"
#include"../Game.h"
#include"../Manager/Managers.h"

#define ROOM_TEST 114514
#define ROOM_TEST_2 114515
#define ROOM_TEST_1 114516
#define ROOM_GAMEOVER 1919810

#define ROOM_MAINMENU 1


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


Room* getRoom(int roomid);