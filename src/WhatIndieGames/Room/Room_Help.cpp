#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Help::Room_Help() :Room(ROOM_HELP, NULL, 37 * TILE_GAME_SIZE, 21*TILE_GAME_SIZE) {
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
    cv.addObject("Tip3", DrawableObject(Text(L"按 Z 与人物、场景交互",RGB(255,255,255),RGB(133,163,216)), 940, 420, { 0,0,800,40 }, 1, DRAW_VISIBLE));
    cv.addObject("Tip4", DrawableObject(Text(L"存档点可以保存存档",RGB(255,255,255),RGB(133,163,216)), 940, 670, { 0,0,800,40 }, 1, DRAW_VISIBLE));

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
    int* battled=&localVar["Battled"];
    *battled = 0;
    auto* localv = &localVar;
    npcmanF->setReaction([=]() {
        if (GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING] == 1)return;
        if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] == GAME_STATE_BATTLE)return;
        if (GameManager::getInstance().globalVar[GLOBAL_PLAYER_HP] <= 50) {
            if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;
            Animation sansface = Animation(ResourceManager::getInstance().getResource("SANS_FACE"), 1, 1, 1, 32, 30);
            ConversationSequence::getInstance().setSequence(ConvSeq({
                [=]() {
                    AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                    Conversation::getInstance().beginConversation(Text(L"* 你的HP太低了。"),sansface); },
                [=]() {
                    AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                    Conversation::getInstance().beginConversation(Text(L"* 我都不敢相信你这么菜。"),
                        Animation(ResourceManager::getInstance().getResource("SANS_CLOSEEYE"), 1, 1, 1, 32, 30)); } }
            ));
            ConversationSequence::getInstance().startConversation();
            return;
        }
        if (*battled == 0)*battled = 1;
        AudioManager::getInstance().playSound("SND_ENEMYALARM");
        GameManager::getInstance().getEntity(ENTITY_MAIN_PLAYER)->setSpeedX(0);
        GameManager::getInstance().getEntity(ENTITY_MAIN_PLAYER)->setSpeedY(0);
        GameManager::getInstance().updateEntityPositions();
        GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING] = 1;
        
        GameManager::getInstance().addWaiting([=]() {

            GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING] = 0;

            if (localv->find("HARDCORE") == localv->end()) {

                BattleController::getInstance().setProcess([=]()
                    {
                        AudioManager::getInstance().stopBgm();
                        AudioManager::getInstance().playSound("BGM_BATTLE", true);
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

                            bt.text = Text(L"* 真是一场紧张刺激的战斗呢。");
                            ev.subscribe("BATTLE_DIALOG_START", "BattleDialogCheck", [&]() {
                                bt.setConv(ConvSeq{
                                    [&]() {
                                        if (turn == 1) Conversation::getInstance().beginConversation(Text(L"* 等弹幕落底时，分别按下左、上、右来点击。"));
                                        if (turn == 2) Conversation::getInstance().beginConversation(Text(L"* 遇到长条的橙色弹幕需要一直按住。"));
                                        if (turn == 3) Conversation::getInstance().beginConversation(Text(L"* 绿色的弹幕会有特殊行为。"));
                                        if (turn == 4) Conversation::getInstance().beginConversation(Text(L"* 红色的弹幕往往会有更高的伤害。"));
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
                            AudioManager::getInstance().stopBgm();
                            ConversationSequence::getInstance().setSequence(ConvSeq{
                                []() {Conversation::getInstance().beginConversation(Text(L"* 你胜利了!")); },
                                []() {ConversationSequence::getInstance().stopBattleConv(); BattleController::getInstance().endBattle();  } });
                            ConversationSequence::getInstance().startBattleConv();
                            });
                        ev.subscribe("BATTLE_END", "BattleEndListen", [&]() {
                            AudioManager::getInstance().stopBgm();
                            AudioManager::getInstance().playSound("BGM_SANS", true);
                            ev.unsubscribe("BATTLE_DIALOG_START", "BattleDialogCheck");
                            ev.unsubscribe("BATTLE_NEW_TURN", "BattleTurnHandler");
                            ev.unsubscribe("BATTLE_END_MERCY", "BattleMercyListen");
                            ev.unsubscribe("BATTLE_END", "BattleEndListen");
                            });

                        bt.showScene();
                        ev.emit("BATTLE_NEW_TURN");
                    });
            }
            else {
                BattleController::getInstance().setProcess([=]() 
                    {
                    AudioManager::getInstance().stopBgm();
                    AudioManager::getInstance().playSound("BGM_MEGALOVANIA", true);
                    auto& bt = Battle::getInstance();
                    auto& ev = EventManager::getInstance();


                    bt.press_height = 12;
                    bt.nbtime = 25;
                    bt.nbtime = 0;
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
                        return turn >= 6;
                        };

                    typedef Battle::Attack::Bullet Bul;
                    ev.subscribe("BATTLE_NEW_TURN", "BattleTurnHandler", [&]() {
                        bt.switchState(BATTLE_ACTING);

                        auto it = bt.localVar.find("TURN");
                        if (it == bt.localVar.end())bt.localVar["TURN"] = 0;
                        int& turn = bt.localVar["TURN"];
                        turn++;

                        bt.text = Text(L"* 真是一场紧张刺激的战斗呢。");
                        ev.subscribe("BATTLE_DIALOG_START", "BattleDialogCheck", [&]() {
                            bt.setConv(ConvSeq{
                                [&]() {
                                    Conversation::getInstance().beginConversation(Text(L"* 这可是你自己选的。"));
                                },
                                []() {ConversationSequence::getInstance().stopBattleConv();
                                Battle::getInstance().switchState(BATTLE_BULLET);
                                Battle::getInstance().runAttack();
                                }
                                });
                            bt.runConv();
                            });

                        Battle::Attack atk[20] = {
                            Battle::Attack({
                                {10,Bul(1,10,0,1)},{14,Bul(2,10,0,1)},{18,Bul(3,10,0,1)},
                                {22,Bul(4,10,1,1)},{26,Bul(5,10,1,1)},{30,Bul(6,10,1,1)},
                                {34,Bul(7,10,2,1)},{38,Bul(8,10,2,1)},{42,Bul(9,10,2,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)},{10,Bul(2,10,1,1)},{18,Bul(3,10,0,1)},{18,Bul(4,10,1,1)},{26,Bul(5,10,1,1)},{26,Bul(6,10,2,1)},
                                {34,Bul(7,10,1,1)},{34,Bul(8,10,2,1)},{42,Bul(9,10,0,1)},{42,Bul(10,10,2,1)}, { 50,Bul(11,10,0,1) },{50,Bul(12,10,2,1)},
                                {58,Bul(13,10,0,1)},{58,Bul(14,10,1,1)},{66,Bul(15,10,1,1)},{66,Bul(16,10,2,1)},
                                {80,Bul(17,10,1,1,320)},{100,Bul(18,10,0,1)},{105,Bul(19,10,0,1)},{110,Bul(20,10,0,1)},
                                {125,Bul(21,10,1,1,320)},{145,Bul(22,10,2,1)},{150,Bul(23,10,2,1)},{155,Bul(24,10,2,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,5,0,1)}, { 20,Bul(2,5,1,1) },{ 30,Bul(3,5,2,1) },{ 40,Bul(4,10,0,1) },{ 50,Bul(5,10,1,1) },{ 60,Bul(6,10,2,1) },
                                {50,Bul(7,5,2,1)}, { 60,Bul(8,5,1,1) },{ 70,Bul(9,5,0,1) },{ 80,Bul(10,10,2,1) },{ 90,Bul(11,10,1,1) },{ 100,Bul(12,10,0,1) },
                                { 115,Bul(13,10,0,1,100) },{125,Bul(14,10,1,1)},{135,Bul(15,10,2,1)}, 
                                {135,Bul(16,10,1,1,100)},{145,Bul(17,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,1,1,1000)},{15,Bul(2,10,1,1,10,chgLine(2,100,110,1,0))},{23,Bul(3,10,1,1,10,chgLine(3,100,110,1,0))},
                                {24,Bul(4,10,1,1,10,chgLine(4,100,110,1,2))},{30,Bul(5,10,1,1,10,chgLine(5,200,210,1,2))},
                                {38,Bul(6,10,1,1,10,chgLine(6,200,210,1,0))},{45,Bul(7,10,1,1,10,chgLine(7,200,210,1,2))},
                                {51,Bul(8,10,1,1,10,chgLine(8,150,160,1,2))},{60,Bul(9,10,0,1,10)},{66,Bul(10,10,2,1,10)},
                                {74,Bul(11,10,2,1,10,chgLine(11,150,160,2,0))},{85,Bul(12,10,0,1,10,chgLine(12,170,180,0,2))},
                                {95,Bul(13,10,0,1,150)},{95,Bul(14,10,2,1,150)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,2,1,20,10,2)},
                                {10,Bul(2,10,0,1)},{14,Bul(3,10,1,1)},{18,Bul(4,10,2,1)},{22,Bul(5,10,0,1)},{26,Bul(6,10,1,1)},{30,Bul(7,10,2,1)},
                                {34,Bul(8,10,0,1)},{38,Bul(9,10,1,1,20)},{42,Bul(10,10,2,1)},{46,Bul(11,10,0,1,20)},{50,Bul(12,10,1,1)},{54,Bul(13,10,2,1)},
                                {58,Bul(14,10,0,1)},{62,Bul(15,10,1,1)},{66,Bul(16,10,2,1,20)},
                                {72,Bul(17,10,2,1,20)},{76,Bul(18,10,1,1,40)},{80,Bul(19,10,0,1,20)},{84,Bul(20,10,2,1,40)},{88,Bul(21,10,1,1,20)},{92,Bul(22,10,0,1,20)},
                                {96,Bul(23,10,2,1,20)},{100,Bul(24,10,1,1,20)},{104,Bul(25,10,0,1,40)},
                                {108,Bul(50,10,2,1)},
                                {110,Bul(26,10,0,1)},{112,Bul(27,10,2,1)},{114,Bul(28,10,0,1)},{116,Bul(29,10,2,1)},{118,Bul(30,10,0,1)},{120,Bul(31,10,2,1)},
                                {122,Bul(32,10,0,1)},{124,Bul(33,10,2,1)},{126,Bul(34,10,0,1)},{128,Bul(35,10,2,1)},{130,Bul(36,10,0,1)},{132,Bul(37,10,2,1)},
                                {134,Bul(38,10,0,1)},{136,Bul(39,10,2,1)},{138,Bul(40,10,0,1)},{140,Bul(41,10,2,1)},{142,Bul(42,10,0,1)},{144,Bul(43,10,2,1)},
                                {146,Bul(44,10,0,1)},{148,Bul(45,10,2,1)},{150,Bul(46,10,0,1)},{152,Bul(47,10,2,1)},{154,Bul(48,10,0,1)},{156,Bul(49,10,2,1)}
                                }),
                            
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,0,1)}
                                })

                        };


                        if (turn <= 5)bt.setAttack(atk[turn - 1]);
                        else bt.setAttack(Battle::Attack());
                        //bt.setAttack(atk[3]);
                        });
                        

                    ev.subscribe("BATTLE_END_MERCY", "BattleMercyListen", [=]() {
                        AudioManager::getInstance().stopBgm();
                        ConversationSequence::getInstance().setSequence(ConvSeq{
                            []() {Conversation::getInstance().beginConversation(Text(L"* 你胜利了!")); },
                            []() {ConversationSequence::getInstance().stopBattleConv(); BattleController::getInstance().endBattle();  } });
                        ConversationSequence::getInstance().startBattleConv();
                        });
                    ev.subscribe("BATTLE_END", "BattleEndListen", [&]() {
                        AudioManager::getInstance().stopBgm();
                        AudioManager::getInstance().playSound("BGM_SANS", true);
                        ev.unsubscribe("BATTLE_DIALOG_START", "BattleDialogCheck");
                        ev.unsubscribe("BATTLE_NEW_TURN", "BattleTurnHandler");
                        ev.unsubscribe("BATTLE_END_MERCY", "BattleMercyListen");
                        ev.unsubscribe("BATTLE_END", "BattleEndListen");
                        });

                    bt.showScene();
                    ev.emit("BATTLE_NEW_TURN");
                    });
            }
            BattleController::getInstance().startBattle(); }
        , 15);
        }, 0);
    npcmanF->setDirection(DIRECTION_LEFT);
    npcmanF->setVisible(true);
    addEntity("SANB", npcmanF);


    Entity* hardcore = new Entity("Hardcore", 450,570,{0,0,40,20},true);
    hardcore->setReaction(
        [&]() {
            if (localVar.find("HARDCORE") == localVar.end()) {
                ConversationSequence::getInstance().setSequence({
                    []() {Conversation::getInstance().beginConversation(Text(L"* (这里居然有个开关！)")); },
                    [&]() {
                        AudioManager::getInstance().playSound("SND_SPIKEOPEN");
                        Conversation::getInstance().beginConversation(Text(L"* (你按下了开关。)"));
                        localVar["HARDCORE"] = 1;
                    }
                    });
                ConversationSequence::getInstance().startConversation();
            }}
        , 0);
    addEntity(hardcore);


    Entity* toriel = new Entity("Toriel", 230, 730-2*52, { 0,52,25 * 2,52 * 2 }, { 0,0,25 * 2,52 * 2 },
        firstColumn(ResourceManager::getInstance().getResource("TORIEL_IMAGES"),25,52) ,
            groupBy4(ResourceManager::getInstance().getResource("TORIEL_IMAGES"),25,52));
    toriel->setReaction([=]() {
        if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;
        Animation torielface = Animation(ResourceManager::getInstance().getResource("TORIEL_FACE"), 1, 1, 1, 32, 32);
        ConversationSequence::getInstance().setSequence(ConvSeq({
            [=]() {
                AudioManager::getInstance().playSound("SND_TORIEL_SPEAK",false);
                Conversation::getInstance().beginConversation(Text(L"* 孩子，我想你一定会喜欢这个派！"), torielface); },
            [=]() {
                if (GameManager::getInstance().inventory.size() >= INVENTORY_SIZE) {
                    Conversation::getInstance().beginConversation(Text(L"* 但是你好像拿不下了。"), torielface);
                    AudioManager::getInstance().playSound("SND_TORIEL_SPEAK",false);
                }
                else {
                    Conversation::getInstance().beginConversation(Text(L"* 你获得了 派。"));
                    GameManager::getInstance().addItem("派");
                }
            } }
        ));
        ConversationSequence::getInstance().startConversation();
        }, 0);
    toriel->setVisible(true);
    addEntity("Toriel",toriel);

    Entity* npcman = new Entity("NPC", 300, 730-2*30, { 0,30,23 * 2,30 * 2 }, { 0, 0, 23 * 2,30 * 2 },
        animsF, {
        Animation(allanim4F.getFrame(0),4,1,4,23,30),
        Animation(allanim4F.getFrame(1),4,1,4,23,30),
        Animation(allanim4F.getFrame(2),4,1,4,23,30),
        Animation(allanim4F.getFrame(3),4,1,4,23,30),
        });
    npcman->setVisible(true);
    npcman->setReaction([=]() {
        if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;
        Animation sansface = Animation(ResourceManager::getInstance().getResource("SANS_FACE"), 1, 1, 1, 32, 30);
        if (*battled == 1) {
            *battled = 2;
            ConversationSequence::getInstance().setSequence(ConvSeq({
            [=]() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                Conversation::getInstance().beginConversation(Text(L"* 你说站在右边的那个家伙？"),sansface); },
            [=]() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                Conversation::getInstance().beginConversation(Text(L"* 你的妈妈没教过你瞬移吗？"),sansface); },
                }
            ));
            ConversationSequence::getInstance().startConversation();
            return;
        }
        ConversationSequence::getInstance().setSequence(ConvSeq({
            [=]() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                Conversation::getInstance().beginConversation(Text(L"* 就像这样，按Z进行对话。"),sansface); },
            [=]() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                Conversation::getInstance().beginConversation(Text(L"* 学会了吗？"),sansface); },
            [=]() {Conversation::getInstance().beginConversation(

                Conversation::Choice(ChoiceItem({
                    Text(L"学会了"),
                    Text(L"没学会")
                    }),[](int res) {GameManager::getInstance().globalVar["Choose_Temp"] = res + 1; })
            ); },
            [=]() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                if (GameManager::getInstance().globalVar["Choose_Temp"] == 1) {
                    Conversation::getInstance().beginConversation(Text(L"* 很好。"),sansface);
                }
                else if (GameManager::getInstance().globalVar["Choose_Temp"] == 2) {
                    ConversationSequence::getInstance().startConversation();
                }
            } }
        ));
        ConversationSequence::getInstance().startConversation();
        }, 0);
    npcman->setDirection(DIRECTION_DOWN);
    addEntity("npc", npcman);

    Entity* savepoint = new Entity("Savepoint", 940, 700, { 5,5,35,35 }, { 0,0,40,40 },
        Animation(ResourceManager::getInstance().getResource("SAVEPOINT"),2,1,2,20,20,5));
    savepoint->setVisible(true);
    savepoint->setReaction([]() {
        AudioManager::getInstance().playSound("SND_SAVING");
        GameManager::getInstance().addHP(1000);
        ConversationSequence::getInstance().setSequence({ 
            []() {Conversation::getInstance().beginConversation(Text(L"* 存档已保存（由于你在 帮助 中，其实并没有）。"));
            } });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity("Savepoint", savepoint);

    Entity* airwallTop = new Entity("AirwallTop", 0, MAIN_PLAYER_HEIGHT-30, { 0,0,width,10 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, height, { 0,0,width,10 }, false),
        * airwallRight = new Entity("AirwallRight", width, -10, { 0,0,10,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallRight", airwallRight);

    Entity* house = new Entity("House", 350,490, { 0,100,256,236 }, { 0,0, 256,236 },
        Animation(ResourceManager::getInstance().getResource("HOUSE"), 1, 1, 1, 128, 118));
    house->setVisible(true);
    house->setDrawYPrioBias(100);
    addEntity("House", house);
   

    //GameManager::getInstance().savingVar[GLOBAL_PLAYER_MAXHP] = 10;
    //GameManager::getInstance().globalVar[GLOBAL_PLAYER_HP] = GameManager::getInstance().savingVar[GLOBAL_PLAYER_MAXHP];

    


}
Room_Help::~Room_Help() {
    //MessageBoxA(0,"FUCKYOU","FUCK",0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_room_help");
    Canvas::getInstance().deleteObject("Tip1");
    Canvas::getInstance().deleteObject("Tip2");
    Canvas::getInstance().deleteObject("Tip3");
    Canvas::getInstance().deleteObject("Tip4");
    
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setSpeedX(0);
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setSpeedY(0);
    EventManager::getInstance().unsubscribe("BATTLE_DIALOG_START", "BattleDialogCheck");
    EventManager::getInstance().unsubscribe("BATTLE_NEW_TURN", "BattleTurnHandler");
    EventManager::getInstance().unsubscribe("BATTLE_END_MERCY", "BattleMercyListen");
    EventManager::getInstance().unsubscribe("BATTLE_END", "BattleEndListen");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}