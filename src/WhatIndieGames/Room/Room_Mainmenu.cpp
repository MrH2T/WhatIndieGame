#include"AllRooms.h"


Room_Mainmenu::Room_Mainmenu() :Room(ROOM_MAINMENU, NULL, WINDOW_WIDTH, WINDOW_HEIGHT) {
    roomInit();
}
void Room_Mainmenu::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_MAINMENU"))AudioManager::getInstance().playSound("BGM_MAINMENU",true);
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
    auto& gm = GameManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    auto& ev = EventManager::getInstance();
    Entity* banner = new Entity("MainmenuBanner", 400, 30, { 0,0,300,200 }, { 0,0,500,300 },
        Animation(ResourceManager::getInstance().getResource("MAINMENU_BANNER"), 1, 1, 1, 300, 200));
    banner->setVisible(1);
    addEntity("MainMenuBanner",banner);

    localVar["choice"] = 0;
    cv.addObject("MainmenuResume", DrawableObject(Text(L"继续游戏", RGB(255, 255, 0),RGB(0,0,0),L"Simsun",40), 
        600, 400, {0,0,200,40}, 9, DRAW_ABSOLUTE | DRAW_VISIBLE));
    cv.addObject("MainmenuRestart", DrawableObject(Text(L"新的游戏", RGB(255, 255, 255), RGB(0, 0, 0), L"Simsun", 40), 
        600, 450, { 0,0,200,40 }, 9, DRAW_ABSOLUTE | DRAW_VISIBLE));
    cv.addObject("MainmenuHelp", DrawableObject(Text(L"帮助", RGB(255, 255, 255), RGB(0, 0, 0), L"Simsun", 40), 
        600, 500, { 0,0,200,40 }, 9, DRAW_ABSOLUTE | DRAW_VISIBLE));
    cv.addObject("MainmenuExit", DrawableObject(Text(L"退出", RGB(255, 255, 255), RGB(0, 0, 0), L"Simsun", 40), 
        600, 550, { 0,0,200,40 }, 9, DRAW_ABSOLUTE | DRAW_VISIBLE));
    ev.subscribe("UP_PRESS", "MainMenuUp", [&]() {
        if(localVar["choice"] > 0)localVar["choice"]--;
        cv.getObject("MainmenuResume").text.setTColor(RGB(255, 255, 255));
        cv.getObject("MainmenuRestart").text.setTColor(RGB(255, 255, 255));
        cv.getObject("MainmenuHelp").text.setTColor(RGB(255, 255, 255));
        cv.getObject("MainmenuExit").text.setTColor(RGB(255, 255, 255));
        switch (localVar["choice"]) {
        case 0:
            cv.getObject("MainmenuResume").text.setTColor(RGB(255, 255, 0));
            break;
        case 1:
            cv.getObject("MainmenuRestart").text.setTColor(RGB(255, 255, 0));
            break;
        case 2:
            cv.getObject("MainmenuHelp").text.setTColor(RGB(255, 255, 0));
            break;
        case 3:
            cv.getObject("MainmenuExit").text.setTColor(RGB(255, 255, 0));
            break;
        default:
            break;
        }
        AudioManager::getInstance().playSound("SND_CHOOSE");
        });
    ev.subscribe("DOWN_PRESS", "MainMenuDown", [&]() {
        if (localVar["choice"] < 3 )localVar["choice"]++;
        cv.getObject("MainmenuResume").text.setTColor(RGB(255, 255, 255));
        cv.getObject("MainmenuRestart").text.setTColor(RGB(255, 255, 255));
        cv.getObject("MainmenuHelp").text.setTColor(RGB(255, 255, 255));
        cv.getObject("MainmenuExit").text.setTColor(RGB(255, 255, 255));
        switch (localVar["choice"]) {
        case 0:
            cv.getObject("MainmenuResume").text.setTColor(RGB(255, 255, 0));
            break;
        case 1:
            cv.getObject("MainmenuRestart").text.setTColor(RGB(255, 255, 0));
            break;
        case 2:
            cv.getObject("MainmenuHelp").text.setTColor(RGB(255, 255, 0));
            break;
        case 3:
            cv.getObject("MainmenuExit").text.setTColor(RGB(255, 255, 0));
            break;
        default:
            break;
        }
        AudioManager::getInstance().playSound("SND_CHOOSE");
        });
    ev.subscribe("Z_PRESS", "MainMenuZ", [&]() {

        AudioManager::getInstance().playSound("SND_CHOOSE_BIG");
        switch (localVar["choice"]) {
        case 0:
            gm.readSaving();
            break;
        case 1:
            gm.newGame();
            break;
        case 2:
            gm.helpRoom();
            break;
        case 3:
            gm.gameEscape();
            break;
        }
        return;
        });

}
Room_Mainmenu::~Room_Mainmenu() {
    clearEntities();
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    cv.deleteObject("MainmenuResume");
    cv.deleteObject("MainmenuRestart");
    cv.deleteObject("MainmenuHelp");
    cv.deleteObject("MainmenuExit");
    ev.unsubscribe("UP_PRESS", "MainMenuUp");
    ev.unsubscribe("DOWN_PRESS", "MainMenuDown");
    ev.unsubscribe("Z_PRESS", "MainMenuZ");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}