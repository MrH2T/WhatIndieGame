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

    cv.addObject("Tip1", DrawableObject(Text(L"���ϡ��¡��������ƶ�",RGB(255,255,255),RGB(133,163,216)), 170, 190, { 0,0,300,40 }, 1, DRAW_VISIBLE));
    cv.addObject("Tip2", DrawableObject(Text(L"�� C �򿪲˵���Z��X�ֱ��ʾȷ�Ϻͳ��أ���һ�еط�����ˣ�",RGB(255,255,255),RGB(133,163,216)), 500, 300, { 0,0,800,40 }, 1, DRAW_VISIBLE));
    cv.addObject("Tip3", DrawableObject(Text(L"�� Z �������������",RGB(255,255,255),RGB(133,163,216)), 940, 420, { 0,0,800,40 }, 1, DRAW_VISIBLE));
    cv.addObject("Tip4", DrawableObject(Text(L"�浵����Ա���浵",RGB(255,255,255),RGB(133,163,216)), 940, 670, { 0,0,800,40 }, 1, DRAW_VISIBLE));

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
    npcmanF->setReaction([=]() {
        if (GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING] == 1)return;
        if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] == GAME_STATE_BATTLE)return;
        if (GameManager::getInstance().globalVar[GLOBAL_PLAYER_HP] <= 50) {
            if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;
            Animation sansface = Animation(ResourceManager::getInstance().getResource("SANS_FACE"), 1, 1, 1, 32, 30);
            ConversationSequence::getInstance().setSequence(ConvSeq({
                [=]() {
                    AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                    Conversation::getInstance().beginConversation(Text(L"* ���HP̫���ˡ�"),sansface); },
                [=]() {
                    AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                    Conversation::getInstance().beginConversation(Text(L"* �Ҷ�������������ô�ˡ�"),
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
            BattleController::getInstance().setProcess([=]()
                {
                    AudioManager::getInstance().stopBgm();
                     AudioManager::getInstance().playSound("BGM_BATTLE", true);
                    auto& bt = Battle::getInstance();
                    auto& ev = EventManager::getInstance();


                    bt.press_height = 12;
                    bt.setEnemy("Sans", 1000, 1, { animsF[1],animsF[1],animsF[1] }, { 0,0,23 * 4,30 * 4 });
                    bt.actions = { std::make_pair("�鿴",[]() {
                        ConversationSequence::getInstance().setSequence(ConvSeq{
                            []() {
                                std::wstring txt = L"* Sans, HP 1, ATK 1, DEF 1, �����ĵ���.";
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

                        bt.text = Text(L"* ����һ�����Ŵ̼���ս���ء�");
                        ev.subscribe("BATTLE_DIALOG_START", "BattleDialogCheck", [&]() {
                            bt.setConv(ConvSeq{
                                [&]() {
                                    if(turn==1) Conversation::getInstance().beginConversation(Text(L"* �ȵ�Ļ���ʱ���ֱ������ϡ����������")); 
                                    if(turn==2) Conversation::getInstance().beginConversation(Text(L"* ���������ĳ�ɫ��Ļ��Ҫһֱ��ס��")); 
                                    if(turn==3) Conversation::getInstance().beginConversation(Text(L"* ��ɫ�ĵ�Ļ����������Ϊ��")); 
                                    if(turn==4) Conversation::getInstance().beginConversation(Text(L"* ��ɫ�ĵ�Ļ�������и��ߵ��˺���")); 
                                    if (turn >= 5)Conversation::getInstance().beginConversation(Text(L"* ���Ѿ�ѧ�������ս���ˡ�"));
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
                            []() {Conversation::getInstance().beginConversation(Text(L"* ��ʤ����!")); },
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


    Entity* toriel = new Entity("Toriel", 230, 730-2*52, { 0,52,25 * 2,52 * 2 }, { 0,0,25 * 2,52 * 2 },
        firstColumn(ResourceManager::getInstance().getResource("TORIEL_IMAGES"),25,52) ,
            groupBy4(ResourceManager::getInstance().getResource("TORIEL_IMAGES"),25,52));
    toriel->setReaction([=]() {
        if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;
        Animation torielface = Animation(ResourceManager::getInstance().getResource("TORIEL_FACE"), 1, 1, 1, 32, 32);
        ConversationSequence::getInstance().setSequence(ConvSeq({
            [=]() {
                AudioManager::getInstance().playSound("SND_TORIEL_SPEAK",false);
                Conversation::getInstance().beginConversation(Text(L"* ���ӣ�������һ����ϲ������ɣ�"), torielface); },
            [=]() {
                if (GameManager::getInstance().inventory.size() >= INVENTORY_SIZE) {
                    Conversation::getInstance().beginConversation(Text(L"* ����������ò����ˡ�"), torielface);
                    AudioManager::getInstance().playSound("SND_TORIEL_SPEAK",false);
                }
                else {
                    Conversation::getInstance().beginConversation(Text(L"* ������ �ɡ�"));
                    GameManager::getInstance().addItem("��");
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
                Conversation::getInstance().beginConversation(Text(L"* ��˵վ���ұߵ��Ǹ��һ"),sansface); },
            [=]() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                Conversation::getInstance().beginConversation(Text(L"* �������û�̹���˲����"),sansface); },
                }
            ));
            ConversationSequence::getInstance().startConversation();
            return;
        }
        ConversationSequence::getInstance().setSequence(ConvSeq({
            [=]() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                Conversation::getInstance().beginConversation(Text(L"* ������������Z���жԻ���"),sansface); },
            [=]() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                Conversation::getInstance().beginConversation(Text(L"* ѧ������"),sansface); },
            [=]() {Conversation::getInstance().beginConversation(

                Conversation::Choice(ChoiceItem({
                    Text(L"ѧ����"),
                    Text(L"ûѧ��")
                    }),[](int res) {GameManager::getInstance().globalVar["Choose_Temp"] = res + 1; })
            ); },
            [=]() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                if (GameManager::getInstance().globalVar["Choose_Temp"] == 1) {
                    Conversation::getInstance().beginConversation(Text(L"* �ܺá�"),sansface);
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
            []() {Conversation::getInstance().beginConversation(Text(L"* �浵�ѱ��棨�������� ���� �У���ʵ��û�У���"));
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