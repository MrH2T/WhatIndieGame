#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Snow_Town::Room_Snow_Town() :Room(ROOM_SNOW_TOWN, NULL, WINDOW_WIDTH, WINDOW_HEIGHT) {
    roomInit();
}
void Room_Snow_Town::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_SNOWTOWN"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_SNOWTOWN", true);
    calculateMap(ResourceManager::getInstance().getResource("SNOW_TILESET"), 63, 9,
        { {49,49,49,153,154,155,153,154,155,153,154,155,153,154,155,153,154,155,153,154,155,153,154,155,153,154,155,153,154,155,153,163,155,153,163,155,153,163,155,153,153,154,155,153,154,155,153,154,155,153,154,155,153,154,155,153,154,155,153,154,155,153,154,155,153,154,155,153,163,155,153,163,155,153,163,155,153}
,{49,49,49,162,163,164,162,163,164,162,163,164,162,163,164,162,163,164,162,163,164,162,163,164,162,163,164,164,163,164,162,163,164,162,163,164,162,163,164,162,162,163,164,162,163,164,162,163,164,162,163,164,162,163,164,162,163,164,162,163,164,162,163,164,164,163,164,162,163,164,162,163,164,162,163,164,162}
,{49,49,49,171,172,173,154,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171,172,173,171}
,{49,49,49,180,181,182,154,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180,181,182,180}
,{49,49,49,189,190,191,0,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,  189,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,189,190,191,  189}
,{49,49,49,198,199,200,0,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,  198,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,198,199,200,  198}
,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
,{10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}
,{19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19}
,{19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19}
,{28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28}
,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    0}
,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  221,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,  221}
,{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,221,221,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,221,221}
,{230,230,230,230,230,230,230,230,230,230,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,0,0,0,0,0,0,0,230,230,230,230,230,230,230,230,230,230,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,221,0,0,0,0,0,0,0,230,230,230}
,{239,239,239,239,239,239,239,239,239,239,263,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,236,239,239,239,239,239,239,239,239,239,239,263,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,230,236,239,239,239}
,{239,239,239,239,239,239,239,239,239,239,272,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,245,239,239,239,239,239,239,239,239,239,239,272,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,245,239,239,239}
,{239,239,239,239,239,239,239,239,239,239,272,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,245,239,239,239,239,239,239,239,239,239,239,272,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,245,239,239,239}
,{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,281,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,254,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,281,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,239,254,-1,-1,-1}
        }
    );

    Canvas::getInstance().addObject("background_snow_town",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 130,530 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_RIGHT);
        break;
    case 1:
        //RIGHT
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 2970,520 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_LEFT);
        break;
    case 2:
        //SNOWMAN 
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 240,200 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    case 3:
        //INN
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 1270,480 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    case 4:
        //House1
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 1610,480 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    case 5:
        //House2
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 2110,480 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    case 6:
        //Lib
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 2520,480 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    case ROOM_ENTRY_SAVING:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 1090,500 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);
    auto& gm = GameManager::getInstance();
    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();

    Entity* entrance = new Entity("Entrance", 0, 240, { 0,0,132,444 }, { 0,0,132,444 }, Animation(ResourceManager::getInstance().getResource("RUINS_ENTRANCE"), 1, 1, 1, 66, 222));
    entrance->setPassable(1);
    entrance->setVisible(1);
    addEntity(entrance);

    Entity* logo = new Entity("Logo", 200, 300, { 0,90,178*3,45*3 }, { 0,0,178*3,45*3 }, Animation(ResourceManager::getInstance().getResource("SNOWDIN_LOGO"), 1, 1, 1, 178, 45));
    logo->setVisible(1);
    logo->setDrawYPrioBias(50);
    addEntity(logo);

    Entity* innshop = new Entity("Inn_Shop", 800, 200, { 0,141,312 * 2,141 * 2 }, { 0,0,312 *2,141 * 2 }, Animation(ResourceManager::getInstance().getResource("BG_INN_SHOP"), 1, 1, 1, 312, 141));
    innshop->setVisible(1);
    innshop->setDrawYPrioBias(100);
    addEntity(innshop);

    Entity* house1 = new Entity("House1", 1500, 240, { 0,100,256,236 }, { 0,0, 256,236 },
        Animation(ResourceManager::getInstance().getResource("HOUSE"), 1, 1, 1, 128, 118));
    house1->setVisible(1);
    house1->setDrawYPrioBias(100);
    addEntity(house1);

    Entity* tree = new Entity("Christmastree", 1850, 300, { 0,100,128,170 }, { 0,0, 128,170 },
        Animation(ResourceManager::getInstance().getResource("CHRISTMASTREE"), 1, 1, 1, 64, 85));
    tree->setDrawYPrioBias(100);
    tree->setVisible(1);
    addEntity(tree);

    Entity* house2 = new Entity("House2", 2000, 240, { 0,100,256,236 }, { 0,0, 256,236 },
        Animation(ResourceManager::getInstance().getResource("HOUSE"), 1, 1, 1, 128, 118));
    house2->setVisible(1);
    house2->setDrawYPrioBias(100);
    addEntity(house2);

    Entity* lib = new Entity("Library", 2400, 200, { 0,138,248*2,138*2 }, { 0,0, 248*2,138*2 },
        Animation(ResourceManager::getInstance().getResource("LIBRARY"), 1, 1, 1, 248, 138));
    lib->setVisible(1);
    lib->setDrawYPrioBias(138);
    addEntity(lib);

    Entity* giftbear = new Entity("Giftbear", 1770, 370, { 0,41,40 * 2,41 * 2 }, { 0,0,40 * 2,41 * 2 }, Animation(
        rs.getResource("GIFTBEAR"), 1, 1, 1, 40, 41));
    giftbear->setVisible(1);
    giftbear->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* ��ÿ�궼�������һ�����")); },
            []() {Conversation::getInstance().beginConversation(Text(L"* �������������û���յ�������...")); } }
        );
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(giftbear);

    Entity* rabbitkid = new Entity("Rabbitkid", 1720, 630, { 0,35,20 * 2,35* 2 }, { 0,0,20 * 2,35 * 2 }, Animation(
        rs.getResource("RABBITKID"), 1, 1, 1, 20, 35));
    rabbitkid->setVisible(1);
    rabbitkid->setReaction([]() {
        if (GameManager::getInstance().savingVar.find("RABBITKID_INFORMED") == GameManager::getInstance().savingVar.end()) {
            ConversationSequence::getInstance().setSequence({
                    []() {Conversation::getInstance().beginConversation(Text(L"* ��˵��������һ������������ˡ�"));},
                    []() {Conversation::getInstance().beginConversation(Text(L"* ����ʶ����?"));},
                    []() {Conversation::getInstance().beginConversation(

                        Conversation::Choice(ChoiceItem({
                            Text(L"��ʶ"),
                            Text(L"����ʶ")
                            }),[](int res) {GameManager::getInstance().globalVar["Choose_Temp"] = res + 1; })
                    ); },
                    []() {
                        if (GameManager::getInstance().globalVar["Choose_Temp"] == 1) {
                            Conversation::getInstance().beginConversation(Text(L"* ���ʵ�Ǿ����ҡ�"),
                                Animation(ResourceManager::getInstance().getResource("NIKO_SPEAK_FACE"),1,1,1,96,96));
                            GameManager::getInstance().savingVar["RABBITKID_INFORMED"] = 1;
                        }
                        else if (GameManager::getInstance().globalVar["Choose_Temp"] == 2) {
                            Conversation::getInstance().beginConversation(Text(L"* û�£���Ҳ����ʶ��"));
                        }
                    } ,
                    []() {
                        if (GameManager::getInstance().globalVar["Choose_Temp"] == 1) {
                            Conversation::getInstance().beginConversation(Text(L"* �ǿ������档"));
                        }
                        else if (GameManager::getInstance().globalVar["Choose_Temp"] == 2) {
                            ConversationSequence::getInstance().stopConversation();
                        }
                    }
                    }
                );
        }
        else {
            ConversationSequence::getInstance().setSequence({
                    []() {Conversation::getInstance().beginConversation(Text(L"* �ܸ�����ʶ�㡣")); },
                }
            );
        }
        
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(rabbitkid);

    Entity* icecap = new Entity("Icecap", 1660, 630, { 0,35,21 * 2,35 * 2 }, { 0,0,21 * 2,35 * 2 }, Animation(
        rs.getResource("ICECAP"), 1, 1, 1, 21, 35));
    icecap->setVisible(1);
    icecap->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {
                if (GameManager::getInstance().savingVar.find("MEET_SNOWMAN") == GameManager::getInstance().savingVar.end()) {
                    Conversation::getInstance().beginConversation(Text(L"* ����˵�и��ط��и�ѩ�ˡ�"));
                }
                else {
                    Conversation::getInstance().beginConversation(Text(L"* ��˵�㿴����һ��ѩ��?"));
                }
                 },
            []() {Conversation::getInstance().beginConversation(Text(L"* ���´�һ��Ҫȥ������")); },
            }
        );
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(icecap);

    Entity* wrapmouse = new Entity("Wrapmouse", 1520, 450, { 0,37,37 * 2,37 * 2 }, { 0,0,37 * 2,37 * 2 }, Animation(
        rs.getResource("WRAPMOUSE"), 1, 1, 1, 37, 37));
    wrapmouse->setVisible(1);
    wrapmouse->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
           []() {
               if (GameManager::getInstance().savingVar.find("MOUSE_KEY_FOUND") == GameManager::getInstance().savingVar.end()) {
                   Conversation::getInstance().beginConversation(Text(L"* �Ұ�Կ�׸����ˡ�"));
               }
               else {
                   Conversation::getInstance().beginConversation(Text(L"* ���ҵ����ҵ�Կ��?"));
               }
                },
           []() {
                if (GameManager::getInstance().savingVar.find("MOUSE_KEY_FOUND") == GameManager::getInstance().savingVar.end()) {
                    Conversation::getInstance().beginConversation(Text(L"* ������ֻ�������洵���ˡ�"));
               }
               else {
                   Conversation::getInstance().beginConversation(Text(L"* �һ�����������Ŵ���ɡ�"));
               }
                 },
            }
        );
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(wrapmouse);

    Entity* scarflady = new Entity("Scarflady", 2430, 430, { 0,41,28 * 2,41 * 2 }, { 0,0,28 * 2,41 * 2 }, Animation(
        rs.getResource("SCARFLADY"), 1, 1, 1, 28, 41));
    scarflady->setVisible(1);
    scarflady->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
          []() {Conversation::getInstance().beginConversation(Text(L"* �Ҿ��������ͼ��ݡ�")); },
          []() {Conversation::getInstance().beginConversation(Text(L"* ��Ҫ������ͦů�͵ġ�")); },
            }
        );
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(scarflady);

    Entity* shop = new Entity("Shop", 900, 470, { 0,0,60,20 },true);
    shop->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
          []() {Conversation::getInstance().beginConversation(Text(L"* �̵꣺��������ð���7Gһ��")); },
          []() {Conversation::getInstance().beginConversation(Text(L"��һ����?"),
                    Conversation::Choice(ChoiceItem({
                        Text(L"��һ��"),
                        Text(L"����")
                        }),[](int res) {GameManager::getInstance().globalVar["Choose_Temp"] = res + 1; })
                ); },
                []() {
                    if (GameManager::getInstance().globalVar["Choose_Temp"] == 1) {
                        if (GameManager::getInstance().savingVar[GLOBAL_PLAYER_GOLD] < 7) {
                             Conversation::getInstance().beginConversation(Text(L"* ��û��ô��Ǯ��"));
                        }
                        else if (GameManager::getInstance().inventory.size() == INVENTORY_SIZE) {
                            Conversation::getInstance().beginConversation(Text(L"* ��Ų����ˡ�"));
                        }
                        else {
                            GameManager::getInstance().addItem("����ð�");
                            GameManager::getInstance().addGold(-7);
                        }
                        ConversationSequence::getInstance().stopConversation();
                    }
                    else if (GameManager::getInstance().globalVar["Choose_Temp"] == 2) {
                            ConversationSequence::getInstance().stopConversation();
                    }
                }
            }
            );
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(shop);


    Entity* portal1 = new Entity("Portal1", 20, 490, { 0,0,70,100 }, true);
    portal1->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 1;
        GameManager::getInstance().setRoom(ROOM_RUINS_TORIEL); }, 1);
    addEntity("Portal1", portal1);
    Entity* portal2 = new Entity("Portal2", 3060, 510, { 0,0,5,100 }, true);
    portal2->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_SNOW_CROSSROADS); }, 1);
    //addEntity(portal2);

    if (GameManager::getInstance().savingVar.find("MOUSE_KEY_FOUND") != GameManager::getInstance().savingVar.end()) {
        Entity* portal3 = new Entity("PortalHouse", 1600, 450, { 0,0,60,30 }, true);
        portal3->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_SNOW_HOUSE); }, 1);
        addEntity("Portal3", portal3);
    }
    Entity* portal4 = new Entity("PortalLib", 2510, 470, { 0,0,60,10 }, true);
    portal4->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_SNOW_LIBRARY); }, 1);
    addEntity(portal4);

    Entity* portal5 = new Entity("PortalSanshouse", 2090, 470, { 0,0,60,10 }, true);
    portal5->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_SNOW_SANSHOUSE); }, 1);
    addEntity(portal5);

    Entity* portal6 = new Entity("PortalInn", 1260, 480, { 0,0,60,10 }, true);
    portal6->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_SNOW_INN); }, 1);
    addEntity(portal6);

    Entity* portal7 = new Entity("PortalSnowman", 240, 120, { 0,0,60,10 }, true);
    portal7->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_SNOW_SNOWMAN); }, 1);
    addEntity(portal7);

    Entity
        * airwallTop = new Entity("AirwallTop", 120, 60, { 0,0,110,170 }, false),
        * airwallTop1 = new Entity("AirwallTop1", 290, 60, { 0,0,width,170 }, false),
        * airwallLeft = new Entity("AirwallLeft", 95, 210, { 0,0,10,300 }, false),
        * airwallLeft1 = new Entity("AirwallLeft1", 15, 600, { 0,0,10,200 }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, 800, { 0,0,width,5 }, false),
        * airwallRight = new Entity("AirwallRight", 3070, 210, { 0,0,5,280 }, false),
        * airwallRight1 = new Entity("AirwallRight1", 3070, 610, { 0,0,5,200 }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallTop1", airwallTop1);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallLeft1", airwallLeft1);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallRight", airwallRight);
    addEntity("AirwallRight1", airwallRight1);
    
    Entity* savepoint = new Entity("Savepoint", 1090, 470, { 5,5,35,35 }, { 0,0,40,40 },
        Animation(ResourceManager::getInstance().getResource("SAVEPOINT"), 2, 1, 2, 20, 20, 5));
    savepoint->setVisible(true);
    savepoint->setReaction([]() {
        //AudioManager::getInstance().playSound("SND_SAVING");
        GameManager::getInstance().addHP(1000);
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* ����ѩ�е�С����������˾��ġ�"));
            },
            []() {Conversation::getInstance().beginConversation(Text(L"* �浵�ѱ��棡"));
                    GameManager::getInstance().gameSaving();
            } });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity("Savepoint", savepoint);
}
Room_Snow_Town::~Room_Snow_Town() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_snow_town");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}
void Room_Snow_Town::roomUpdate() {

}