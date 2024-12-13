#include"AllRooms.h"

Room_Falldown::Room_Falldown() :Room(ROOM_FALLDOWN, NULL, 680*2, 260*2) {
    roomInit();
}
void Room_Falldown::roomInit() {
    AudioManager::getInstance().stopBgm();
    map = ResourceManager::getInstance().getResource("BG_FALLDOWN");
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    auto& gm = GameManager::getInstance();
    cv.addObject("room_falldown_background", DrawableObject(Animation(map, 1, 1, 1, 680, 260),
        0, 0, RECT({ 0,0,width,height }), 0));


    switch (gm.globalVar[ROOM_ENTRANCE]) {
    case 0:
        gm.entities[ENTITY_MAIN_PLAYER]->setPos({ 280,240 });
        gm.entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    case 1:
        gm.entities[ENTITY_MAIN_PLAYER]->setPos({ 1210,310 });
        gm.entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    }
    gm.entities[ENTITY_MAIN_PLAYER]->setVisible(true);

    Entity* flowerins = new Entity("Flowerins", 280-30, 240, { 0,0,80,80 }, true);
    flowerins->setReaction([&]() {
        ConversationSequence::getInstance().setSequence({
            []() {
                Conversation::getInstance().beginConversation(Text(L"* 是这些花接住了你。"));
            } });
        ConversationSequence::getInstance().startConversation(); }, 0);
    addEntity("Flowerins", flowerins);

    Entity* airwallTop = new Entity("AirwallTop", 60, 90, { 0,0,width,10 }, false),
        * airwallTop1 = new Entity("AirwallTop1", 570, 280, { 0,0,600,10 }, false),
        * airwallLeft = new Entity("AirwallLeft", 30, 100, { 0,0,10,height }, false),
        * airwallLeft1 = new Entity("AirwallLeft1", 150, 40*7-30, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 40, 480, { 0,0,width,10 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 490, 400, { 0,0,width,10 }, false),
        * airwallBottom2 = new Entity("AirwallBottom2", 610, 40*7-40, { 0,0,40*4,10 }, false),
        * airwallRight = new Entity("AirwallRight", 1340, -10, { 0,0,10,height }, false),
        * airwallRight1 = new Entity("AirwallRight1", 570, 80, { 0,0,10,200 }, false),
        * airwallRight2 = new Entity("AirwallRight2", 490, 400, { 0,0,10,200 }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallTop1", airwallTop1);
    addEntity("AirwallLeft", airwallLeft);
    //addEntity("AirwallLeft1", airwallLeft1);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallBottom1", airwallBottom1);
    //addEntity("AirwallBottom2", airwallBottom2);
    addEntity("AirwallRight", airwallRight);
    addEntity("AirwallRight1", airwallRight1);
    addEntity("AirwallRight2", airwallRight2);

    Entity* portal = new Entity("Portal", 1200, 270, { 0,0,100,10 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_RUINS_BATTLE); }, 1);
    addEntity("Portal", portal);


    if (gm.savingVar.find("ROOM_FALLDOWN_ARRIVE") == gm.savingVar.end()) {
        gm.addWaiting([&]() {
            ConversationSequence::getInstance().setSequence({
                []() {Conversation::getInstance().beginConversation(Text(L"* 我这是到哪里了???"),
                    Animation(ResourceManager::getInstance().getResource("NIKO_SHOCK_FACE"),1,1,1,96,96)); },
                [&]() {ConversationSequence::getInstance().stopConversation();  gm.globalVar[GLOBAL_GAME_STATE] = GAME_STATE_COMMON; }
                });
            ConversationSequence::getInstance().startConversation();
            }, 40);
        gm.globalVar[GLOBAL_GAME_STATE] = GAME_STATE_CUTSCENE;
        gm.savingVar["ROOM_FALLDOWN_ARRIVE"] = 1;
    }

    AudioManager::getInstance().playSound("SND_FALL_LAND");
}
Room_Falldown::~Room_Falldown() {
    clearEntities();;
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    cv.deleteObject("room_falldown_background");
    
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}