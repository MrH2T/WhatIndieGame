#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Snow_Crossroads::Room_Snow_Crossroads() :Room(ROOM_SNOW_CROSSROADS, NULL, 19 * TILE_GAME_SIZE, 14 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Snow_Crossroads::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_SNOW"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_SNOW", true);
    calculateMap(ResourceManager::getInstance().getResource("SNOW_TILESET"), 63, 9,
        { {0,0,0,0,0,18,19,19,20,0,0,0,0,0},{0,0,0,1,0,18,19,19,20,0,3,0,0,0},{0,0,0,0,0,18,19,19,20,0,0,0,0,0},{0,1,0,0,0,18,19,19,20,0,0,0,3,0},{0,0,0,0,0,18,19,19,20,0,0,0,0,0},{10,10,10,10,10,12,19,19,13,10,10,10,10,10},{19,19,19,19,19,19,19,19,19,19,19,19,19,19},{19,19,19,19,19,19,19,19,19,19,19,19,19,19},{28,28,28,28,28,21,19,19,22,28,28,28,28,28},{0,0,0,0,0,18,19,19,20,0,0,0,0,0},{0,1,0,0,0,18,19,19,20,0,0,0,0,0},{0,0,0,0,0,18,19,19,20,0,0,0,2,0},{0,0,0,0,0,18,19,19,20,0,0,0,0,0},{0,0,0,1,0,18,19,19,20,0,0,0,0,0} });

    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    Canvas::getInstance().addObject("background_snow_crossroads",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 30,240 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_RIGHT);
        break;
    case 1:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 260,20 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    case 2:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 490,240 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_LEFT);
        break;
    case 3:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 260,490 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);



    Entity* portal1 = new Entity("PortalLeft", 0, 240, { 0,0,5,70 }, true);
    portal1->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 1;
        GameManager::getInstance().setRoom(ROOM_SNOW_TOWN); }, 1);
    addEntity(portal1);

    Entity* portal2 = new Entity("PortalUp", 240, 0, { 0,0,70,5 }, true);
    portal2->setReaction([&]() {

        //hotland
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_SNOW_BRIDGE); 
        }, 1);
    addEntity(portal2);

    Entity* portal3 = new Entity("PortalRight", 550, 240, { 0,0,5,70 }, false);
    portal3->setReaction([&]() {
        //waterfall
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        //GameManager::getInstance().setRoom(ROOM_SNOW_TOWN); 
        }, 1);
    addEntity(portal3);

    Entity* portal4 = new Entity("PortalDown", 240, 550, { 0,0,70,5 }, false);
    portal4->setReaction([&]() {
        //snow plain

        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        //GameManager::getInstance().setRoom(ROOM_SNOW_TOWN); 
        }, 1);
    addEntity(portal4);

    Entity* airwallTop = new Entity("AirwallTop", 0, -5, { 0,0,220,5 }, false),
        * airwallTop1 = new Entity("AirwallTop1", 330, -5, { 0,0,220,5 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,5,220 }, false),
        * airwallLeft1 = new Entity("AirwallLeft1", -10, 320, { 0,0,5,220 }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, 560, { 0,0,220,5 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 330, 560, { 0,0,220,5 }, false),
        * airwallRight = new Entity("AirwallRight", 560, 0, { 0,0,10,220 }, false),  
        * airwallRight1 = new Entity("AirwallRight1", 560, 330, { 0,0,10,220}, false);
    addEntity(airwallTop);
    addEntity(airwallTop1);
    addEntity(airwallLeft);
    addEntity(airwallLeft1);
    addEntity(airwallBottom);
    addEntity(airwallBottom1);
    addEntity(airwallRight);
    addEntity(airwallRight1);

}
Room_Snow_Crossroads::~Room_Snow_Crossroads() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_snow_crossroads");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}