#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Help::Room_Help() :Room(ROOM_TEST, NULL, 37 * TILE_GAME_SIZE, 21*TILE_GAME_SIZE) {
    roomInit();
}
void Room_Help::roomInit() {
    if(!AudioManager::getInstance().isPlaying("BGM_SANS"))AudioManager::getInstance().stopBgm(),AudioManager::getInstance().playSound("BGM_SANS", true);
    auto& gm = GameManager::getInstance();
    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    calculateMap(ResourceManager::getInstance().getResource("TEST_ROOM_TILESET"), 4, 5,
        { {0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0},{5,6,6,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},{10,11,11,11,9,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0},{10,11,11,11,14,16,16,16,16,16,16,16,16,16,16,16,16,13,11,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0},{15,16,16,16,17,0,0,0,0,0,5,6,6,6,6,6,6,8,11,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,3,0,0,0,0,0,0,0,10,11,11,11,11,11,11,11,11,12,0,0,0,0,3,0,0,0,0,0,5,6,6,6,6,6,7},{0,0,0,0,0,3,0,0,0,0,10,11,14,16,16,16,16,16,16,17,0,0,0,0,0,0,0,0,0,0,10,11,11,11,11,11,12},{0,0,0,2,0,0,0,0,0,0,10,11,9,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8,11,11,11,11,11,12},{0,0,0,0,0,0,0,0,0,0,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12},{0,0,0,2,0,0,0,0,0,0,15,16,16,16,16,16,16,16,16,16,16,13,11,14,16,16,16,16,16,16,13,11,11,11,11,11,12},{0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,10,11,12,0,0,0,0,0,0,10,11,11,11,11,11,12},{0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,12,0,3,0,0,0,0,15,16,16,16,16,16,17},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,12,0,0,0,0,1,3,0,0,0,0,0,0,0},{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,10,11,12,0,0,0,0,0,0,0,0,0,2,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,12,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,12,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,10,11,12,0,0,0,0,3,0,0,0,0,3,0,0,0},{0,0,0,0,0,5,6,6,6,6,8,11,11,9,6,6,6,6,6,6,6,8,11,12,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,17,0,0,0,0,0,0,0,0,0,0,0,0,0} });
    cv.addObject("background_room_help",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));

    gm.entities[ENTITY_MAIN_PLAYER]->setVisible(true);
    gm.entities[ENTITY_MAIN_PLAYER]->setPos({2*TILE_GAME_SIZE,2*TILE_GAME_SIZE+20});

    cv.addObject("Tip1", DrawableObject(Text(L"按上、下、左、右来移动",RGB(255,255,255),RGB(133,163,216)), 170, 190, { 0,0,300,40 }, 1, DRAW_VISIBLE));
    cv.addObject("Tip2", DrawableObject(Text(L"按 C 打开菜单，Z，X分别表示确认和撤回（在一切地方皆如此）",RGB(255,255,255),RGB(133,163,216)), 500, 300, { 0,0,800,40 }, 1, DRAW_VISIBLE));

    Animation allanimF = Animation(ResourceManager::getInstance().getResource("SANS_IMAGES"), 16, 4, 4, 23, 30);
    Animation allanim4F = Animation(ResourceManager::getInstance().getResource("SANS_IMAGES"), 4, 4, 1, 23 * 4, 30);
    std::vector<Animation> animsF({
        Animation(allanimF.getFrame(0),1,1,1,23,30),
        Animation(allanimF.getFrame(4),1,1,1,23,30),
        Animation(allanimF.getFrame(8),1,1,1,23,30),
        Animation(allanimF.getFrame(12),1,1,1,23,30),
        });
    Entity* npcmanF = new Entity("SANB", 34*TILE_GAME_SIZE, 9*TILE_GAME_SIZE-20, { 0,30,23 * 2,30 * 2 }, { 0, 0, 23 * 2,30 * 2 },
        animsF, {
        Animation(allanim4F.getFrame(0),4,1,4,23,30),
        Animation(allanim4F.getFrame(1),4,1,4,23,30),
        Animation(allanim4F.getFrame(2),4,1,4,23,30),
        Animation(allanim4F.getFrame(3),4,1,4,23,30),
        });
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
                    bt.setEnemy("Sans", 1000, 1, { animsF[1],animsF[1],animsF[1] }, { 0,0,23 * 4,30 * 4 });
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



                    bt.mercible = [&]() {
                        auto it = bt.localVar.find("TURN");
                        if (it == bt.localVar.end())return false;
                        int& turn = bt.localVar["TURN"];
                        return turn >= 5;
                        };

                    typedef Battle::Attack::Bullet Bul;
                    ev.subscribe("BATTLE_NEW_TURN", "BattleTurnHandler", [&]() {
                        bt.switchState(BATTLE_ACTING);

                        auto it = bt.localVar.find("TURN");
                        if (it == bt.localVar.end())bt.localVar["TURN"] = 0;
                        int& turn = bt.localVar["TURN"];
                        turn++;

                        bt.text = "* 真是一场紧张刺激的战斗呢。";
                        ev.subscribe("BATTLE_DIALOG_START", "BattleDialogCheck", [&]() {
                            bt.setConv(ConvSeq{
                                [&]() {
                                    if(turn==1) Conversation::getInstance().beginConversation(Text(L"* 等弹幕落底时，分别按下左、上、右来点击。")); 
                                    if(turn==2) Conversation::getInstance().beginConversation(Text(L"* 遇到长条的橙色弹幕需要一直按住。")); 
                                    if(turn==3) Conversation::getInstance().beginConversation(Text(L"* 绿色的弹幕会有特殊行为。")); 
                                    if(turn==4) Conversation::getInstance().beginConversation(Text(L"* 红色的弹幕往往会有更高的伤害。")); 
                                    if (turn >= 5)Conversation::getInstance().beginConversation(Text(L"* 你已经学会基本的战斗了。"));
                                },
                                []() {ConversationSequence::getInstance().stopBattleConv();
                                Battle::getInstance().switchState(BATTLE_BULLET);
                                Battle::getInstance().runAttack();
                                }
                                });
                            bt.runConv();
                            });
                        if (turn == 1) {
                            bt.setAttack(Battle::Attack({
                                {10,Bul(1,10,0,1)},{30,Bul(2,10,1,1)},{50,Bul(3,10,2,1)},{70,Bul(4,10,1,1)},{90,Bul(5,10,0,1)},
                                {110,Bul(6,10,0,1)},{110,Bul(7,10,1,1)},{110,Bul(8,10,2,1)}
                                }));
                        }
                        else if (turn == 2) {
                            bt.setAttack(Battle::Attack({
                                {10,Bul(1,10,0,1,100)},{30,Bul(2,10,1,1,100)},{50,Bul(3,10,2,1,100)},{80,Bul(4,10,1,1,700)},{80,Bul(5,10,0,1,100)},
                                {100,Bul(6,10,2,1,100)},{120,Bul(7,10,0,1,100)},{140,Bul(8,10,2,1,100)}
                                }));
                        }
                        else if (turn == 3) {
                            bt.setAttack(Battle::Attack({
                                {10,Bul(1,10,1,1,10,chgLine(1,200,210,1,0))},{30,Bul(2,10,1,1,10,chgLine(2,200,210,1,2))},
                                {50,Bul(3,10,0,1,10,chgLine(3,200,210,0,1))},{70,Bul(4,10,2,1,10,chgLine(4,200,210,2,1))},
                                {90,Bul(5,10,0,1,10,chgLine(5,200,210,0,2))},{110,Bul(6,10,2,1,10,chgLine(6,200,210,2,0))},
                                {130,Bul(7,10,0,1,10,chgLine(7,200,210,0,2))},{150,Bul(8,10,2,1,10,chgLine(8,200,210,2,0))}
                                }));
                        }
                        else if (turn == 4) {
                            bt.setAttack(Battle::Attack({
                        {10,Bul(1,10,0,1)},{30,Bul(2,10,1,1)},{50,Bul(3,10,2,1)},{70,Bul(4,10,1,1,200)},
                            {100,Bul(5,10,0,1)},{100,Bul(6,10,2,1)},
                            {120,Bul(7,10,1,1,10,[]() {
                                auto me = Battle::getInstance().getCurAttack().getBullet(7);
                                if (me.id == 0)return false;
                                if (me.pos == 2)return false;
                                if (me.posY >= 200 && me.posY < 210 && me.pos == 1)
                                {
                                    Battle::getInstance().getCurAttack().moveBullet(7, 1, 2, me.posY - 10);
                                    return true;
                                }

                                return false; })}
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
                            ,{150,Bul(9,10,1,5,10,2)},{160,Bul(10,10,1,5,10,2)},{170,Bul(11,10,1,5,10,2)}
                                }));
                        }
                        else bt.setAttack(Battle::Attack());
                        });
                        


                    ev.subscribe("BATTLE_END_MERCY", "BattleMercyListen", [=]() {
                        //AudioManager::getInstance().stopBgm();
                        ConversationSequence::getInstance().setSequence(ConvSeq{
                            []() {Conversation::getInstance().beginConversation(Text(L"* 你胜利了!")); },
                            []() {ConversationSequence::getInstance().stopBattleConv(); BattleController::getInstance().endBattle();  } });
                        ConversationSequence::getInstance().startBattleConv();
                        });
                    ev.subscribe("BATTLE_END", "BattleEndListen", [&]() {
                        AudioManager::getInstance().stopBgm();
                        AudioManager::getInstance().playSound("BGM_SANS",true);
                        ev.unsubscribe("BATTLE_DIALOG_START", "BattleDialogCheck");
                        ev.unsubscribe("BATTLE_NEW_TURN", "BattleTurnHandler");
                        ev.unsubscribe("BATTLE_END_MERCY", "BattleMercyListen");
                        ev.unsubscribe("BATTLE_END", "BattleEndListen");
                        });

                    bt.showScene();
                    ev.emit("BATTLE_NEW_TURN");
                });

            BattleController::getInstance().startBattle(); }
        , 15);
        }, 0);
    npcmanF->setDirection(DIRECTION_LEFT);
    npcmanF->setVisible(true);
    addEntity("SANB", npcmanF);


    Entity* airwallTop = new Entity("AirwallTop", 0, MAIN_PLAYER_HEIGHT-30, { 0,0,width,10 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, height, { 0,0,width,10 }, false),
        * airwallRight = new Entity("AirwallRight", width, -10, { 0,0,10,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallRight", airwallRight);


    //GameManager::getInstance().savingVar[GLOBAL_PLAYER_MAXHP] = 10;
    //GameManager::getInstance().globalVar[GLOBAL_PLAYER_HP] = GameManager::getInstance().savingVar[GLOBAL_PLAYER_MAXHP];

    


}
Room_Help::~Room_Help() {
    //MessageBoxA(0,"FUCKYOU","FUCK",0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_room_help");
    Canvas::getInstance().deleteObject("Tip1");
    Canvas::getInstance().deleteObject("Tip2");
    
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setSpeedX(0);
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setSpeedY(0);
    EventManager::getInstance().unsubscribe("BATTLE_DIALOG_START", "BattleDialogCheck");
    EventManager::getInstance().unsubscribe("BATTLE_NEW_TURN", "BattleTurnHandler");
    EventManager::getInstance().unsubscribe("BATTLE_END_MERCY", "BattleMercyListen");
    EventManager::getInstance().unsubscribe("BATTLE_END", "BattleEndListen");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}