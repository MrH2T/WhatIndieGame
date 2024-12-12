#include"AllRooms.h"
Room* getRoom(int roomid) {
	switch (roomid) {
	case ROOM_TEST:
		return new Room_Test();
	case ROOM_TEST_2:
		return new Room_Test_2();
	case ROOM_TEST_1:
		return new Room_Test_1();
	case ROOM_GAMEOVER:
		return new Room_Gameover();
	case ROOM_MAINMENU:
		return new Room_Mainmenu();
	case ROOM_HELP:
		return new Room_Help();
	case ROOM_FALLDOWN:
		return new Room_Falldown();
	case ROOM_RUINS_PUZZLE:
		return new Room_Ruins_Puzzle();
	case ROOM_RUINS_BATTLE:
		return new Room_Ruins_Battle();
	case ROOM_RUINS_CANDY:
		return new Room_Ruins_Candy();
	}
	
	return NULL;
}

