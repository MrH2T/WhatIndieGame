#include"AllRooms.h"

Room_Gameover::Room_Gameover() :Room(ROOM_GAMEOVER, NULL, WINDOW_WIDTH,WINDOW_HEIGHT ) {
    roomInit();
}
void Room_Gameover::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_GAMEOVER"))AudioManager::getInstance().playSound("BGM_GAMEOVER",true);
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);

    Entity *banner = new Entity("GameoverBanner",(WINDOW_WIDTH-422)/2,100,{0,0,422,182}, { 0,0,422,182 },
            Animation(ResourceManager::getInstance().getResource("GAMEOVER_BANNER"),1,1,1,422,182));
    banner->setVisible(true);
    addEntity("GameoverBanner", banner);

    auto& cv = Canvas::getInstance();
    cv.addObject("GameoverResume",DrawableObject(Text(L"重新开始",RGB(255,255,0)), 200, 500, {0,0,200,30}, 9, DRAW_ABSOLUTE|DRAW_VISIBLE));
    cv.addObject("GameoverQuit", DrawableObject(Text(L"退出"),600,500,{0,0,200,30},9,DRAW_ABSOLUTE|DRAW_VISIBLE));
    auto& ev = EventManager::getInstance();
    
    localVar["choice"] = 0;
    ev.subscribe("LEFT_PRESS", "GameoverRoomLeft", [&]() {
        localVar["choice"] = 0;
        cv.getObject("GameoverResume").text.setTColor(RGB(255,255,0));
        cv.getObject("GameoverQuit").text.setTColor(RGB(255, 255, 255));
        AudioManager::getInstance().playSound("SND_CHOOSE");
        });
    ev.subscribe("RIGHT_PRESS", "GameoverRoomRight", [&]() {
        localVar["choice"] = 1;
        cv.getObject("GameoverResume").text.setTColor(RGB(255, 255, 255));
        cv.getObject("GameoverQuit").text.setTColor(RGB(255, 255, 0));
        AudioManager::getInstance().playSound("SND_CHOOSE");
        });
    ev.subscribe("Z_PRESS", "GameoverRoomZ", [&]() {
        if (localVar["choice"] == 0) {
            if (GameManager::getInstance().globalVar[ROOM_ENTRANCE] == 1)GameManager::getInstance().setRoom(ROOM_MAINMENU);
            if (!GameManager::getInstance().readSaving())
            {
                GameManager::getInstance().newGame();
            }
        }
        else if (localVar["choice"] == 1) {
            GameManager::getInstance().setRoom(ROOM_MAINMENU);
        }
        return;
        });
}
Room_Gameover::~Room_Gameover() {
    clearEntities();
    AudioManager::getInstance().stopBgm("BGM_GAMEOVER");
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    cv.deleteObject("background_room_gameover");
    cv.deleteObject("GameoverResume");
    cv.deleteObject("GameoverQuit");
    ev.unsubscribe("LEFT_PRESS", "GameoverRoomLeft");
    ev.unsubscribe("RIGHT_PRESS", "GameoverRoomRight");
    ev.unsubscribe("Z_PRESS", "GameoverRoomZ");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}