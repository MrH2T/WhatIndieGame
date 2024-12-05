#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Test::Room_Test():Room(ROOM_TEST,NULL,2*WINDOW_WIDTH,2*WINDOW_HEIGHT) {
    roomInit();
}
void Room_Test::roomInit() {
	//if(!AudioManager::getInstance().isPlaying("BGM_SANS"))AudioManager::getInstance().stopBgm(),AudioManager::getInstance().playSound("BGM_SANS", true);
    map = ResourceManager::getInstance().getResource("BACKGROUND");
    Canvas::getInstance().addObject("background_room_test",
        DrawableObject(
            Animation(map, 1, 1, 1, 240, 160),
            0, 0, RECT({ 0,0,width,height }), 0));
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);
    
    Animation allanimF = Animation(ResourceManager::getInstance().getResource("SANS_IMAGES"), 16, 4, 4, 23, 30);
    Animation allanim4F = Animation(ResourceManager::getInstance().getResource("SANS_IMAGES"), 4, 4, 1, 23 * 4, 30);
    std::vector<Animation> animsF({
        Animation(allanimF.getFrame(0),1,1,1,23,30),
        Animation(allanimF.getFrame(4),1,1,1,23,30),
        Animation(allanimF.getFrame(8),1,1,1,23,30),
        Animation(allanimF.getFrame(12),1,1,1,23,30),
        });
    Entity* npcmanF = new Entity("SANB", 200, 300, { 0,30,23 * 2,30 * 2 }, { 0, 0, 23 * 2,30 * 2 },
        animsF, {
        Animation(allanim4F.getFrame(0),4,1,4,23,30),
        Animation(allanim4F.getFrame(1),4,1,4,23,30),
        Animation(allanim4F.getFrame(2),4,1,4,23,30),
        Animation(allanim4F.getFrame(3),4,1,4,23,30),
        });
    npcmanF->setVisible(true);
    npcmanF->setReaction([=]() {
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
                    AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_BATTLE", true);
                    auto& bt = Battle::getInstance();
                    auto& ev = EventManager::getInstance();


                    bt.press_height = 12;
                    bt.setEnemy("Sans", 1000, 1, {animsF[1],animsF[1],animsF[1]},{0,0,23*4,30*4});
                    bt.actions = { std::make_pair("查看",[]() {
                        ConversationSequence::getInstance().setSequence(ConvSeq{
                            []() {
                                std::wstring txt = L"* Sans, HP 1, ATK 1, DEF 1, 最弱的敌人.";
                                Conversation::getInstance().beginConversation(Text(txt)); },
                            []() {
                        ConversationSequence::getInstance().stopBattleConv(); 
                        Battle::getInstance().switchState(BATTLE_DIALOG); 
                            }
                        
                            });
                        ConversationSequence::getInstance().startBattleConv();
                    }) };



                    bt.mercible = []() {return true; };

                    typedef Battle::Attack::Bullet Bul;
                    ev.subscribe("BATTLE_NEW_TURN", "BattleTurnHandler", [&]() {
                        bt.switchState(BATTLE_ACTING);
                        bt.text = "* 但谁也没有来";
                        auto it= bt.localVar.find("TURN");
                        if (it == bt.localVar.end())bt.localVar["TURN"] = 0;

                        int& turn = bt.localVar["TURN"];
                        turn++;
                        ev.subscribe("BATTLE_DIALOG_START", "BattleDialogCheck", [&]() {
                        bt.setConv(ConvSeq{
                            []() {Conversation::getInstance().beginConversation(Text(L"* Well done.")); },
                            []() {ConversationSequence::getInstance().stopBattleConv(); 
                            Battle::getInstance().switchState(BATTLE_BULLET);
                            Battle::getInstance().runAttack(); 
                            }
                            });
                        bt.runConv();
                        });
                        bt.setAttack(Battle::Attack({
                        {10,Bul(1,10,0,1)},{30,Bul(2,10,1,1)},{50,Bul(3,10,2,1)},{70,Bul(4,10,1,1,200)},
                            {100,Bul(5,10,0,1)},{100,Bul(6,10,2,1)},
                            {120,Bul(7,10,1,1,10,[]() {
                                auto me = Battle::getInstance().getCurAttack().getBullet(7);
                                if (me.id == 0)return false;
                                if (me.pos == 2)return false;
                                if (me.posY >= 200 && me.posY < 210 && me.pos == 1)
                                {
                                    Battle::getInstance().getCurAttack().moveBullet(7, 1, 2, me.posY-10);
                                    return true;
                                }

                                return false ; })}
                            ,{130,Bul(8,10,1,1,10,[]() {
                                auto me = Battle::getInstance().getCurAttack().getBullet(8);
                                if (me.id == 0)return false;
                                if (me.pos == 0)return false;
                                if (me.posY >= 200 && me.posY < 210 && me.pos == 1)
                                {
                                    Battle::getInstance().getCurAttack().moveBullet(8, 1, 0, me.posY - 10);
                                    return true;
                                }

                                return false; })}
                            ,{150,Bul(9,10,1,2,10,2)},{160,Bul(10,10,1,2,10,2)},{170,Bul(11,10,1,2,10,2)}
                            }));
                        });
                        
                    

                    ev.subscribe("BATTLE_END_MERCY", "BattleMercyListen", [=]() {
                        //AudioManager::getInstance().stopBgm();
                        ConversationSequence::getInstance().setSequence(ConvSeq{
                            []() {Conversation::getInstance().beginConversation(Text(L"* 你胜利了! 获得 10G.")); },
                            []() {ConversationSequence::getInstance().stopBattleConv(); BattleController::getInstance().endBattle();  } });
                        ConversationSequence::getInstance().startBattleConv();
                        });
                    ev.subscribe("BATTLE_END", "BattleEndListen", [&]() {
                        AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_SANS", true);
                        ev.unsubscribe("BATTLE_DIALOG_START", "BattleDialogCheck");
                        ev.unsubscribe("BATTLE_NEW_TURN", "BattleTurnHandler");
                        ev.unsubscribe("BATTLE_END_MERCY", "BattleMercyListen");
                        ev.unsubscribe("BATTLE_END", "BattleEndListen");
                        });

                    bt.showScene();
                    ev.emit("BATTLE_NEW_TURN");
                });

            BattleController::getInstance().startBattle(); }
            ,15);
        }, 0);
    npcmanF->setDirection(DIRECTION_DOWN);
    addEntity("SANB", npcmanF);


    Entity* airwallTop = new Entity("AirwallTop", 0, MAIN_PLAYER_HEIGHT, { 0,0,width,10 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, height, { 0,0,width,10 }, false),
        * airwallRight = new Entity("AirwallRight", width, -10, { 0,0,10,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallRight", airwallRight);

    Entity* portal = new Entity("Portal", 500, 200, { 0,0,100,100 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE]=0;
        GameManager::getInstance().setRoom(ROOM_TEST_1); }, 1);
    addEntity("Portal",portal);

    //GameManager::getInstance().savingVar[GLOBAL_PLAYER_MAXHP] = 10;
    //GameManager::getInstance().globalVar[GLOBAL_PLAYER_HP] = GameManager::getInstance().savingVar[GLOBAL_PLAYER_MAXHP];

    GameManager::getInstance().addItem("怪物糖果");

}
Room_Test::~Room_Test () {
    //MessageBoxA(0,"FUCKYOU","FUCK",0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_room_test");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setSpeedX(0);
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setSpeedY(0);
    EventManager::getInstance().unsubscribe("BATTLE_DIALOG_START", "BattleDialogCheck");
    EventManager::getInstance().unsubscribe("BATTLE_NEW_TURN", "BattleTurnHandler");
    EventManager::getInstance().unsubscribe("BATTLE_END_MERCY", "BattleMercyListen");
    EventManager::getInstance().unsubscribe("BATTLE_END", "BattleEndListen");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}