#include"AllRooms.h"


Cutscene_Falling::Cutscene_Falling() :Room(CUTSCENE_FALLING, NULL, WINDOW_WIDTH, WINDOW_HEIGHT) {
    roomInit();
}
void Cutscene_Falling::roomInit() {
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
    auto& gm = GameManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    auto& ev = EventManager::getInstance();

    Entity* nikofalling = new Entity("NikoFalling", 10, 200, { 0,0,300,200 }, { 0,0,320,280 },
        Animation(ResourceManager::getInstance().getResource("MAINMENU_NIKO"), 2, 1, 2, 80, 72, 37));
    nikofalling->setVisible(1);
    addEntity("NikoFalling", nikofalling);
    AudioManager::getInstance().playSound("SND_FALLING");
    localVar["distance"] = 420;

}
Cutscene_Falling::~Cutscene_Falling() {
    clearEntities();
    AudioManager::getInstance().stopBgm();
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}
void Cutscene_Falling::roomUpdate() {
    localVar["distance"] -= 6;
    if (localVar["distance"] == 0) {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_FALLDOWN,GAME_STATE_CUTSCENE);
    }
    else {
        int dis = localVar["distance"];
        auto ent = entities["NikoFalling"];
        ent->setPos({ 448 - dis / 3,500 - dis },1);
        ent->resizeDrawbox({ 0,0,2 * dis / 3, dis / 3 });
    }
}