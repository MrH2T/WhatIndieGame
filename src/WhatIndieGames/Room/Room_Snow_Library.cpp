#include"AllRooms.h"

Room_Snow_Library::Room_Snow_Library() :Room(ROOM_SNOW_LIBRARY, NULL, 320 * 2, 240 * 2) {
    roomInit();
}
void Room_Snow_Library::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_SNOWTOWN"))AudioManager::getInstance().stopBgm(),
        AudioManager::getInstance().playSound("BGM_SNOWTOWN", 1);
    map = ResourceManager::getInstance().getResource("BG_LIBRARY");
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    auto& gm = GameManager::getInstance();
    cv.addObject("room_snow_library", DrawableObject(Animation(map, 1, 1, 1, 320, 240),
        0, 0, RECT({ 0,0,width,height }), 0));


    switch (gm.globalVar[ROOM_ENTRANCE]) {
    case 0:
        gm.entities[ENTITY_MAIN_PLAYER]->setPos({ 300,390 });
        gm.entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    }
    gm.entities[ENTITY_MAIN_PLAYER]->setVisible(true);


    Entity* shelf1 = new Entity("Shelf1", 80, 130, { 0,0,80,10 }, false);
    shelf1->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 上面是关于数学的书（看不懂）。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(shelf1);

    Entity* shelf2 = new Entity("Shelf2", 160, 130, { 0,0,80,10 }, false);
    shelf2->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 上面是关于地下世界的书。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(shelf2);

    Entity* shelf3 = new Entity("Shelf3", 240, 130, { 0,0,80,10 }, false);
    shelf3->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 上面是关于雪糕的书。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(shelf3);

    Entity* shelf4 = new Entity("Shelf4", 320, 130, { 0,0,80,10 }, false);
    shelf4->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 上面是关于电脑的书。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(shelf4);

    Entity* shelf5 = new Entity("Shelf5", 400, 130, { 0,0,80,10 }, false);
    shelf5->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 上面是关于三角符文的书(那是什么?)。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(shelf5);

    Entity* shelf6 = new Entity("Shelf6", 480, 130, { 0,0,80,10 }, false);
    shelf6->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 被梯子挡住了。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(shelf6);


    Entity* airwallTop = new Entity("AirwallTop", 50, 100, { 0,0,520,50 }, false),
        * airwallLeft = new Entity("AirwallLeft", 65, 160, { 0,0,10,height }, false),
        * airwallLeft1 = new Entity("AirwallLeft1", 70, 250, { 0,0,160,200 }, false),
        * airwallBottom = new Entity("AirwallBottom", 230, 410, { 0,0,40,100 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 365, 410, { 0,0,400,80 }, false),
        * airwallRight = new Entity("AirwallRight", 565, 80, { 0,0,10,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity(airwallLeft1);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallBottom1", airwallBottom1);
    addEntity("AirwallRight", airwallRight);

    Entity* portal = new Entity("Portal", 280, 470, { 0,0,100,10 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 6;
        GameManager::getInstance().setRoom(ROOM_SNOW_TOWN); }, 1);
    addEntity("Portal", portal);



}
Room_Snow_Library::~Room_Snow_Library() {
    clearEntities();;
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    cv.deleteObject("room_snow_library");

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}