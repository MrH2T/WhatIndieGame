#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Lab_Fight::Room_Lab_Fight() :Room(ROOM_LAB_FIGHT, NULL, 19 * TILE_GAME_SIZE, 14 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Lab_Fight::roomInit() {
    AudioManager::getInstance().stopBgm();
    calculateMap(ResourceManager::getInstance().getResource("TRUELAB_TILESET"), 10, 7,
        { {7,8,30,30,9,8,8,30,12},{14,15,37,37,16,15,15,37,19},{21,22,44,44,23,22,23,22,26},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{-1,-1,-1,-1,1} });

    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    Canvas::getInstance().addObject("background_lab_fight",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 160,320 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);

    Entity* wall = new Entity("Wall", 160, 360, { 0,0,40,40 }, { 0,0,40,40 }, Animation(subBitmap(rs.getResource("TRUELAB_TILESET"), { 0,0,20,20 }), 1, 1, 1, 40, 40));
    wall->setPassable(1);
    addEntity(wall);

    Entity* glitch1 = new Entity("Glitch1", 50, 30, { 0,0,90,120 }, { 0,0,90,120 }, Animation(rs.getResource("GREEN_GLITCH"), 1, 1, 1, 192, 256), true);
    Entity* glitch2 = new Entity("Glitch2", 250, 70, { 0,0,90,120 }, { 0,0,90,120 }, Animation(rs.getResource("GREEN_GLITCH"), 1, 1, 1, 192, 256), true);
    Entity* glitch3 = new Entity("Glitch3", 150, 220, { 0,0,90,120 }, { 0,0,90,120 }, Animation(rs.getResource("GREEN_GLITCH"), 1, 1, 1, 192, 256), true);

    addEntity("Glitch1", glitch1);
    addEntity("Glitch2", glitch2);
    addEntity("Glitch3", glitch3);

    auto battle = [=]() {
       

        AudioManager::getInstance().playSound("SND_ENEMYALARM");
        GameManager::getInstance().getEntity(ENTITY_MAIN_PLAYER)->setSpeedX(0);
        GameManager::getInstance().getEntity(ENTITY_MAIN_PLAYER)->setSpeedY(0);
        GameManager::getInstance().updateEntityPositions();
        GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING] = 1;

        GameManager::getInstance().addWaiting([=]() {

            GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING] = 0;


            BattleController::getInstance().setProcess([=]()
                { 
                    glitch1->setVisible(0);
                    glitch2->setVisible(0);
                    glitch3->setVisible(0);
                    AudioManager::getInstance().stopBgm();
                    AudioManager::getInstance().playSound("BGM_FINALBOSS", true);
                    auto& bt = Battle::getInstance();
                    auto& ev = EventManager::getInstance();

                    Animation glitch = Animation(ResourceManager::getInstance().getResource("GREEN_GLITCH"), 2, 1, 2, 96, 256,8);
                    bt.press_height = 15;
                    bt.setEnemy("???", 180, 2, { glitch,glitch,glitch }, { 0,0,96,256 });
                    bt.actions = { std::make_pair("查看",[]() {
                        ConversationSequence::getInstance().setSequence(ConvSeq{
                            []() {
                                std::wstring txt = L"* ???, HP 180, DEF "+std::to_wstring(
                                Battle::getInstance().enemy_hp<80?4:2) + L", 最后的敌人。";
                                Conversation::getInstance().beginConversation(Text(txt)); },
                            []() {
                        ConversationSequence::getInstance().stopBattleConv();
                        Battle::getInstance().switchState(BATTLE_DIALOG);
                            }
                            });
                        ConversationSequence::getInstance().startBattleConv();
                    }),
                        std::make_pair("防御",[]() {
                            GameManager::getInstance().globalVar[GLOBAL_PLAYER_DEF] = 5;
                            Battle::getInstance().nbtime = 25;
                        ConversationSequence::getInstance().setSequence(ConvSeq{
                            []() {
                                Conversation::getInstance().beginConversation(Text(L"* 你防御了自己。"));
                            },
                            []() {
                                Conversation::getInstance().beginConversation(Text(L"* 本回合无敌时间加长，防御提高。"));
                            },
                            []() {
                        ConversationSequence::getInstance().stopBattleConv();
                        Battle::getInstance().switchState(BATTLE_DIALOG);
                            }
                            });
                        ConversationSequence::getInstance().startBattleConv();
                    }),
                        std::make_pair("强化",[]() {
                        Battle::getInstance().localVar["ADVANCE_NEXT"] = 1;

                        ConversationSequence::getInstance().setSequence(ConvSeq{
                            [=]() {
                                Conversation::getInstance().beginConversation(Text(L"* 你强化了自己。"));
                            },
                            [=]() {
                                Conversation::getInstance().beginConversation(Text(L"* 下一回合攻击力变为三倍。"));
                            },
                            []() {
                        ConversationSequence::getInstance().stopBattleConv();
                        Battle::getInstance().switchState(BATTLE_DIALOG);
                            }
                            });
                        ConversationSequence::getInstance().startBattleConv();
                    })
                    };

                    bt.localVar["LASTATK"] = -1;

                    bt.mercible = [&]() {
                        return false;
                        };

                    ev.subscribe("BATTLE_NEW_TURN", "BattleTurnHandler", [&]() {
                        bt.nbtime = (bt.enemy_hp<=30)?5:10;
                        bt.switchState(BATTLE_ACTING);

                        GameManager::getInstance().globalVar[GLOBAL_PLAYER_DEF] = GameManager::getInstance().savingVar[GLOBAL_PLAYER_DEF];

                        auto it = bt.localVar.find("TURN");
                        if (it == bt.localVar.end())bt.localVar["TURN"] = 0;
                        int& turn = bt.localVar["TURN"];
                        turn++;

                        if (bt.localVar["ADVANCE_NEXT"]==1) {
                            bt.localVar["ADVANCE_NEXT"] = 0;
                            GameManager::getInstance().globalVar[GLOBAL_PLAYER_ATK] =3*GameManager::getInstance().savingVar[GLOBAL_PLAYER_ATK];
                        }
                        else {
                            GameManager::getInstance().globalVar[GLOBAL_PLAYER_ATK] = GameManager::getInstance().savingVar[GLOBAL_PLAYER_ATK];
                        }

                        std::wstring txt= L"* 最后一战。";
                        if (bt.enemy_hp <= 80 && bt.localVar.find("LESS_80") == bt.localVar.end()) {
                            bt.localVar["LESS_80"] = 1;
                            bt.enemy_def = 4;
                            txt = L"* ??? 的防御提高了。";
                        }
                        if (bt.enemy_hp <= 30 && bt.localVar.find("LESS_30") == bt.localVar.end()) {
                            AudioManager::getInstance().stopBgm();
                            AudioManager::getInstance().playSound("BGM_FINALBOSS_2", true);
                            bt.localVar["LESS_30"] = 1;
                            txt = L"* ??? 的伤害提高了，你的无敌时间缩短了。";
                        }
                        bt.text = Text(txt);
                        ev.subscribe("BATTLE_DIALOG_START", "BattleDialogCheck", [&]() {
                            bt.setConv(ConvSeq{
                                [&]() {
                                    Conversation::getInstance().beginConversation(Text(L"* ......"));
                                },
                                [&]() {ConversationSequence::getInstance().stopBattleConv();

                                    typedef Battle::Attack::Bullet Bul;
                                    int dm = (bt.enemy_hp <= 30) ? 2 : 1;
                                    std::vector<std::pair<int,Bul> > bul3;
                                    bul3.clear();
                                    for (int i = 1; i <=20; i++) {
                                        int j = rand() % 3, k = rand() % 3;
                                        while (k == j)k = rand() % 3;
                                        bul3.push_back({ 10 + (i - 1) * 8,Bul(i,10,j,dm,10,chgLine(i,150,160,j,k)) });
                                    }


                                    Battle::Attack atk[9] = {
                                        Battle::Attack({
                                              {10,Bul(1,10,0,dm)},{18,Bul(2,10,1,dm)},{26,Bul(3,10,2,dm)},{34,Bul(4,10,1,dm)},
                                               {42,Bul(5,10,0,dm)},{50,Bul(6,10,1,dm)},{58,Bul(7,10,2,dm)},{66,Bul(8,10,1,dm)},
                                               {74,Bul(9,10,0,dm)},{82,Bul(10,10,1,dm)},{90,Bul(11,10,2,dm)},{98,Bul(12,10,1,dm)},
                                               {106,Bul(13,10,0,dm)},{114,Bul(14,10,1,dm)},{122,Bul(15,10,2,dm)},{130,Bul(16,10,1,dm)},
                                                 {138,Bul(17,10,0,dm)}
                                        }),
                                           Battle::Attack({
                                              {10,Bul(1,10,0,dm,320)},{26,Bul(2,10,2,dm)},{34,Bul(3,10,2,dm)},{42,Bul(4,10,2,dm)},
                                               {50,Bul(5,10,2,dm,320)},{66,Bul(6,10,0,dm)},{74,Bul(7,10,0,dm)},{82,Bul(8,10,0,dm)},
                                               {90,Bul(9,10,0,dm,400)},{106,Bul(10,10,2,dm,40)},{114,Bul(11,10,2,dm,40)},{122,Bul(12,10,2,dm,40)},
                                               {138,Bul(13,10,2,dm,400)},{154,Bul(14,10,0,dm,40)},{162,Bul(15,10,0,dm,40)},{170,Bul(16,10,0,dm,40)}
                                        }),Battle::Attack({
                                            {10 + 8 * (1 - 1),Bul(1,10,rand() % 3,dm)},{10 + 8 * (2 - 1),Bul(2,10,rand() % 3,dm)},{10 + 8 * (3 - 1),Bul(3,10,rand() % 3,dm)},
                                            {10 + 8 * (4 - 1),Bul(4,10,rand() % 3,dm)},{10 + 8 * (5 - 1),Bul(5,10,rand() % 3,dm)},{10 + 8 * (6 - 1),Bul(6,10,rand() % 3,dm)},
                                            {10 + 8 * (7 - 1),Bul(7,10,rand() % 3,dm)},{10 + 8 * (8 - 1),Bul(8,10,rand() % 3,dm)},{10 + 8 * (9 - 1),Bul(9,10,rand() % 3,dm)},
                                            {10 + 8 * (10 - 1),Bul(10,10,rand() % 3,dm)},{10 + 8 * (11 - 1),Bul(11,10,rand() % 3,dm)},{10 + 8 * (12 - 1),Bul(12,10,rand() % 3,dm)},
                                            {10 + 8 * (13 - 1),Bul(13,10,rand() % 3,dm)},{10 + 8 * (14 - 1),Bul(14,10,rand() % 3,dm)},{10 + 8 * (15 - 1),Bul(15,10,rand() % 3,dm)},
                                            {10 + 8 * (16 - 1),Bul(16,10,rand() % 3,dm)},{10 + 8 * (17 - 1),Bul(17,10,rand() % 3,dm)},{10 + 8 * (18 - 1),Bul(18,10,rand() % 3,dm)},
                                            {10 + 8 * (19 - 1),Bul(19,10,rand() % 3,dm)},{10 + 8 * (20 - 1),Bul(20,10,rand() % 3,dm)},{10 + 8 * (21 - 1),Bul(21,10,rand() % 3,dm)},
                                            {10 + 8 * (22 - 1),Bul(22,10,rand() % 3,dm)},{10 + 8 * (23 - 1),Bul(23,10,rand() % 3,dm)},{10 + 8 * (24 - 1),Bul(24,10,rand() % 3,dm)},
                                            {10 + 8 * (25 - 1),Bul(25,10,rand() % 3,dm)},{10 + 8 * (26 - 1),Bul(26,10,rand() % 3,dm)},{10 + 8 * (27 - 1),Bul(27,10,rand() % 3,dm)},
                                            {10 + 8 * (28 - 1),Bul(28,10,rand() % 3,dm)},{10 + 8 * (29 - 1),Bul(29,10,rand() % 3,dm)},{10 + 8 * (30 - 1),Bul(30,10,rand() % 3,dm)}
                                        }),bul3,
                                            Battle::Attack({
                                                {10,Bul(1,10,0,dm,560)},{10,Bul(2,10,1,dm)},{18,Bul(3,10,2,dm)},{26,Bul(4,10,1,dm)},{34,Bul(5,10,2,dm)},{42,Bul(6,10,1,dm)},
                                                {50,Bul(7,10,2,dm)},{58,Bul(8,10,1,dm)},{66,Bul(9,10,2,dm)},
                                                {82,Bul(10,10,2,dm,560)},{82,Bul(11,10,1,dm)},{90,Bul(12,10,0,dm)},{98,Bul(13,10,1,dm)},{106,Bul(14,10,0,dm)},{114,Bul(15,10,1,dm)},
                                                {122,Bul(16,10,0,dm)},{130,Bul(17,10,1,dm)},{138,Bul(18,10,0,dm)},
                                                {154,Bul(19,10,0,dm,560)},{154,Bul(20,10,0,dm,10,chgLine(20,150,160,0,rand() % 2 + 1))},
                                                {162,Bul(21,10,0,dm,10,chgLine(21,150,160,0,rand()%2+1))},{170,Bul(22,10,0,dm,10,chgLine(22,150,160,0,rand() % 2 + 1))},
                                                {178,Bul(23,10,0,dm,10,chgLine(23,150,160,0,rand()%2+1))},{186,Bul(24,10,0,dm,10,chgLine(24,150,160,0,rand() % 2 + 1))},
                                                {194,Bul(25,10,0,dm,10,chgLine(25,150,160,0,rand() % 2 + 1))},{202,Bul(26,10,0,dm,10,chgLine(26,150,160,0,rand() % 2 + 1))},
                                                {210,Bul(27,10,0,dm,10,chgLine(27,150,160,0,rand() % 2 + 1))},
                                                {154+72,Bul(28,10,2,dm,560)},{154 + 72,Bul(29,10,2,dm,10,chgLine(29,150,160,2,rand() % 2))},
                                                {162 + 72,Bul(30,10,2,dm,10,chgLine(30,150,160,2,rand() % 2))},{170 + 72,Bul(31,10,2,dm,10,chgLine(31,150,160,2,rand() % 2))},
                                                {178 + 72,Bul(32,10,2,dm,10,chgLine(32,150,160,2,rand() % 2))},{186 + 72,Bul(33,10,2,dm,10,chgLine(33,150,160,2,rand() % 2))},
                                                {194 + 72,Bul(34,10,2,dm,10,chgLine(34,150,160,2,rand() % 2))},{202 + 72,Bul(35,10,2,dm,10,chgLine(35,150,160,2,rand() % 2))},
                                                {210 + 72,Bul(36,10,2,dm,10,chgLine(36,150,160,2,rand() % 2))},
                                        }),
                                        //TODO
                                            Battle::Attack({
                                {10,Bul(1,10,0,dm)},{10,Bul(2,10,1,dm)},{18,Bul(3,10,0,dm)},{18,Bul(4,10,1,dm)},{26,Bul(5,10,1,dm)},{26,Bul(6,10,2,dm)},
                                {34,Bul(7,10,1,dm)},{34,Bul(8,10,2,dm)},{42,Bul(9,10,0,dm)},{42,Bul(10,10,2,dm)}, { 50,Bul(11,10,0,dm) },{50,Bul(12,10,2,dm)},
                                {58,Bul(13,10,0,dm)},{58,Bul(14,10,1,dm)},{66,Bul(15,10,1,dm)},{66,Bul(16,10,2,dm)},
                                {80,Bul(17,10,1,dm,320)},{100,Bul(18,10,0,dm)},{105,Bul(19,10,0,dm)},{110,Bul(20,10,0,dm)},
                                {125,Bul(21,10,1,dm,320)},{145,Bul(22,10,2,dm)},{150,Bul(23,10,2,dm)},{155,Bul(24,10,2,dm)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,5,0,dm)}, { 20,Bul(2,5,1,dm) },{ 30,Bul(3,5,2,dm) },{ 40,Bul(4,10,0,dm) },{ 50,Bul(5,10,1,dm) },{ 60,Bul(6,10,2,dm) },
                                {50,Bul(7,5,2,dm)}, { 60,Bul(8,5,1,dm) },{ 70,Bul(9,5,0,dm) },{ 80,Bul(10,10,2,dm) },{ 90,Bul(11,10,1,dm) },{ 100,Bul(12,10,0,dm) },
                                { 115,Bul(13,10,0,dm,100) },{125,Bul(14,10,1,dm)},{135,Bul(15,10,2,dm)},
                                {135,Bul(16,10,1,dm,100)},{145,Bul(17,10,0,dm)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,10,1,dm,1000)},{15,Bul(2,10,1,dm,10,chgLine(2,100,110,1,0))},{23,Bul(3,10,1,dm,10,chgLine(3,100,110,1,0))},
                                {24,Bul(4,10,1,dm,10,chgLine(4,100,110,1,2))},{30,Bul(5,10,1,dm,10,chgLine(5,200,210,1,2))},
                                {38,Bul(6,10,1,dm,10,chgLine(6,200,210,1,0))},{45,Bul(7,10,1,dm,10,chgLine(7,200,210,1,2))},
                                {51,Bul(8,10,1,dm,10,chgLine(8,150,160,1,2))},{60,Bul(9,10,0,dm,10)},{66,Bul(10,10,2,dm,10)},
                                {74,Bul(11,10,2,dm,10,chgLine(11,150,160,2,0))},{85,Bul(12,10,0,dm,10,chgLine(12,170,180,0,2))},
                                {95,Bul(13,10,0,dm,150)},{95,Bul(14,10,2,dm,150)}
                                }),
                            Battle::Attack({
                                {10,Bul(1,2,1,15,10,2)},
                                {10,Bul(2,10,0,dm)},{14,Bul(3,10,1,dm)},{18,Bul(4,10,2,dm)},{22,Bul(5,10,0,dm)},{26,Bul(6,10,1,dm)},{30,Bul(7,10,2,dm)},
                                {34,Bul(8,10,0,dm)},{38,Bul(9,10,1,dm,20)},{42,Bul(10,10,2,dm)},{46,Bul(11,10,0,dm,20)},{50,Bul(12,10,1,dm)},{54,Bul(13,10,2,dm)},
                                {58,Bul(14,10,0,dm)},{62,Bul(15,10,1,dm)},{66,Bul(16,10,2,dm,20)},
                                {72,Bul(17,10,2,dm,20)},{76,Bul(18,10,1,dm,40)},{80,Bul(19,10,0,dm,20)},{84,Bul(20,10,2,dm,40)},{88,Bul(21,10,1,dm,20)},{92,Bul(22,10,0,dm,20)},
                                {96,Bul(23,10,2,dm,20)},{100,Bul(24,10,1,dm,20)},{104,Bul(25,10,0,dm,40)},
                                {108,Bul(50,10,2,dm)},
                                {110,Bul(26,10,0,dm)},{112,Bul(27,10,2,dm)},{114,Bul(28,10,0,dm)},{116,Bul(29,10,2,dm)},{118,Bul(30,10,0,dm)},{120,Bul(31,10,2,dm)},
                                {122,Bul(32,10,0,dm)},{124,Bul(33,10,2,dm)},{126,Bul(34,10,0,dm)},{128,Bul(35,10,2,dm)},{130,Bul(36,10,0,dm)},{132,Bul(37,10,2,dm)},
                                {134,Bul(38,10,0,dm)},{136,Bul(39,10,2,dm)},{138,Bul(40,10,0,dm)},{140,Bul(41,10,2,dm)},{142,Bul(42,10,0,dm)},{144,Bul(43,10,2,dm)},
                                {146,Bul(44,10,0,dm)},{148,Bul(45,10,2,dm)},{150,Bul(46,10,0,dm)},{152,Bul(47,10,2,dm)},{154,Bul(48,10,0,dm)},{156,Bul(49,10,2,dm)}
                                }),
                                    };
                                    std::vector<int> possible;
                                    possible.clear();
                                    if (bt.enemy_hp <= 30) {
                                        for (int _ = 0; _ < 5; _++)possible.push_back(3);
                                        for (int _ = 0; _ < 10; _++)possible.push_back(4);
                                        for (int _ = 0; _ < 20; _++)possible.push_back(5);
                                        for (int _ = 0; _ < 30; _++)possible.push_back(6);
                                        for (int _ = 0; _ < 40; _++)possible.push_back(7);
                                        for (int _ = 0; _ < 40; _++)possible.push_back(8);
                                    }
                                    else  if (bt.enemy_hp <= 60) {
                                        for (int _ = 0; _ < 5; _++)possible.push_back(0);
                                        for (int _ = 0; _ < 5; _++)possible.push_back(1);
                                        for (int _ = 0; _ < 5; _++)possible.push_back(2);
                                        for (int _ = 0; _ < 5; _++)possible.push_back(3);
                                        for (int _ = 0; _ < 20; _++)possible.push_back(4);
                                        for (int _ = 0; _ < 20; _++)possible.push_back(5);
                                        for (int _ = 0; _ < 20; _++)possible.push_back(6);
                                        for (int _ = 0; _ < 30; _++)possible.push_back(7);
                                        for (int _ = 0; _ < 30; _++)possible.push_back(8);
                                    }
                                    else if (bt.enemy_hp <= 130) {
                                        for (int _ = 0; _ < 10; _++)possible.push_back(0);
                                        for (int _ = 0; _ < 10; _++)possible.push_back(1);
                                        for (int _ = 0; _ < 10; _++)possible.push_back(2);
                                        for (int _ = 0; _ < 10; _++)possible.push_back(3);
                                        for (int _ = 0; _ < 20; _++)possible.push_back(4);
                                        for (int _ = 0; _ < 20; _++)possible.push_back(5);
                                        for (int _ = 0; _ < 20; _++)possible.push_back(6);
                                    }
                                    else {
                                        for (int _ = 0; _ < 20; _++)possible.push_back(0);
                                        for (int _ = 0; _ < 20; _++)possible.push_back(1);
                                        for (int _ = 0; _ < 20; _++)possible.push_back(2);
                                        for (int _ = 0; _ < 20; _++)possible.push_back(3);
                                    }


                                    int choose = possible[rand() % possible.size()];
                                    while (choose == bt.localVar["LASTATK"])choose = possible[rand() % possible.size()];
                                    bt.localVar["LASTATK"] = choose;
                                    bt.setAttack(atk[choose]);

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
                            []() {Conversation::getInstance().beginConversation(Text(L"* 你做到了!"));
                                },
                            []() {
                                ConversationSequence::getInstance().stopBattleConv(); 
                                BattleController::getInstance().endBattle();  
                                GameManager::getInstance().addWaiting([](){
                                    GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
                                    GameManager::getInstance().setRoom(ROOM_PORTAL,GAME_STATE_CUTSCENE);
                                    },0);
                            } });
                        ConversationSequence::getInstance().startBattleConv();
                        });
                    ev.subscribe("BATTLE_END_MERCY", "BattleMercyListen", [=]() {
                        AudioManager::getInstance().stopBgm();
                        ConversationSequence::getInstance().setSequence(ConvSeq{
                            []() {Conversation::getInstance().beginConversation(Text(L"* 这不可能。"));},
                            []() {ConversationSequence::getInstance().stopBattleConv();
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

        };

    Entity* tv = new Entity("TV", 140, 50, { 0,0,41 * 2,33 * 2 }, { 0,0,41 * 2,33 * 2 }, Animation(rs.getResource("LABTV"), 1, 1, 1, 41, 33));
    tv->setVisible(1);
    tv->setReaction([=]() {
        ConversationSequence::getInstance().setSequence({
            [=]() {Conversation::getInstance().beginConversation(Text(L"               准备好了吗？"),
                Conversation::Choice(ChoiceItem({
                    Text(L"还没有"),
                    Text(L"准备好了")
                    }),[](int res) {GameManager::getInstance().globalVar["Choose_Temp"] = res + 1; })); },
            [=]() {
                if (GameManager::getInstance().globalVar["Choose_Temp"] == 1) {
                    ConversationSequence::getInstance().stopConversation();
                }
                else if (GameManager::getInstance().globalVar["Choose_Temp"] == 2) {
                    ConversationSequence::getInstance().stopConversation();
                    GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_CUTSCENE;
                    AudioManager::getInstance().playSound("BGM_STRANGE");
                    GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_CUTSCENE;
                    entities["Wall"]->setVisible(1);
                    entities["Wall"]->setPassable(0);
                    GameManager::getInstance().addWaiting([=]() {
                        entities["Glitch1"]->setVisible(1);
                        }, 30);
                    GameManager::getInstance().addWaiting([=]() {
                        entities["Glitch2"]->setVisible(1);
                        }, 60);
                    GameManager::getInstance().addWaiting([=]() {
                        entities["Glitch3"]->setVisible(1);
                        }
                    , 90);
                    GameManager::getInstance().addWaiting([=]() {
                        AudioManager::getInstance().stopBgm();
                        }, 135);
                    GameManager::getInstance().addWaiting([=]() {
                        battle();
                        }, 140);
                }
            }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(tv);















    Entity* portal = new Entity("Portal", 160, 380, { 0,0,40,5 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 1;
        GameManager::getInstance().setRoom(ROOM_LAB_TALK); }, 1);
    addEntity("Portal", portal);

    Entity* airwallTop = new Entity("AirwallTop", 0, 115, { 0,0,360,5 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,5,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, 360, { 0,0,150,40 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 210, 360, { 0,0,150,40 }, false),
        * airwallRight = new Entity("AirwallRight", 370, 0, { 0,0,10,height }, false);
    addEntity(airwallTop);
    addEntity(airwallLeft);
    addEntity(airwallBottom);
    addEntity(airwallBottom1);
    addEntity(airwallRight);

}
Room_Lab_Fight::~Room_Lab_Fight() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_lab_fight");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}