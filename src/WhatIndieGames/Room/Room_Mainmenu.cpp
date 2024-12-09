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

    Entity* nikofalling = new Entity("NikoFalling", 10, 200, { 0,0,300,200 }, { 0,0,320,280 },
        Animation(ResourceManager::getInstance().getResource("MAINMENU_NIKO"), 2, 1, 2, 80, 72,37));
    nikofalling->setVisible(1);
    addEntity("NikoFalling", nikofalling);


    cv.addObject("Background1",
        DrawableObject(Animation(ResourceManager::getInstance().getResource("MAINMENU_BACKGROUND"), 1, 1, 1, 367, 482),
            0, 0, { 0,0,367,640 }, 0, DRAW_VISIBLE ));
    cv.addObject("Background2",
        DrawableObject(Animation(ResourceManager::getInstance().getResource("MAINMENU_BACKGROUND"), 1, 1, 1, 367, 482),
            0, 640, { 0,0,367,640 }, 0, DRAW_VISIBLE));

    cv.addObject("Purplelight0",
        DrawableObject(Animation(ResourceManager::getInstance().getResource("MAINMENU_PURPLELIGHTS"), 4, 1, 4, 20, 200, 10),
            50, 100, { 0,0,20,200 }, 9, DRAW_AUTOTICK | DRAW_VISIBLE | DRAW_ABSOLUTE));
    cv.addObject("Purplelight1",
        DrawableObject(Animation(ResourceManager::getInstance().getResource("MAINMENU_PURPLELIGHTS"), 4, 1, 4, 20, 200, 10),
            170, 50, { 0,0,20,200 }, 9, DRAW_AUTOTICK | DRAW_VISIBLE | DRAW_ABSOLUTE));
    cv.addObject("Purplelight2",
        DrawableObject(Animation(ResourceManager::getInstance().getResource("MAINMENU_PURPLELIGHTS"), 4, 1, 4, 20, 200, 10),
            140, 200, { 0,0,20,200 }, 9, DRAW_AUTOTICK | DRAW_VISIBLE | DRAW_ABSOLUTE));
    cv.addObject("Purplelight3",
        DrawableObject(Animation(ResourceManager::getInstance().getResource("MAINMENU_PURPLELIGHTS"), 4, 1, 4, 20, 200, 10),
            300, 100, { 0,0,20,200 }, 9, DRAW_AUTOTICK | DRAW_VISIBLE | DRAW_ABSOLUTE));
    cv.getObject("Purplelight0").anim.setCurFrame(0);
    cv.getObject("Purplelight1").anim.setCurFrame(10);
    cv.getObject("Purplelight2").anim.setCurFrame(20);
    cv.getObject("Purplelight3").anim.setCurFrame(30);

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
        if(localVar["choice"] > 0)localVar["choice"]--,AudioManager::getInstance().playSound("SND_CHOOSE");;
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
        });
    ev.subscribe("DOWN_PRESS", "MainMenuDown", [&]() {
        if (localVar["choice"] < 3 )localVar["choice"]++,AudioManager::getInstance().playSound("SND_CHOOSE");;
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
    AudioManager::getInstance().stopBgm("BGM_MAINMENU");
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    cv.deleteObject("Purplelight0");
    cv.deleteObject("Purplelight1");
    cv.deleteObject("Purplelight2");
    cv.deleteObject("Purplelight3");
    cv.deleteObject("Background1");
    cv.deleteObject("Background2");
    cv.deleteObject("MainmenuResume");
    cv.deleteObject("MainmenuRestart");
    cv.deleteObject("MainmenuHelp");
    cv.deleteObject("MainmenuExit");
    ev.unsubscribe("UP_PRESS", "MainMenuUp");
    ev.unsubscribe("DOWN_PRESS", "MainMenuDown");
    ev.unsubscribe("Z_PRESS", "MainMenuZ");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}
void Room_Mainmenu::roomUpdate() {
    auto& bg1 = Canvas::getInstance().getObject("Background1"),&bg2=Canvas::getInstance().getObject("Background2");
    bg1.posY -= 10;
    bg2.posY -= 10;
    if (bg1.posY == -640)bg1.posY = 640;
    if (bg2.posY == -640)bg2.posY = 640;
    static unsigned int count = 0;
    count++;
    if (count % 40 == 0) {
        int dx = rand() % 7 - 3, dy = rand() % 7 - 3;
        entities["NikoFalling"]->setPos({ 10+dx,200+dy },1);
    }
}