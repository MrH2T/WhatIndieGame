#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Ruins_Secret::Room_Ruins_Secret() :Room(ROOM_RUINS_SECRET, NULL, 19 * TILE_GAME_SIZE, 14 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Ruins_Secret::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_HOTSPRING"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_HOTSPRING", true);
    calculateMap(ResourceManager::getInstance().getResource("RUINS_TILESET"), 19, 8,
        { {29,22,22,22,22,22,22,22,22,22,22,30},{15,2,2,2,2,2,2,2,2,2,2,13},{15,2,2,2,2,2,2,2,2,2,2,13},{15,10,10,10,10,10,10,10,10,10,10,13},{23,16,16,16,16,16,16,16,16,16,16,13},{16,16,16,80,81,81,82,16,16,16,16,13},{7,16,80,84,84,84,84,81,82,16,16,13},{15,16,83,84,84,84,84,84,84,82,16,13},{15,16,83,84,84,84,84,84,84,85,16,13},{15,16,16,16,16,16,16,16,16,16,16,13},{37,6,6,6,6,6,6,6,6,6,6,38} });

    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    Canvas::getInstance().addObject("background_ruins_secret",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 30,180 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_RIGHT);
        break;
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);



    HBITMAP vane=NULL;
    calculateMap(vane, ResourceManager::getInstance().getResource("RUINS_TILESET"),19, 8, { {90,86,90,90,90,86,90,92,94},{90,86,90,86,90,86,90,92,94},{90,86,90,86,90,90,90,92,94} });
    Entity* vanes = new Entity("Vane", 0, 40, { 0,0,440,120 }, { 0,0,440,120 }, Animation(vane, 1, 1, 1, 360, 120), true);
    vanes->setVisible(1);
    addEntity(vanes);

    Entity* bench = new Entity("Bench", 290, 180, {5,20,75,35},{0,0,80,40},Animation(ResourceManager::getInstance().getResource("BENCH"),1,1,1,183,90));
    bench->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* （似乎不是这个世界的东西。）")); },
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    bench->setVisible(1);
    addEntity(bench);

    Entity* hotspring = new Entity("Hotspring", 80, 240, { 0,0,280,120 }, true);
    hotspring->setReaction([]() {
        GameManager::getInstance().addHP(1000);
        }, 1);
    addEntity(hotspring);

    Entity* portal = new Entity("Portal", 0, 200, { 0,0,5,40 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 1;
        GameManager::getInstance().setRoom(ROOM_RUINS_PUZZLE_2); }, 1);
    addEntity("Portal", portal);

    Entity* airwallTop = new Entity("AirwallTop", 0, 120, { 0,0,450,10 }, false),
        * airwallLeft = new Entity("AirwallLeft", 30, 30, { 0,0,10,170 }, false),
        * airwallLeft1 = new Entity("AirwallLeft1", 30, 250, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 20, 400, { 0,0,450,10 }, false),
        * airwallRight = new Entity("AirwallRight", 450, 0, { 0,0,10,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallLeft1", airwallLeft1);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallRight", airwallRight);

}
Room_Ruins_Secret::~Room_Ruins_Secret() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_ruins_secret");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}