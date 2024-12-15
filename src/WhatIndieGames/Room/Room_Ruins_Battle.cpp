#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Ruins_Battle::Room_Ruins_Battle() :Room(ROOM_RUINS_BATTLE, NULL, WINDOW_WIDTH, WINDOW_HEIGHT) {
    roomInit();
}
void Room_Ruins_Battle::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_RUINS"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_RUINS", true);
    calculateMap(ResourceManager::getInstance().getResource("RUINS_TILESET"), 19, 8,
        { {29,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22},{15,2,2,2,20,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},{15,2,2,2,2,2,2,2,2,2,2,2,2,3,2,2,2,3,2,2,2,2,2,2,2,2,2},{15,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},{15,16,16,16,24,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},{15,16,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},{15,16,16,16,8,8,26,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},{15,80,81,81,72,73,81,81,81,81,81,81,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6},{15,83,84,84,73,73,84,84,84,84,84,84,13,14,14},{15,83,84,84,73,73,84,84,84,84,84,84,21,22,22},{15,83,84,84,73,73,84,84,84,84,84,84,1,2,2},{15,83,84,84,73,73,73,73,73,84,84,84,9,10,10},{15,83,84,84,81,81,81,81,73,73,73,73,16,16,16},{15,83,84,84,84,84,84,84,73,73,73,73,16,16,16},{15,83,84,84,84,73,73,73,73,81,81,5,6,6,6},{15,83,84,84,84,73,73,81,81,84,84,13},{15,83,84,84,84,73,73,84,84,84,84,13},{15,16,16,16,16,8,8,16,16,16,16,13},{15,16,16,16,16,8,8,16,16,16,16,13},{15,16,16,16,16,8,8,16,16,16,16,13},{15,16,16,16,16,8,8,16,16,16,16,13},{15,16,16,16,16,8,8,8,25,16,16,13},{15,16,16,16,16,32,8,8,8,16,16,13},{15,16,16,16,16,16,16,8,8,16,16,13},{15,16,16,16,16,16,16,8,8,16,16,13},{15,16,16,16,16,16,16,8,8,16,16,13},{15,16,16,16,16,16,16,8,8,16,16,13},{37,6,6,6,6,6,7,8,8,5,6,38},{14,14,14,14,14,14,15,8,8,13,14,14} });

    Canvas::getInstance().addObject("background_ruins_battle",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 300,1070 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    case 1:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 980,180 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_LEFT);
        break;
    case 2:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 520,480 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_LEFT);
        break;
    case ROOM_ENTRY_SAVING:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 150,970 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_LEFT);
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);


    Entity* portal1 = new Entity("Portal1", 1050, 180, { 0,0,10,120 }, true);
    portal1->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_RUINS_PUZZLE); }, 1);
    addEntity("Portal1", portal1);
    Entity* portal2 = new Entity("Portal2", 300, 1150, { 0,0,100,10 }, true);
    portal2->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 1;
        GameManager::getInstance().setRoom(ROOM_FALLDOWN); }, 1);
    addEntity("Portal2", portal2);
    Entity* portal3 = new Entity("Portal3", 590, 480, { 0,0,10,80 }, true);
    portal3->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_RUINS_CANDY); }, 1);
    addEntity("Portal3", portal3);


    Entity
        * airwallTop = new Entity("AirwallTop", 40, 155, { 0,0,width,5 }, false),
        * airwallTop1 = new Entity("AirwallTop1", 255, 280, { 0,0,width,140 }, false),
        * airwallTop2 = new Entity("AirwallTop2", 375, 425, { 0,0,width,40 }, false),
        * airwallLeft = new Entity("AirwallLeft", 30, 0, { 0,0,10,height }, false),
        * airwallLeft1 = new Entity("AirwallLeft1", 40, 280, { 0,0,110,200 }, false),
        * airwallLeft2 = new Entity("AirwallLeft2", 150, 490, { 0,0,155,60 }, false),
        * airwallLeft3 = new Entity("AirwallLeft3", 40, 560, { 0,0,145,100 }, false),
        * airwallBottom = new Entity("AirwallBottom", 40, 1080, { 0,0,230,80 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 375, 1080, { 0,0,40 * 4 - 10,80 }, false),
        * airwallRight = new Entity("AirwallRight", 445, 565, { 0,0,400,1000 }, false),
        * airwallRight1 = new Entity("AirwallRight1", 375, 560, { 0,0,100,100 }, false),
        * airwallRight2 = new Entity("AirwallRight2", 290, 610, { 0,0,400,50 }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallTop1", airwallTop1);
    addEntity("AirwallTop2", airwallTop2);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallLeft1", airwallLeft1);
    addEntity("AirwallLeft2", airwallLeft2);
    addEntity("AirwallLeft3", airwallLeft3);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallBottom1", airwallBottom1);
    //addEntity("AirwallBottom2", airwallBottom2);
    addEntity("AirwallRight", airwallRight);
    addEntity("AirwallRight1", airwallRight1);
    addEntity("AirwallRight2", airwallRight2);
    auto& gm = GameManager::getInstance();
    if (gm.savingVar.find("RUINS_BATTLE_1_FINISHED") == gm.savingVar.end()) {
        Entity* battle = new Entity("Battle", 600, 140, { 0,0,5,100 },true);
        battle->setReaction([&]() {
            if (gm.savingVar.find("RUINS_BATTLE_1_FINISHED") != gm.savingVar.end())return;
            if (GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING] == 1)return;
            if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] == GAME_STATE_BATTLE)return;


            AudioManager::getInstance().playSound("SND_ENEMYALARM");
            GameManager::getInstance().getEntity(ENTITY_MAIN_PLAYER)->setSpeedX(0);
            GameManager::getInstance().getEntity(ENTITY_MAIN_PLAYER)->setSpeedY(0);
            GameManager::getInstance().updateEntityPositions();
            GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING] = 1;

            GameManager::getInstance().addWaiting([=]() {

                GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING] = 0;
                BattleController::getInstance().setProcess([=]()
                    {
                        AudioManager::getInstance().stopBgm();
                        AudioManager::getInstance().playSound("BGM_BATTLE", true);
                        auto& bt = Battle::getInstance();
                        auto& ev = EventManager::getInstance();

                        Animation frog = Animation(ResourceManager::getInstance().getResource("FROGGIT"),1,1,1,106,102);
                        bt.press_height = 12;
                        bt.nbtime = 25;
                        bt.setEnemy("Froggit", 10, 1, { frog,frog,frog}, { 0,0,106,102 });
                        bt.actions = { std::make_pair("查看",[]() {
                            ConversationSequence::getInstance().setSequence(ConvSeq{
                                []() {
                                    std::wstring txt = L"* Froggit, HP 10, ATK 1。它似乎不是很想战斗。";
                                    Conversation::getInstance().beginConversation(Text(txt)); },
                                []() {
                                    ConversationSequence::getInstance().stopBattleConv();
                                    Battle::getInstance().switchState(BATTLE_DIALOG);
                                }
                                });
                            ConversationSequence::getInstance().startBattleConv();
                        }) ,
                        std::make_pair("解释",[&]() {
                            ConversationSequence::getInstance().setSequence(ConvSeq{
                                []() {
                                    Conversation::getInstance().beginConversation(Text(L"* 嘿，这只是个误会！我不想和你战斗！"),
                                        Animation(ResourceManager::getInstance().getResource("NIKO_SPEAK_FACE"),1,1,1,96,96)); 
                                },
                                [&]() {
                                    bt.localVar["EXPLAIN"] = 1;
                                    ConversationSequence::getInstance().stopBattleConv();
                                    Battle::getInstance().switchState(BATTLE_DIALOG);
                                }
                                });
                            ConversationSequence::getInstance().startBattleConv();
                        }) };

                        bt.mercible = [&]() {
                            auto it = bt.localVar.find("EXPLAIN");
                            if (it == bt.localVar.end())return false;
                            return true;
                            };

                        typedef Battle::Attack::Bullet Bul;
                        ev.subscribe("BATTLE_NEW_TURN", "BattleTurnHandler", [&]() {
                            bt.switchState(BATTLE_ACTING);

                            auto it = bt.localVar.find("TURN");
                            if (it == bt.localVar.end())bt.localVar["TURN"] = 0;
                            int& turn = bt.localVar["TURN"];
                            turn++;

                            if (Battle::getInstance().mercible())bt.text = Text(L"* Froggit 不想战斗了。",RGB(255,255,0));
                            else bt.text = Text(L"* Froggit 突然出现。");
                            ev.subscribe("BATTLE_DIALOG_START", "BattleDialogCheck", [&]() {
                                bt.setConv(ConvSeq{
                                    [&]() {
                                        Conversation::getInstance().beginConversation(Text(L"* （呱。）"));
                                    },
                                    []() {ConversationSequence::getInstance().stopBattleConv();
                                    Battle::getInstance().switchState(BATTLE_BULLET);
                                    Battle::getInstance().runAttack();
                                    }
                                    });
                                bt.runConv();
                                });
                            Battle::Attack atks[3] = {
                                Battle::Attack({{10,Bul(1,10,0,1)},{20,Bul(2,10,1,1)},{30,Bul(3,10,2,1)},{40,Bul(4,10,1,1)},{50,Bul(5,10,0,1)},
                                    {70,Bul(6,10,1,1)},{75,Bul(7,10,1,1)},{80,Bul(8,10,1,1)}}),
                                Battle::Attack({{10,Bul(1,10,0,1)},{15,Bul(2,10,0,1)},{20,Bul(3,10,0,1)},{30,Bul(4,10,1,1,50)},{50,Bul(5,10,2,1)},
                                    {55,Bul(6,10,2,1)},{60,Bul(7,10,2,1)},{70,Bul(8,10,1,1,50)}}),
                                Battle::Attack({{10,Bul(1,10,0,1)},{15,Bul(2,10,1,1)},{20,Bul(3,10,0,1)},{25,Bul(4,10,1,1)},{30,Bul(5,10,0,1)},
                                    {35,Bul(6,10,1,1)},{40,Bul(7,10,2,1)},{45,Bul(8,10,1,1)},{50,Bul(9,10,2,1)},{55,Bul(10,10,1,1)},
                                    {60,Bul(11,10,2,1)},{65,Bul(12,10,1,1)}})};
                            int ch = rand() % 10;
                            if (ch <= 4) bt.setAttack(atks[0]);
                            else if (ch <= 7)bt.setAttack(atks[1]);
                            else bt.setAttack(atks[2]);

                            });


                        ev.subscribe("BATTLE_END_MERCY", "BattleMercyListen", [=]() {
                            AudioManager::getInstance().stopBgm();
                            ConversationSequence::getInstance().setSequence(ConvSeq{
                                []() {Conversation::getInstance().beginConversation(Text(L"* 你胜利了! 获得了10G。"));
                                        GameManager::getInstance().addGold(10);
                                        GameManager::getInstance().savingVar["RUINS_BATTLE_1_FINISHED"] = 1;
                                    },
                                []() {ConversationSequence::getInstance().stopBattleConv(); BattleController::getInstance().endBattle();  } });
                            ConversationSequence::getInstance().startBattleConv();
                            });
                        ev.subscribe("BATTLE_END_WIN", "BattleWinListen", [=]() {
                            AudioManager::getInstance().stopBgm();
                            ConversationSequence::getInstance().setSequence(ConvSeq{
                                []() {Conversation::getInstance().beginConversation(Text(L"* 你胜利了! 获得了10G，3EXP。"));
                                        GameManager::getInstance().addGold(10);
                                        GameManager::getInstance().addEXP(3);
                                        GameManager::getInstance().savingVar[GLOBAL_KILLS] += 1;
                                        GameManager::getInstance().savingVar["RUINS_BATTLE_1_FINISHED"] = 1;
                                    },
                                []() {ConversationSequence::getInstance().stopBattleConv(); BattleController::getInstance().endBattle();  } });
                            ConversationSequence::getInstance().startBattleConv();
                            });
                        ev.subscribe("BATTLE_END", "BattleEndListen", [&]() {
                            AudioManager::getInstance().stopBgm();
                            AudioManager::getInstance().playSound("BGM_RUINS", true);
                            ev.unsubscribe("BATTLE_DIALOG_START", "BattleDialogCheck");
                            ev.unsubscribe("BATTLE_NEW_TURN", "BattleTurnHandler");
                            ev.unsubscribe("BATTLE_END_MERCY", "BattleMercyListen");
                            ev.unsubscribe("BATTLE_END_WIN", "BattleWinListen");
                            ev.unsubscribe("BATTLE_END", "BattleEndListen");
                            });

                        bt.showScene();
                        ev.emit("BATTLE_NEW_TURN");
                    });

                BattleController::getInstance().startBattle(); }
            , 15);
            }
            , 1);
            addEntity("Battle", battle);
    }

    Entity* savepoint = new Entity("Savepoint", 90, 970, { 5,5,35,35 }, { 0,0,40,40 },
        Animation(ResourceManager::getInstance().getResource("SAVEPOINT"), 2, 1, 2, 20, 20, 5));
    savepoint->setVisible(true);
    savepoint->setReaction([]() {
        //AudioManager::getInstance().playSound("SND_SAVING");
        GameManager::getInstance().addHP(1000);
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 这神秘的紫色遗迹让你充满了决心。"));
            },
            []() {Conversation::getInstance().beginConversation(Text(L"* 存档已保存！"));
                    GameManager::getInstance().gameSaving();
            } });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity("Savepoint", savepoint);
}
Room_Ruins_Battle::~Room_Ruins_Battle() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_ruins_battle");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}