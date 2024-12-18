#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Hot_Entrance::Room_Hot_Entrance() :Room(ROOM_HOT_ENTRANCE, NULL, 19 * TILE_GAME_SIZE, 14 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Hot_Entrance::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_HOT"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_HOT", true);
    calculateMap(ResourceManager::getInstance().getResource("HOT_TILESET"), 20, 18,
        { 
        {-1},
        {-1},
        {-1},
        {-1},
        {152,153,153,153,153,153,153,153,153,153,153,153,153,153,153,153,153,153,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        {3,4,4,4,4,4,4,4,4,4,4,4,58,4,4,4,4,4},
        {3,59,4,4,4,4,4,58,4,4,4,4,4,4,4,4,4,4},
        {3,4,4,4,4,4,4,4,4,4,60,4,4,4,4,4,4,4},
        {3,4,4,4,22,22,22,22,22,22,22,22,22,22,22,22,22,22},
        {3,4,4,5,37,37,37,37,37,37,37,37,37,37,37,37,37,37},
        {3,4,4,5,37,37,37,37,37,37,37,37,37,37,37,37,37,37},
        {3,4,4,5},
        {3,4,4,5},
        {3,4,4,5},
        {3,4,4,5},
        {3,4,4,5},
        {3,4,4,5},
        {3,4,4,5},
        {21,22,22,23},
        {37,126,127,37},
        {37,126,144,37},
        {-1,126,127},
        {-1,126,144},
        {-1,127,127},
        {-1,144,127} });

    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    Canvas::getInstance().addObject("background_hot_entrance",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 60,920 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    case 1:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 530,240 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_LEFT);
        break;
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);

    Entity* lab = new Entity("Lab", 470, 0, { 0,0,175 * 2,192 * 2 }, { 0,0,175 * 2,192 * 2 }, Animation(rs.getResource("LAB_ENTRANCE"), 1, 1, 1, 175, 192));
    lab->setVisible(1);
    lab->setPassable(1);
    addEntity(lab);


    Entity* portal1 = new Entity("Portal1", 50, 980, { 0,0,70,5 }, true);
    portal1->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 1;
        GameManager::getInstance().setRoom(ROOM_SNOW_BRIDGE); }, 1);
    addEntity(portal1);

    Entity* portal2 = new Entity("Portal2", 590, 230, { 0,0,30,60 }, true);
    portal2->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_LAB_TALK); }, 1);
    addEntity(portal2);

    Entity* stone = new Entity("Stone", 40, 240, { 5,5,35,35 }, false);
    stone->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 你不该指望石头会有什么反应。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(stone);


    Entity* airwallTop = new Entity("AirwallTop", 0, 155, { 0,0,500,5 }, false),
        * airwallTop1 = new Entity("AirwallTop1", 500, 160, { 0,0,90,75 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,5,760 }, false),
        * airwallLeft1 = new Entity("AirwallLeft1", 30, 760, { 0,0,5,220 }, false),
        * airwallBottom = new Entity("AirwallBottom", 160, 360, { 0,0,600,400 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 640, 200, { 0,0,220,300 }, false),
        * airwallRight = new Entity("AirwallRight", 125, 760, { 0,0,10,220 }, false);
    addEntity(airwallTop);
    addEntity(airwallTop1);
    addEntity(airwallLeft);
    addEntity(airwallLeft1);
    addEntity(airwallBottom);
    addEntity(airwallBottom1);
    addEntity(airwallRight);

}
Room_Hot_Entrance::~Room_Hot_Entrance() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_hot_entrance");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}