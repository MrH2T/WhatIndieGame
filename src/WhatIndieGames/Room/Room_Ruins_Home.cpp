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
                [=]() {C->beginConversation(Text(L"* 里面有一块巧克力")); },
                [=]() {Conversation::getInstance().beginConversation(Text(L"              要拿一块吗？"),
                    Conversation::Choice(ChoiceItem({
                    Text(L"拿一颗"),
                    Text(L"不拿")
                    }),[](int res) {GameManager::getInstance().globalVar["Choose_Temp"] = res + 1; })); },
                [=]() {
                if (GameManager::getInstance().globalVar["Choose_Temp"] == 1) {
                    if (GameManager::getInstance().inventory.size() == INVENTORY_SIZE) {
                        Conversation::getInstance().beginConversation(Text(L"* 你拿不下了。"));
                    }
                    else {
                        Conversation::getInstance().beginConversation(Text(L"* 你拿了一块巧克力。"));
                        GameManager::getInstance().savingVar["CHAIRIEL_CHOCO"] = 1;
                        GameManager::getInstance().addItem("巧克力");
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
                [=]() {C->beginConversation(Text(L"* 是空的。")); },
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
            [=]() {C->beginConversation(Text(L"* 非常整洁的水槽。")); }
            });
        CS.startConversation();
        }, 0);
    addEntity(sink);
    Entity* oven = new Entity("Oven", 290, 100, { 0,0,50,40 }, true);
    oven->setReaction([&]() {
        auto& CS = ConversationSequence::getInstance();
        auto* C = &Conversation::getInstance();
        CS.setSequence({
            [=]() {C->beginConversation(Text(L"* 灶台上有刚刚用过的痕迹。")); }
            });
        CS.startConversation();
        }, 0);
    addEntity(oven);

    Entity* shelf = new Entity("Shelf", 420, 400, { 0,0,120,40 }, true);
    shelf->setReaction([&]() {
        auto& CS = ConversationSequence::getInstance();
        auto* C = &Conversation::getInstance();
        CS.setSequence({
            [=]() {C->beginConversation(Text(L"* 书架上是你从来没见过的书。")); }
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
                    [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* 我在冰箱里放了一些巧克力。"),torielface); },
                    [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* 如果你想吃的话可以拿来吃！"),torielface); }
                });
        }
        
        else if (gm.savingVar.find("CHAIRIEL_TASK_FINISHED") == gm.savingVar.end()) {
            if (gm.savingVar.find("CHAIRIEL_CELLPHONE") == gm.savingVar.end()) {
                CS.setSequence({
                    [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* 你知道吗，我在南边散步的时候把手机弄丢了。"),torielface); },
                    [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* 如果你能帮我找回来我会很开心的。"),torielface); }
                    });
            }
            else {
                CS.setSequence({
                    [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* 那就是我的手机！非常感谢！"),torielface); },
                    [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK");
                if (GameManager::getInstance().inventory.size() == INVENTORY_SIZE) {
                    C->beginConversation(Text(L"* 我想给你一个我自己烤的派，但是你好像装不下了。"),torielface);
                        }
                else {
                    C->beginConversation(Text(L"* 这是我自己烤的派，尽情享用吧！"), torielface);
                    GameManager::getInstance().addItem("派");
                    GameManager::getInstance().savingVar["CHAIRIEL_TASK_FINISHED"] = 1;
                }
                    }
                    });
            }
        }
        else {
            CS.setSequence({
                   [=]() {AudioManager::getInstance().playSound("SND_TORIEL_SPEAK"); C->beginConversation(Text(L"* 我相信你一定能回去的！"),torielface); }
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