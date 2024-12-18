#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Snow_Bridge::Room_Snow_Bridge() :Room(ROOM_SNOW_BRIDGE, NULL, 19 * TILE_GAME_SIZE, 14 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Snow_Bridge::roomInit() {
    AudioManager::getInstance().stopBgm();
    calculateMap(ResourceManager::getInstance().getResource("SNOW_TILESET"), 63, 9,
        { {-1,-1,-1,-1,105},
{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{-1,-1,-1,-1,105},{0,9,10,10,10,10,10,11,0},{0,18,19,19,19,19,19,20,0},{0,27,28,21,19,22,28,29,0} });

    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    Canvas::getInstance().addObject("background_snow_bridge",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 160,890 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_RIGHT);
        break;
    case 1:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 160,0 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    case ROOM_ENTRY_SAVING:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 130,860 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_LEFT);
        break;
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);


    if (GameManager::getInstance().savingVar.find("UNDYNE_BATTLED") == GameManager::getInstance().savingVar.end()) {
        Entity* battle = new Entity("Battle", 160, 400, { 0,0,40,5 }, true);
        battle->setReaction(
            []() {
                if (GameManager::getInstance().savingVar.find("UNDYNE_BATTLED") == GameManager::getInstance().savingVar.end()) {
                    ConversationSequence::getInstance().setSequence({
                        []() {Conversation::getInstance().beginConversation(Text(L"* 要过去得先经过我!!!")); },
                       []() {ConversationSequence::getInstance().stopConversation();
                    AudioManager::getInstance().playSound("SND_ENEMYALARM");
                    GameManager::getInstance().getEntity(ENTITY_MAIN_PLAYER)->setSpeedX(0);
                    GameManager::getInstance().getEntity(ENTITY_MAIN_PLAYER)->setSpeedY(0);
                    GameManager::getInstance().updateEntityPositions();
                    GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING] = 1;
                    GameManager::getInstance().globalVar[GLOBAL_PLAYER_ATK] = GameManager::getInstance().savingVar[GLOBAL_PLAYER_ATK];
                    GameManager::getInstance().globalVar[GLOBAL_PLAYER_DEF] = GameManager::getInstance().savingVar[GLOBAL_PLAYER_DEF];

                    GameManager::getInstance().addWaiting([=]() {

                        GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING] = 0;

                        
                            BattleController::getInstance().setProcess([=]()
                                {
                                    AudioManager::getInstance().stopBgm();
                                    AudioManager::getInstance().playSound("BGM_UNDYNE", true);
                                    auto& bt = Battle::getInstance();
                                    auto& ev = EventManager::getInstance();


                                    bt.press_height = 15;
                                    Animation undyne = Animation(ResourceManager::getInstance().getResource("UNDYNE"), 1, 1, 1, 20, 49);
                                    bt.setEnemy("Undyne", 32, 1, { undyne,undyne,undyne }, { 0,0,20 * 4,49 * 4 });
                                    bt.actions = { std::make_pair("查看",[]() {
                                        ConversationSequence::getInstance().setSequence(ConvSeq{
                                            []() {
                                                std::wstring txt = L"* Undyne, HP 32, 皇家卫队的队长。";
                                                Conversation::getInstance().beginConversation(Text(txt)); },
                                            []() {
                                        ConversationSequence::getInstance().stopBattleConv();
                                        Battle::getInstance().switchState(BATTLE_DIALOG);
                                            }
                                            });
                                        ConversationSequence::getInstance().startBattleConv();
                                    }),
                                        std::make_pair("防御",[]() {
                                        ConversationSequence::getInstance().setSequence(ConvSeq{
                                            []() {
                                                Conversation::getInstance().beginConversation(Text(L"* 本回合无敌时间加长。"));
                                                Battle::getInstance().nbtime = 25; 
                                            },
                                            []() {
                                        ConversationSequence::getInstance().stopBattleConv();
                                        Battle::getInstance().switchState(BATTLE_DIALOG);
                                            }
                                            });
                                        ConversationSequence::getInstance().startBattleConv();
                                    }),
                                        std::make_pair("说服",[]() {
                                        Battle::getInstance().localVar["PERSUADE_THIS"] = 1;
                                        if (Battle::getInstance().localVar.find("PERSUADE") == Battle::getInstance().localVar.end())
                                            Battle::getInstance().localVar["PERSUADE"] = 1;
                                        else  Battle::getInstance().localVar["PERSUADE"] += 1;

                                        ConversationSequence::getInstance().setSequence(ConvSeq{
                                            [=]() {
                                                Conversation::getInstance().beginConversation(Text(L"* 你尝试说服 Undyne 自己需要通过这里。"));
                                            },
                                            [=]() {
                                                if (Battle::getInstance().localVar["PERSUADE"] < 5) {
                                                    Conversation::getInstance().beginConversation(Text(L"* 似乎有一点用处，继续这么做。"));
                                                }
                                                else {
                                                    Conversation::getInstance().beginConversation(Text(L"* Undyne 已经被说服了。"));
                                                }
                                            },
                                            []() {
                                        ConversationSequence::getInstance().stopBattleConv();
                                        Battle::getInstance().switchState(BATTLE_DIALOG);
                                            }
                                            });
                                        ConversationSequence::getInstance().startBattleConv();
                                    })
                                    };



                                    bt.mercible = [&]() {
                                        auto it = bt.localVar.find("PERSUADE");
                                        if (it == bt.localVar.end())return false;
                                        int& per = (*it).second;
                                        return per >= 5;
                                        };

                                    ev.subscribe("BATTLE_NEW_TURN", "BattleTurnHandler", [&]() {
                                        bt.localVar["PERSUADE_THIS"] = 0;
                                        bt.nbtime = 10;
                                        if (bt.enemy_hp <= 10)bt.nbtime = 0;
                                        bt.switchState(BATTLE_ACTING);

                                        auto it = bt.localVar.find("TURN");
                                        if (it == bt.localVar.end())bt.localVar["TURN"] = 0;
                                        int& turn = bt.localVar["TURN"];
                                        turn++;

                                        std::wstring str[2] = {L"* Undyne 拦住了去路。",L"* 狂风呼啸。"};
                                        if (turn == 1)bt.text = Text(L"* Undyne 出击！");
                                        else bt.text = Text(str[rand() % 2]);
                                        ev.subscribe("BATTLE_DIALOG_START", "BattleDialogCheck", [&]() {
                                            bt.setConv(ConvSeq{
                                                [&]() {
                                                    std::wstring txt = L"";
                                                    if (bt.localVar["PERSUADE_THIS"] == 1) {
                                                        switch (bt.localVar["PERSUADE"]) {
                                                        case 1:txt = L"* 我不会允许你到我们的实验室!"; break;
                                                        case 2:txt = L"* 哪怕你是来自另一个世界的人也不可以!"; break;
                                                        case 3:txt = L"* 你说你被困在这里了?"; break;
                                                        case 4:txt = L"* 你是说你回不了家了吗?"; break;
                                                        case 5:txt = L"* 好吧，我相信你，你过去吧。"; break;
                                                        default:txt = L"* (没有必要继续战斗了。)"; break;
                                                            }

                                                    }
                                                    else {
                                                        txt = L"* 休想通过我这里!";
                                                    }
                                                    Conversation::getInstance().beginConversation(Text(txt));
                                                },
                                                [&]() {ConversationSequence::getInstance().stopBattleConv();

                                                    typedef Battle::Attack::Bullet Bul;
                                                    Battle::Attack atk[5] = {
                                                        Battle::Attack({
                                                            {10,Bul(1,10,0,1)},{16,Bul(2,10,0,1)},{22,Bul(3,10,0,1)},{29,Bul(4,10,0,1,10,chgLine(4,100,110,0,1))},
                                                            {34,Bul(5,10,1,1)},{40,Bul(6,10,1,1)},{46,Bul(7,10,1,1)},{53,Bul(8,10,1,1,10,chgLine(8,100,110,1,2))},
                                                            {58,Bul(9,10,2,1)},{64,Bul(10,10,2,1)},{70,Bul(11,10,2,1)},{76,Bul(12,10,2,1,10,chgLine(12,100,110,2,0))},
                                                            {82,Bul(13,10,1,1)},{88,Bul(14,10,1,1)},{94,Bul(15,10,1,1)}
                                                        }),
                                                        Battle::Attack({
                                                            {10,Bul(1,10,rand()%3,1)},{18,Bul(2,10,rand() % 3,1)},{26,Bul(3,10,rand() % 3,1)},
                                                            {34,Bul(4,10,rand() % 3,1)},{42,Bul(5,10,rand() % 3,1)},{50,Bul(6,10,rand() % 3,1)},
                                                            {58,Bul(7,10,rand() % 3,1)},{66,Bul(8,10,rand() % 3,1)},{74,Bul(9,10,rand() % 3,1)},
                                                            {82,Bul(10,10,rand() % 3,1)},{90,Bul(11,10,rand() % 3,1)},{98,Bul(12,10,rand() % 3,1)},
                                                            {106,Bul(13,10,rand() % 3,1)},{114,Bul(14,10,rand() % 3,1)},{122,Bul(15,10,rand() % 3,1)},
                                                            {130,Bul(16,10,rand() % 3,1)},{138,Bul(17,10,rand() % 3,1)},{146,Bul(18,10,rand() % 3,1)},
                                                            {154,Bul(19,10,rand() % 3,1)},{162,Bul(20,10,rand() % 3,1)}
                                                        }),
                                                        Battle::Attack({
                                                            {10,Bul(1,10,0,2,200)},{15,Bul(2,10,2,1)},{20,Bul(3,10,1,1)},{25,Bul(4,10,2,1)},
                                                            {30,Bul(5,10,1,2,200)},{35,Bul(6,10,0,1)},{40,Bul(7,10,2,1)},{45,Bul(8,10,0,1)},
                                                            {50,Bul(9,10,2,2,200)},{55,Bul(10,10,1,1)},{60,Bul(11,10,0,1)},{65,Bul(12,10,1,1)}
                                                        }),
                                                        Battle::Attack({
                                                            {10,Bul(1,10,0,1)},{20,Bul(2,10,0,2,200)},{50,Bul(3,10,0,1)},
                                                            {20,Bul(4,10,1,1)},{30,Bul(5,10,1,2,200)},{60,Bul(6,10,1,1)},
                                                            {30,Bul(7,10,2,1)},{40,Bul(8,10,2,2,200)},{70,Bul(9,10,2,1)}
                                                        }),
                                                        Battle::Attack({
                                                            {10,Bul(1,10,1,1,200)},{30,Bul(2,10,1,1,10,chgLine(2,150,160,1,0))},{31,Bul(3,10,1,1,10,chgLine(3,150,160,1,2))},
                                                            {20,Bul(22,10,1,1,10,chgLine(22,150,160,1,0))},{21,Bul(32,10,1,1,10,chgLine(32,150,160,1,2))},
                                                            {40,Bul(4,10,0,1,200)},{60,Bul(5,10,0,1,10,chgLine(5,150,160,0,1))},{60,Bul(6,10,0,1,10,chgLine(6,150,160,0,2))},
                                                            {50,Bul(52,10,0,1,10,chgLine(52,150,160,0,1))},{50,Bul(62,10,0,1,10,chgLine(62,150,160,0,2))},
                                                            {70,Bul(7,10,2,1,200)},{90,Bul(8,10,0,5,10,2)},{90,Bul(9,10,2,1,10,chgLine(9,150,160,2,1))},
                                                            {110,Bul(10,10,0,1)},{115,Bul(11,10,1,1)},{115,Bul(12,10,2,1)},{120,Bul(13,10,1,1)},{125,Bul(14,10,0,1)},
                                                            {125,Bul(15,10,2,1)},{130,Bul(16,10,2,1)},{135,Bul(17,10,0,1)},{135,Bul(18,10,1,1)}
                                                        }),

                                                    };

                                                    if (bt.localVar["PERSUADE_THIS"])
                                                    {
                                                        if (bt.localVar["PERSUADE"] < 5||bt.localVar["PERSUADE"]==5&&bt.localVar["PERSUADE_THIS"]==1) {
                                                            Battle::getInstance().setAttack(atk[bt.localVar["PERSUADE"] - 1]);
                                                        }
                                                        else Battle::getInstance().setAttack(Battle::Attack());
                                                    }
                                                   else {
                                                        if (bt.localVar["PERSUADE"] >= 5)Battle::getInstance().setAttack(Battle::Attack());
                                                        else 
                                                        Battle::getInstance().setAttack(atk[rand() % std::min(5,std::max(std::max(bt.localVar["PERSUADE"],
                                                            bt.localVar[ATTACK_USE]
                                                       ), 1))]);
                                                   }

                                                Battle::getInstance().switchState(BATTLE_BULLET);
                                                Battle::getInstance().runAttack();
                                                }
                                                });
                                            bt.runConv();
                                            });

                                        


                                        });

                                    ev.subscribe("BATTLE_END_WIN", "BattleWinListen", [=]() {
                                        AudioManager::getInstance().stopBgm();
                                        ConversationSequence::getInstance().setSequence(ConvSeq{
                                            []() {Conversation::getInstance().beginConversation(Text(L"* 你胜利了! 获得了 30G，15EXP。"));
                                            GameManager::getInstance().addGold(30);
                                            GameManager::getInstance().addEXP(15);
                                            GameManager::getInstance().savingVar[GLOBAL_KILLS] += 1;
                                            GameManager::getInstance().savingVar["UNDYNE_KILLED"] = 1;
                                            GameManager::getInstance().savingVar["UNDYNE_BATTLED"] = 1;
                                                },
                                            []() {ConversationSequence::getInstance().stopBattleConv(); BattleController::getInstance().endBattle();  } });
                                        ConversationSequence::getInstance().startBattleConv();
                                        });
                                    ev.subscribe("BATTLE_END_MERCY", "BattleMercyListen", [=]() {
                                        AudioManager::getInstance().stopBgm();
                                        ConversationSequence::getInstance().setSequence(ConvSeq{
                                            []() {Conversation::getInstance().beginConversation(Text(L"* 你胜利了! 获得 20G")); 
                                                    GameManager::getInstance().addGold(20);
                                            },
                                            []() {ConversationSequence::getInstance().stopBattleConv();
                                        GameManager::getInstance().savingVar["UNDYNE_BATTLED"] = 1;
                                        BattleController::getInstance().endBattle();  } });
                                        ConversationSequence::getInstance().startBattleConv();
                                        });
                                    ev.subscribe("BATTLE_END", "BattleEndListen", [&]() {
                                        AudioManager::getInstance().stopBgm();
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
                        });
                    ConversationSequence::getInstance().startConversation();
                }
            },1);
        addEntity(battle);
    }








    Entity* portal1 = new Entity("Portal1", 160, 950, { 0,0,70,5 }, true);
    portal1->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 1;
        GameManager::getInstance().setRoom(ROOM_SNOW_CROSSROADS); }, 1);
    addEntity(portal1);

    Entity* portal2 = new Entity("Portal2", 160, 0, { 0,0,70,5 }, true);
    portal2->setReaction([&]() {

        //hotland
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_HOT_ENTRANCE);
        }, 1);
    addEntity(portal2);

    Entity* airwallTop = new Entity("AirwallTop", 20, 0, { 0,0,130,830 }, false),
        * airwallTop1 = new Entity("AirwallTop1", 210, 0, { 0,0,130,830 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 830, { 0,0,5,220 }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, 950, { 0,0,150,5 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 210, 950, { 0,0,150,5 }, false),
        * airwallRight = new Entity("AirwallRight", 365, 830, { 0,0,5,220 }, false);
    addEntity(airwallTop);
    addEntity(airwallTop1);
    addEntity(airwallLeft);
    addEntity(airwallBottom);
    addEntity(airwallBottom1);
    addEntity(airwallRight);

    Entity* savepoint = new Entity("Savepoint", 80, 880, { 5,5,35,35 }, { 0,0,40,40 },
        Animation(ResourceManager::getInstance().getResource("SAVEPOINT"), 2, 1, 2, 20, 20, 5));
    savepoint->setVisible(true);
    savepoint->setReaction([]() {
        //AudioManager::getInstance().playSound("SND_SAVING");
        GameManager::getInstance().addHP(1000);
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 狂风呼啸，这座长长的木桥让你充满了决心。"));
            },
            []() {Conversation::getInstance().beginConversation(Text(L"* 存档已保存！"));
                    GameManager::getInstance().gameSaving();
            } });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity("Savepoint", savepoint);

}
Room_Snow_Bridge::~Room_Snow_Bridge() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_snow_bridge");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}