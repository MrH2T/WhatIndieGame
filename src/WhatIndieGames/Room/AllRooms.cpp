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
	case ROOM_FIRST:
		return new Room_First();
	case ROOM_FALLDOWN:
		return new Room_Falldown();
	case ROOM_RUINS_PUZZLE:
		return new Room_Ruins_Puzzle();
	case ROOM_RUINS_BATTLE:
		return new Room_Ruins_Battle();
	case ROOM_RUINS_CANDY:
		return new Room_Ruins_Candy();
	case ROOM_RUINS_TORIEL:
		return new Room_Ruins_Toriel();
	case ROOM_RUINS_HOME:
		return new Room_Ruins_Home();
	case ROOM_RUINS_PUZZLE_2:
		return new Room_Ruins_Puzzle_2();
	case ROOM_RUINS_SECRET:
		return new Room_Ruins_Secret();
	case ROOM_SNOW_TOWN:
		return new Room_Snow_Town();
	case ROOM_SNOW_SNOWMAN:
		return new Room_Snow_Snowman();
	case ROOM_SNOW_INN:
		return new Room_Snow_Inn();
	case ROOM_SNOW_HOUSE:
		return new Room_Snow_House();
	case ROOM_SNOW_SANSHOUSE:
		return new Room_Snow_Sanshouse();
	case ROOM_SNOW_LIBRARY:
		return new Room_Snow_Library();
	case ROOM_SNOW_CROSSROADS:
		return new Room_Snow_Crossroads();
	case ROOM_SNOW_BRIDGE:
		return new Room_Snow_Bridge();
	case ROOM_HOT_ENTRANCE:
		return new Room_Hot_Entrance();
	case ROOM_LAB_TALK:
		return new Room_Lab_Talk();
	case ROOM_LAB_FIGHT:
		return new Room_Lab_Fight();
	case ROOM_PORTAL:
		return new Room_Portal();
	case ROOM_FINAL:
		return new Room_Final();

	case CUTSCENE_FALLING:
		return new Cutscene_Falling();
	}
	
	return NULL;
}

