#include"AllRooms.h"


Cutscene_Cast::Cutscene_Cast() :Room(CUTSCENE_CAST, NULL, WINDOW_WIDTH, WINDOW_HEIGHT) {
    roomInit();
}
void Cutscene_Cast::roomInit() {
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
    auto& gm = GameManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    auto& ev = EventManager::getInstance();

    AudioManager::getInstance().playSound("BGM_CAST");

    Entity* banner = new Entity("Banner", 200, 30, { 0,0,300,200 }, { 0,0,500,300 },
        Animation(ResourceManager::getInstance().getResource("MAINMENU_BANNER"), 1, 1, 1, 300, 200));
    addEntity("Banner", banner);

    localVar["ROLLING"] = 0;
    auto* roll = &localVar["ROLLING"];

    std::wstring cast = L"What Indie Games\n奇奇怪怪独立游戏\n\n作者: Mr_H2T\n\n素材来源:\n1. Undertale\n2. Deltarune\n3. Oneshot\n4. Hollow Knight\n5. OMORI\n\n\n\
OST:\n\nFrom Undertale (Toby Fox):\n\n1. Ruins\n2. Fallen Down\n\
3. Determination\n4. Home\n5. sans.\n6. Snowy\n7. Snowdin Town\n8. Spear of Justice\n9. Another Medium\n10. Megalovania\n\n\n\
From Deltarune (Toby Fox):\n\n1. Rude Buster\n2. Gallery\n3. THE HOLY\n4. Your Power\n5. Don't Forget\n6. Before the Story\n\n\n\
From Hollow Knight (Team Cherry): \n\n1. Reflection\n\n\nFrom OMORI (OMOCAT):\n\n1. OMORI\n2. OMORI - ALTER\n\n\n\n\n\nThanks for Playing!";

    cv.addObject("Cast", DrawableObject(Text(cast), 300, 700, { 0,0,400,3000 }, 2));

    GameManager::getInstance().addWaiting(
        [=]() {
            banner->setVisible(1);
        }
        ,20 );
    GameManager::getInstance().addWaiting(
        [=]() {
            banner->setVisible(0);
            *roll = 1;
            Canvas::getInstance().getObject("Cast").switchState(DRAW_VISIBLE, 1);
        }
    , 80);
    GameManager::getInstance().addWaiting(
        [=]() {
            GameManager::getInstance().goMainMenu();
        }
    , 1150);
}
Cutscene_Cast::~Cutscene_Cast() {
    clearEntities();
    AudioManager::getInstance().stopBgm();
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    cv.deleteObject("Cast");

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}
void Cutscene_Cast::roomUpdate() {
    static int TICK = 0;
    TICK++;
    if (localVar["ROLLING"] == 0)return;

    Canvas::getInstance().getObject("Cast").posY -= 2;
    
}