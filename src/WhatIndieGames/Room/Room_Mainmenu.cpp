#include"AllRooms.h"

Room_Mainmenu::Room_Mainmenu() :Room(ROOM_GAMEOVER, NULL, WINDOW_WIDTH, WINDOW_HEIGHT) {
    roomInit();
}
void Room_Mainmenu::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_MAINMENU"))AudioManager::getInstance().playSound("BGM_MAINMENU",true);
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);

}
Room_Mainmenu::~Room_Mainmenu() {
    clearEntities();
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}