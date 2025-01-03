#include"AllRooms.h"

Room_Snow_House::Room_Snow_House() :Room(ROOM_SNOW_HOUSE, NULL, 219 * 2, 198 * 2) {
    roomInit();
}
void Room_Snow_House::roomInit() {
    if(!AudioManager::getInstance().isPlaying("BGM_SNOWTOWN"))AudioManager::getInstance().stopBgm(),
        AudioManager::getInstance().playSound("BGM_SNOWTOWN",1);
    map = ResourceManager::getInstance().getResource("BG_SNOW_ROOM");
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    auto& gm = GameManager::getInstance();
    cv.addObject("room_snow_house", DrawableObject(Animation(map, 1, 1, 1, 219, 198),
        0, 0, RECT({ 0,0,width,height }), 0));


    switch (gm.globalVar[ROOM_ENTRANCE]) {
    case 0:
        gm.entities[ENTITY_MAIN_PLAYER]->setPos({ 310,320 });
        gm.entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    }
    gm.entities[ENTITY_MAIN_PLAYER]->setVisible(true);


    Entity* airwallTop = new Entity("AirwallTop", 40, 120, { 0,0,350,10 }, false),
        * airwallLeft = new Entity("AirwallLeft", 20, 120, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 20, 360, { 0,0,260,40 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 380, 360, { 0,0,100,40 }, false),
        * airwallRight = new Entity("AirwallRight", 410, 80, { 0,0,10,height }, false),
        * airwallRight1 = new Entity("AirwallRight1", 310, 120, { 0,0,100,130 }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallBottom1", airwallBottom1);
    addEntity("AirwallRight", airwallRight);
    addEntity("AirwallRight1", airwallRight1);

    Entity* bed = new Entity("Bed", 300, 120, { 5,5,65,95 }, true);
    bed->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 一张很舒服的床")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(bed);

    Entity* shelf = new Entity("Shelf", 230, 110, { 5,5,65,35 }, true);
    shelf->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 不应该打开别人的柜子。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(shelf);

    Entity* desk = new Entity("Desk", 150, 100, { 5,5,65,15 }, true);
    desk->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 柜子上放着一些书。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(desk);

    Entity* lamp = new Entity("Lamp", 30, 110, { 5,5,35,35 }, true);
    lamp->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 一台小巧的台灯。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(lamp);



    Entity* portal = new Entity("Portal", 280, 390, { 0,0,100,10 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 4;
        GameManager::getInstance().setRoom(ROOM_SNOW_TOWN); }, 1);
    addEntity("Portal", portal);


    
}
Room_Snow_House::~Room_Snow_House() {
    clearEntities();;
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    cv.deleteObject("room_snow_house");

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}