#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Ruins_Toriel::Room_Ruins_Toriel() :Room(ROOM_RUINS_TORIEL, NULL, WINDOW_WIDTH, WINDOW_HEIGHT) {
    roomInit();
}
void Room_Ruins_Toriel::roomInit() {
    auto& gm = GameManager::getInstance();
    if (!AudioManager::getInstance().isPlaying("BGM_RUINS"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_RUINS", true);
    calculateMap(ResourceManager::getInstance().getResource("RUINS_TILESET"), 19, 8,
        { {15,3,1,2,2,2,4,2,2,1,2,2,2,4,2,13},{15,3,1,2,2,2,4,44,45,1,2,2,2,4,2,13},{15,10,1,5,6,7,4,46,47,1,5,6,7,4,10,13},{15,16,1,21,22,23,4,54,55,1,21,22,23,4,16,13},{15,16,9,10,10,10,12,62,63,9,10,10,10,12,16,13},{15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,24,25,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,8,8,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,8,8,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,8,8,16,16,16,16,16,16,13},{23,16,16,16,16,16,35,8,8,34,16,16,16,16,16,21},{8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},{8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},{7,16,16,16,16,16,27,8,8,26,16,16,16,16,16,5},{15,16,16,16,16,16,16,8,8,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,8,8,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,8,8,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,8,8,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,8,8,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,8,8,16,16,16,16,16,16,13},{37,6,6,6,6,6,7,8,8,5,6,6,6,6,6,38} });

    Canvas::getInstance().addObject("background_ruins_toriel",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 50,530 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_RIGHT);
        break;
    case 1:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 560,530 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_LEFT);
        break;
    case 2:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 300,820 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    case 3:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({300,170});
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    case ROOM_ENTRY_SAVING:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 150,270 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);


    Entity* portal1 = new Entity("Portal1", 0, 500, { 0,0,5,100 }, true);
    portal1->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 1;
        GameManager::getInstance().setRoom(ROOM_RUINS_PUZZLE); }, 1);
    addEntity("Portal1", portal1);
    Entity* portal2 = new Entity("Portal2", 640, 500, { 0,0,5,100 }, true);
    portal2->setReaction([&]() {
        /*GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 1;
        GameManager::getInstance().setRoom(ROOM_SNOWTOWN);*/
        }, 1);
    addEntity("Portal2", portal2);
    Entity* portal3 = new Entity("Portal3", 270, 900, { 0,0,100,5 }, true);
    portal3->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_RUINS_PUZZLE_2); 
        }, 1);
    addEntity("Portal3", portal3);
    Entity* portal4 = new Entity("Portal4", 270, 150, { 0,0,100,5 }, true);
    portal4->setReaction([&]() {
         GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
         GameManager::getInstance().setRoom(ROOM_RUINS_HOME); 
        }, 1);
    addEntity("Portal4", portal4);




    Entity
        * airwallTop = new Entity("AirwallTop", 40, 110, { 0,0,40,10 }, false),
        * airwallTop1 = new Entity("AirwallTop1", 560, 110, { 0,0,40,10 }, false),
        * airwallTop2 = new Entity("AirwallTop2", 90, 110, { 0,0,180,80 }, false),
        * airwallTop3 = new Entity("AirwallTop3", 370, 110, { 0,0,180,80 }, false),
        * airwallLeft = new Entity("AirwallLeft", 30, 120, { 0,0,10,400 }, false),
        * airwallLeft1 = new Entity("AirwallLeft1", 30, 600, { 0,0,10,280 }, false),
        * airwallBottom = new Entity("AirwallBottom", 40, 880, { 0,0,230,40 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 370, 880, { 0,0,230,40 }, false),
        * airwallRight = new Entity("AirwallRight", 610, 120, { 0,0,400,400 }, false),
        * airwallRight1 = new Entity("AirwallRight1", 610, 600, { 0,0,400,280 }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallTop1", airwallTop1);
    addEntity("AirwallTop2", airwallTop2);
    addEntity("AirwallTop3", airwallTop3);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallLeft1", airwallLeft1);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallBottom1", airwallBottom1);
    addEntity("AirwallRight", airwallRight);
    addEntity("AirwallRight1", airwallRight1);
    
    Entity* savepoint = new Entity("Savepoint", 150, 240, { 5,5,35,35 }, { 0,0,40,40 },
        Animation(ResourceManager::getInstance().getResource("SAVEPOINT"), 2, 1, 2, 20, 20, 5));
    savepoint->setVisible(true);
    savepoint->setReaction([]() {
        //AudioManager::getInstance().playSound("SND_SAVING");
        GameManager::getInstance().addHP(1000);
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 这位可爱的老妇人和这座可爱的房子让你充满了决心。"));
            },
            []() {Conversation::getInstance().beginConversation(Text(L"* 存档已保存！"));
                    GameManager::getInstance().gameSaving();
            } });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity("Savepoint", savepoint);




    if (gm.savingVar.find("RUINS_TORIEL_TALKED") == gm.savingVar.end()) {
        Entity* toriel = new Entity("Toriel", 170, 410, { 0,52,25 * 2,52 * 2 }, { 0,0,25 * 2,52 * 2 },
            firstColumn(ResourceManager::getInstance().getResource("TORIEL_IMAGES"), 25, 52),
            groupBy4(ResourceManager::getInstance().getResource("TORIEL_IMAGES"), 25, 52));
        toriel->setVisible(true);
        addEntity("Toriel", toriel);
        
        gm.addWaiting([&]() {gm.globalVar[GLOBAL_GAME_STATE] = GAME_STATE_CUTSCENE; }, 1);
        gm.addWaiting([=]() {
            toriel->setSpeedY(10);
            }, 10);
        gm.addWaiting([=]() {
            toriel->setSpeedY(0), toriel->setSpeedX(-10);
            }, 17);
        gm.addWaiting([=]() {
            toriel->setSpeedY(0), toriel->setSpeedX(0);
            
            }, 24);
        gm.addWaiting([=]() {
            auto* C = &Conversation::getInstance();
            auto& CS = ConversationSequence::getInstance();
            Animation torielface = Animation(ResourceManager::getInstance().getResource("TORIEL_FACE"), 1, 1, 1, 32, 32);
            Animation niko_distressed = Animation(ResourceManager::getInstance().getResource("NIKO_DISTRESSED_FACE"), 1, 1, 1, 96, 96);
            Animation niko_sad = Animation(ResourceManager::getInstance().getResource("NIKO_SAD_FACE"), 1, 1, 1, 96, 96);
            Animation niko_cry = Animation(ResourceManager::getInstance().getResource("NIKO_CRY_FACE"), 1, 1, 1, 96, 96);
            AudioManager::getInstance().stopBgm();
            AudioManager::getInstance().playSound("BGM_TORIEL",true);
            CS.setSequence({
                [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* 你好，你是新来到这里的吗？"),torielface); },
                [=]() {C->beginConversation(Text(L"* 是的，我好像正在看我的电脑，然后我就到了这里。"),niko_distressed); },
                [=]() {C->beginConversation(Text(L"* 而且，我好像......"),niko_sad); },
                [=]() {C->beginConversation(Text(L"* 不知道怎么出去......"),niko_cry); },
                [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* 别担心，孩子。"),torielface); },
                [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* 前面就有一个镇子，还有我们的皇家科学家。"),torielface); },
                [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* 我相信你一定能够出去的。"),torielface); },
                [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* 而且，"),torielface); },
                [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* 如果你不急着离开的话，为什么不到我的家里坐坐呢？"),torielface); },
                [=]() {
                    ConversationSequence::getInstance().stopConversation();
                    GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_CUTSCENE;
                    GameManager::getInstance().addWaiting(
                        [=]() {
                            toriel->setSpeedX(10);
                        }
                    ,10);
                    GameManager::getInstance().addWaiting(
                        [=]() {
                            toriel->setSpeedX(0),toriel->setSpeedY(-10);
                        }
                    , 29);
                    GameManager::getInstance().addWaiting(
                        [=]() {
                            toriel->setSpeedX(0),toriel->setSpeedY(-10);
                            toriel->setPassable(1), toriel->setVisible(0);
                            GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_COMMON;
                            GameManager::getInstance().savingVar["RUINS_TORIEL_TALKED"] = 1;
                            if (!AudioManager::getInstance().isPlaying("BGM_RUINS"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_RUINS", true);
                        }
                    , 60);
                },
                });
            CS.startConversation();
            }, 32);
    }




}
Room_Ruins_Toriel::~Room_Ruins_Toriel() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_ruins_toriel");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}
void Room_Ruins_Toriel::roomUpdate() {

}