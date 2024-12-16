#include"AllRooms.h"

Room_Snow_Sanshouse::Room_Snow_Sanshouse() :Room(ROOM_SNOW_SANSHOUSE, NULL, 240 * 2, 240 * 2) {
    roomInit();
}
void Room_Snow_Sanshouse::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_SANS"))AudioManager::getInstance().stopBgm(),
        AudioManager::getInstance().playSound("BGM_SANS", 1);
    map = ResourceManager::getInstance().getResource("BG_SANSROOM");
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    auto& gm = GameManager::getInstance();
    cv.addObject("room_snow_sanshouse", DrawableObject(Animation(map, 1, 1, 1, 240, 240),
        0, 0, RECT({ 0,0,width,height }), 0));


    switch (gm.globalVar[ROOM_ENTRANCE]) {
    case 0:
        gm.entities[ENTITY_MAIN_PLAYER]->setPos({ 160,400 });
        gm.entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    }
    gm.entities[ENTITY_MAIN_PLAYER]->setVisible(true);

    Entity* desk = new Entity("Desk", 90, 160, { 5,5,95,45 }, false);
    desk->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 一张桌子，上面有个台灯。")); },
            []() {Conversation::getInstance().beginConversation(Text(L"* 台灯里夹着一本量子力学的书(什么?)。")); },
            []() {Conversation::getInstance().beginConversation(Text(L"* 书里又有一个台灯。")); },
            []() {Conversation::getInstance().beginConversation(Text(L"* 你决定停下。")); }
            });
        ConversationSequence::getInstance().startConversation();
        },0);
    addEntity(desk);

    Entity* bed = new Entity("Bed", 320, 170, { 5,5,65,85 }, false);
    bed->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 床，或者说床垫。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(bed);

    Entity* sock = new Entity("sock", 80, 340, { 0,0,45,45 }, true);
    sock->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 袜子。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(sock);

    Entity* sans = new Entity("Sans", 220, 150, { 0,30,23 * 2,30 * 2 }, { 0, 0, 23 * 2,30 * 2 }, 
        firstColumn(ResourceManager::getInstance().getResource("SANS_IMAGES"), 23, 30),
        groupBy4(ResourceManager::getInstance().getResource("SANS_IMAGES"), 23, 30));
    sans->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK");
                Conversation::getInstance().beginConversation(Text(L"* 嘿。"),
                Animation(ResourceManager::getInstance().getResource("SANS_FACE"),1,1,1,32,32)); },
            []() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK");
                Conversation::getInstance().beginConversation(Text(L"* 技术上说，你这属于私闯民宅。"),
                Animation(ResourceManager::getInstance().getResource("SANS_FACE"),1,1,1,32,32)); },
            []() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK");
                Conversation::getInstance().beginConversation(Text(L"* 但骷髅已经挂了."),
                Animation(ResourceManager::getInstance().getResource("SANS_FACE"),1,1,1,32,32));},
            []() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK");
                Conversation::getInstance().beginConversation(Text(L"* 你真走运。"),
                Animation(ResourceManager::getInstance().getResource("SANS_FACE"),1,1,1,32,32)); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    sans->setVisible(1);
    addEntity(sans);


    Entity* airwallTop = new Entity("AirwallTop", 70, 150, { 0,0,350,10 }, false),
        * airwallLeft = new Entity("AirwallLeft", 70, 140, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 60, 400, { 0,0,60,80 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 225, 400, { 0,0,200,80 }, false),
        * airwallRight = new Entity("AirwallRight", 390, 150, { 0,0,10,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallBottom1", airwallBottom1);
    addEntity("AirwallRight", airwallRight);

    Entity* portal = new Entity("Portal", 140, 470, { 0,0,100,10 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 5;
        GameManager::getInstance().setRoom(ROOM_SNOW_TOWN); }, 1);
    addEntity("Portal", portal);



}
Room_Snow_Sanshouse::~Room_Snow_Sanshouse() {
    clearEntities();;
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    cv.deleteObject("room_snow_sanshouse");

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}