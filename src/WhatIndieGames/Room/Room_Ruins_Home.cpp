#include"AllRooms.h"

Room_Ruins_Home::Room_Ruins_Home() :Room(ROOM_RUINS_HOME, NULL, 1280, 802) {
    roomInit();
}
void Room_Ruins_Home::roomInit() {
    AudioManager::getInstance().stopBgm();
    map = ResourceManager::getInstance().getResource("HOME_BACKGROUND");
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    auto& gm = GameManager::getInstance();
    cv.addObject("room_home_background", DrawableObject(Animation(map, 1, 1, 1, 640, 401),
        0, 0, RECT({ 0,0,width,height }), 0));
    if(!AudioManager::getInstance().isPlaying("BGM_HOME"))AudioManager::getInstance().stopBgm(),AudioManager::getInstance().playSound("BGM_HOME", true);

    switch (gm.globalVar[ROOM_ENTRANCE]) {
    case 0:
        gm.entities[ENTITY_MAIN_PLAYER]->setPos({ 940,710 });
        gm.entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    }
    gm.entities[ENTITY_MAIN_PLAYER]->setVisible(true);


    Entity
        * airwall1 = new Entity("Airwall1", 0, 50, { 0,0,390,100 }, false),
        * airwall2 = new Entity("Airwall2", 0, 50, { 0,0,30,720 }, false),
        * airwall3 = new Entity("Airwall3", 30, 760, { 0,0,880,30 }, false),
        * airwall4 = new Entity("Airwall4", 1000, 760, { 0,0,270,30 }, false),
        * airwall5 = new Entity("Airwall5", 1210, 330, { 0,0,10,500 }, false),
        * airwall6 = new Entity("Airwall6", 610, 430, { 0,0,600,170 }, false),
        * airwall7 = new Entity("Airwall7", 610, 740, { 0,0,90,50 }, false),
        * airwall8 = new Entity("Airwall8", 180, 290, { 0,0,420,160 }, false),
        * airwall9 = new Entity("Airwall9", 370, 80, { 0,0,420,200 }, false),
        * airwall10 = new Entity("Airwall10", 40, 290, { 0,0,40,150 }, false);
    addEntity(airwall1);
    addEntity(airwall2);
    addEntity(airwall3);
    addEntity(airwall4);
    addEntity(airwall5);
    addEntity(airwall6);
    addEntity(airwall7);
    addEntity(airwall8);
    addEntity(airwall9);
    addEntity(airwall10);

    Entity* fridge = new Entity("Fridge",50,100,{0,0,50,40},true);
    fridge->setReaction([&]() {
        auto& CS = ConversationSequence::getInstance();
        auto* C = &Conversation::getInstance();
        if (gm.savingVar.find("CHAIRIEL_CHOCO") == gm.savingVar.end()) {
            CS.setSequence({
                [=]() {C->beginConversation(Text(L"* ������һ���ɿ���")); },
                [=]() {Conversation::getInstance().beginConversation(Text(L"              Ҫ��һ����"),
                    Conversation::Choice(ChoiceItem({
                    Text(L"��һ��"),
                    Text(L"����")
                    }),[](int res) {GameManager::getInstance().globalVar["Choose_Temp"] = res + 1; })); },
                [=]() {
                if (GameManager::getInstance().globalVar["Choose_Temp"] == 1) {
                    if (GameManager::getInstance().inventory.size() == INVENTORY_SIZE) {
                        Conversation::getInstance().beginConversation(Text(L"* ���ò����ˡ�"));
                    }
                    else {
                        Conversation::getInstance().beginConversation(Text(L"* ������һ���ɿ�����"));
                        GameManager::getInstance().savingVar["CHAIRIEL_CHOCO"] = 1;
                        GameManager::getInstance().addItem("�ɿ���");
                    }
                }
                else if (GameManager::getInstance().globalVar["Choose_Temp"] == 2) {
                    ConversationSequence::getInstance().stopConversation();
                }
                } });
            CS.startConversation();
        }
        else {
            CS.setSequence({
                [=]() {C->beginConversation(Text(L"* �ǿյġ�")); },
                });
            CS.startConversation();
        }
        }, 0);
    addEntity(fridge);

    Entity* sink = new Entity("Sink", 130, 100, { 0,0,50,40 }, true);
    sink->setReaction([&]() {
        auto& CS = ConversationSequence::getInstance();
        auto* C = &Conversation::getInstance();
        CS.setSequence({
            [=]() {C->beginConversation(Text(L"* �ǳ������ˮ�ۡ�")); }
            });
        CS.startConversation();
        }, 0);
    addEntity(sink);
    Entity* oven = new Entity("Oven", 290, 100, { 0,0,50,40 }, true);
    oven->setReaction([&]() {
        auto& CS = ConversationSequence::getInstance();
        auto* C = &Conversation::getInstance();
        CS.setSequence({
            [=]() {C->beginConversation(Text(L"* ��̨���иո��ù��ĺۼ���")); }
            });
        CS.startConversation();
        }, 0);
    addEntity(oven);

    Entity* shelf = new Entity("Shelf", 420, 400, { 0,0,120,40 }, true);
    shelf->setReaction([&]() {
        auto& CS = ConversationSequence::getInstance();
        auto* C = &Conversation::getInstance();
        CS.setSequence({
            [=]() {C->beginConversation(Text(L"* ������������û�������顣")); }
            });
        CS.startConversation();
        }, 0);
    addEntity(shelf);



    Entity* portal = new Entity("Portal", 920, 780, { 0,0,100,10 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 3;
        GameManager::getInstance().setRoom(ROOM_RUINS_TORIEL); }, 1);
    addEntity("Portal", portal);

    Entity* chairiel = new Entity("Chairiel", 270, 520, { 20,52,94,104 }, {0,0,94,104},Animation(ResourceManager::getInstance().getResource("CHAIRIEL"),1,1,1,47,52));
    chairiel->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 3;
        GameManager::getInstance().setRoom(ROOM_RUINS_TORIEL); }, 1);
    chairiel->setVisible(1);
    chairiel->setReaction([&]() {
        auto& CS = ConversationSequence::getInstance();
        auto* C = &Conversation::getInstance();
        Animation torielface = Animation(ResourceManager::getInstance().getResource("TORIEL_FACE"), 1, 1, 1, 32, 32);
        if (gm.savingVar.find("CHAIRIEL_CHOCO") == gm.savingVar.end()&& (gm.savingVar.find("CHAIRIEL_CELLPHONE") == gm.savingVar.end()
                || gm.savingVar.find("CHAIRIEL_TASK_FINISHED") != gm.savingVar.end())) {
            CS.setSequence({
                    [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* ���ڱ��������һЩ�ɿ�����"),torielface); },
                    [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* �������ԵĻ����������ԣ�"),torielface); }
                });
        }
        
        else if (gm.savingVar.find("CHAIRIEL_TASK_FINISHED") == gm.savingVar.end()) {
            if (gm.savingVar.find("CHAIRIEL_CELLPHONE") == gm.savingVar.end()) {
                CS.setSequence({
                    [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* ��֪���������ϱ�ɢ����ʱ����ֻ�Ū���ˡ�"),torielface); },
                    [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* ������ܰ����һ����һ�ܿ��ĵġ�"),torielface); }
                    });
            }
            else {
                CS.setSequence({
                    [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* �Ǿ����ҵ��ֻ����ǳ���л��"),torielface); },
                    [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK");
                if (GameManager::getInstance().inventory.size() == INVENTORY_SIZE) {
                    C->beginConversation(Text(L"* �������һ�����Լ������ɣ����������װ�����ˡ�"),torielface);
                        }
                else {
                    C->beginConversation(Text(L"* �������Լ������ɣ��������ðɣ�"), torielface);
                    GameManager::getInstance().addItem("��");
                    GameManager::getInstance().savingVar["CHAIRIEL_TASK_FINISHED"] = 1;
                }
                    }
                    });
            }
        }
        else {
            CS.setSequence({
                   [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* ��������һ���ܻ�ȥ�ģ�"),torielface); }
                });
        }
        CS.startConversation();


        }, 0);


    addEntity(chairiel);


    
}
Room_Ruins_Home::~Room_Ruins_Home() {
    clearEntities();;
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    cv.deleteObject("room_home_background");

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}