#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Lab_Talk::Room_Lab_Talk() :Room(ROOM_LAB_TALK, NULL, 19 * TILE_GAME_SIZE, 14 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Lab_Talk::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_HOT"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_HOT", true);
    calculateMap(ResourceManager::getInstance().getResource("LAB_TILESET"), 12, 6,
        { {-1,7,8,8,8,8,8,8,8,8,8,8,8,9},{-1,7,8,8,8,8,8,8,8,8,8,8,8,9},{-1,7,8,8,8,8,8,8,8,8,31,32,33,9},{-1,7,8,8,8,8,8,8,8,8,19,4,21,9},{-1,13,14,14,14,14,14,14,14,14,25,20,27,15},{-1,0,0,0,0,0,0,0,0,0,0,0,0,0},{-1,0,0,0,0,0,0,0,0,0,0,0,0,0},{-1,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0} });

    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    Canvas::getInstance().addObject("background_lab_talk",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 20,330 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_RIGHT);
        break;
    case 1:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 440,180 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    case ROOM_ENTRY_SAVING:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 440,310 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_RIGHT);
        break;
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);

    Entity* tools = new Entity("Tools", 280,120,{0,0,2*60,2*31},{0,0,2*60,2*31}, Animation(rs.getResource("ALPHYSTOOLS"), 1, 1, 1, 60, 31));
    tools->setPassable(1);
    tools->setVisible(1);
    tools->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 墙上摆着各种工具。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(tools);

    Entity* table = new Entity("Table", 50, 130, { 0,0,2*110,2*78 }, { 0,0,2*110,2*78 }, Animation(rs.getResource("ALPHYSTABLE"), 1, 1, 1, 110, 78));
    table->setPassable(0);
    table->setVisible(1);
    table->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 桌上堆满了草稿纸。(看起来乱糟糟的。)")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(table);

    Entity* portal = new Entity("Portal", 0, 320, { 0,0,5,80 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 1;
        GameManager::getInstance().setRoom(ROOM_HOT_ENTRANCE); }, 1);
    addEntity("Portal", portal);

    Entity* portal1 = new Entity("Portal1", 440, 160, { 0,0,80,5 }, true);
    portal1->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_LAB_FIGHT); }, 1);
    addEntity(portal1);

    Entity* alphys = new Entity("Alphys",135,220,{0,0,29*2,31*2},{0,0,29*2,31*2},
            firstColumn(ResourceManager::getInstance().getResource("ALPHYS_IMAGES"), 29, 31),
            groupBy4(ResourceManager::getInstance().getResource("ALPHYS_IMAGES"), 29, 31));
        
    alphys->setDirection(DIRECTION_UP);
    alphys->setVisible(1);
    alphys->setReaction(
        []() {
            ConversationSequence::getInstance().setSequence({
                []() {AudioManager::getInstance().playSound("SND_ALPHYS_SPEAK");
                Conversation::getInstance().beginConversation(Text(L"* 理论上来说你有很大的概率会失败。"),
                    Animation(ResourceManager::getInstance().getResource("ALPHYS_FACE"),1,1,1,52,43)); },
                []() {AudioManager::getInstance().playSound("SND_ALPHYS_SPEAK");
                Conversation::getInstance().beginConversation(Text(L"* 但据我所知你总有办法一次次尝试，对吗?"),
                    Animation(ResourceManager::getInstance().getResource("ALPHYS_FACE"),1,1,1,52,43)); }
                });
            ConversationSequence::getInstance().startConversation();
        }
        , 0);
    addEntity(alphys);

    if (GameManager::getInstance().savingVar.find("ALPHYS_TALKED") == GameManager::getInstance().savingVar.end()) {
        GameManager::getInstance().addWaiting([](){

            GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setSpeedX(0);
            GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setSpeedY(0);
            GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_CUTSCENE;
            }, 0);
        GameManager::getInstance().addWaiting([=]() {
            alphys->setSpeedY(5);
            }, 20);
        GameManager::getInstance().addWaiting([=]() {
            alphys->setSpeedX(-5);
            alphys->setSpeedY(0);
            }, 40);
        GameManager::getInstance().addWaiting([=]() {
            alphys->setSpeedX(0);
            alphys->setSpeedY(0);
            }, 50);
        GameManager::getInstance().addWaiting([=]() {
            ConversationSequence::getInstance().setSequence({
                []() {AudioManager::getInstance().playSound("SND_ALPHYS_SPEAK");
                Conversation::getInstance().beginConversation(Text(L"* 看来你就是误入这个世界的人了。"),
                    Animation(ResourceManager::getInstance().getResource("ALPHYS_FACE"),1,1,1,52,43)); },
                []() {AudioManager::getInstance().playSound("SND_ALPHYS_SPEAK");
                Conversation::getInstance().beginConversation(Text(L"* 我听说了你的事情。"),
                    Animation(ResourceManager::getInstance().getResource("ALPHYS_FACE"),1,1,1,52,43)); },
                []() {AudioManager::getInstance().playSound("SND_ALPHYS_SPEAK");
                Conversation::getInstance().beginConversation(Text(L"* 我已经找到了让你回去的方法。"),
                    Animation(ResourceManager::getInstance().getResource("ALPHYS_FACE"),1,1,1,52,43)); },
                []() {AudioManager::getInstance().playSound("SND_ALPHYS_SPEAK");
                Conversation::getInstance().beginConversation(Text(L"* 你的进入是因为系统漏洞的吞噬将你拉入了你的电脑之中。"),
                    Animation(ResourceManager::getInstance().getResource("ALPHYS_FACE"),1,1,1,52,43)); },
                []() {AudioManager::getInstance().playSound("SND_ALPHYS_SPEAK");
                Conversation::getInstance().beginConversation(Text(L"* 你将在前面的房间里与系统进行最后的战斗。"),
                    Animation(ResourceManager::getInstance().getResource("ALPHYS_FACE"),1,1,1,52,43)); },
                []() {AudioManager::getInstance().playSound("SND_ALPHYS_SPEAK");
                Conversation::getInstance().beginConversation(Text(L"* 只要你成功了，你就能够回到原来的世界。"),
                    Animation(ResourceManager::getInstance().getResource("ALPHYS_FACE"),1,1,1,52,43)); },
                 []() {AudioManager::getInstance().playSound("SND_ALPHYS_SPEAK");
            if (GameManager::getInstance().savingVar[GLOBAL_PLAYER_LV] == 0) {
                Conversation::getInstance().beginConversation(Text(L"* 你现在有点弱，我帮你提升一下。"),
                    Animation(ResourceManager::getInstance().getResource("ALPHYS_FACE"), 1, 1, 1, 52, 43));
                GameManager::getInstance().addEXP(10);
                    }
            else {
                Conversation::getInstance().beginConversation(Text(L"* 现在准备一下吧。"),
                    Animation(ResourceManager::getInstance().getResource("ALPHYS_FACE"),1,1,1,52,43));
                } },
                 [=]() {
                ConversationSequence::getInstance().stopConversation();

                GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_CUTSCENE;
                GameManager::getInstance().addWaiting([=]() {
                    alphys->setSpeedX(5);
                    alphys->setSpeedY(0);
                    }, 0);
                GameManager::getInstance().addWaiting([=]() {
                    alphys->setSpeedX(0);
                    alphys->setSpeedY(-5);
                    }, 10);
                GameManager::getInstance().addWaiting([=]() {
                    alphys->setSpeedX(0);
                    alphys->setSpeedY(0);
                    GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_COMMON;
                    GameManager::getInstance().savingVar["ALPHYS_TALKED"] = 1;
                    }, 30);
                 },
                });
            ConversationSequence::getInstance().startConversation();
            }, 53);
    }



    Entity* airwallTop = new Entity("AirwallTop", 40, 110, { 0,0,390,80 }, false),
        * airwallTop1 = new Entity("AirwallTop1", 490, 115, { 0,0,80,80 }, false),
        * airwallLeft = new Entity("AirwallLeft", 30, 0, { 0,0,10,320 }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, 400, { 0,0,560,10 }, false),
        * airwallRight = new Entity("AirwallRight", 570, 0, { 0,0,10,height }, false);
    addEntity(airwallTop);
    addEntity(airwallTop1);
    addEntity(airwallLeft);
    addEntity(airwallBottom);
    addEntity(airwallRight);

    Entity* savepoint = new Entity("Savepoint", 480, 320, { 5,5,35,35 }, { 0,0,40,40 },
        Animation(ResourceManager::getInstance().getResource("SAVEPOINT"), 2, 1, 2, 20, 20, 5));
    savepoint->setVisible(true);
    savepoint->setReaction([]() {
        //AudioManager::getInstance().playSound("SND_SAVING");
        GameManager::getInstance().addHP(1000);
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 想到自己即将面临最后之战，这使你充满了决心。"));
            },
            []() {Conversation::getInstance().beginConversation(Text(L"* 存档已保存！"));
                    GameManager::getInstance().gameSaving();
            } });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity("Savepoint", savepoint);
}
Room_Lab_Talk::~Room_Lab_Talk() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_lab_talk");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}