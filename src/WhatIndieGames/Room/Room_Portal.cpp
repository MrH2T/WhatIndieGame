#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Portal::Room_Portal() :Room(ROOM_PORTAL, NULL, 19 * TILE_GAME_SIZE, 14 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Portal::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_HOT"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_HOT", true);
    calculateMap(ResourceManager::getInstance().getResource("LAB_TILESET"), 12, 6,
        { {-1,7,8,8,8,8,8,8,8,8,8,8,8,9},{-1,7,8,8,8,8,8,8,8,8,8,8,8,9},{-1,7,8,8,8,8,8,8,8,8,31,32,33,9},{-1,7,8,8,8,8,8,8,8,8,19,4,21,9},{-1,13,14,14,14,14,14,14,14,14,25,20,27,15},{-1,0,0,0,0,0,0,0,0,0,0,0,0,0},{-1,0,0,0,0,0,0,0,0,0,0,0,0,0},{-1,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0} });

    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    Canvas::getInstance().addObject("background_lab_talk",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 20,280 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_RIGHT);
        break;
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);




    Entity* portal = new Entity("Portal", 0, 270, { 0,0,5,80 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 2;
        GameManager::getInstance().setRoom(ROOM_RUINS_BATTLE); }, 1);
    addEntity("Portal", portal);

    Entity* airwallTop = new Entity("AirwallTop", 80, 225, { 0,0,320,5 }, false),
        * airwallTop1 = new Entity("AirwallTop1", 0, 225, { 0,0,75,30 }, false),
        //* airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,10,height }, false),
        //* airwallLeft1 = new Entity("AirwallLeft1", 150, 40 * 7 + 10, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 80, 400, { 0,0,320,10 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 0, 360, { 0,0,75,30 }, false),
        //* airwallBottom2 = new Entity("AirwallBottom2", 610, 40 * 7, { 0,0,40 * 4,10 }, false),
        * airwallRight = new Entity("AirwallRight", 410, 0, { 0,0,10,height }, false);


}
Room_Portal::~Room_Portal() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_lab_talk");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}