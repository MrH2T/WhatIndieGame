#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Test_1::Room_Test_1():Room(ROOM_TEST_2,NULL,32*TILE_GAME_SIZE, 18 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Test_1::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_SNOWTOWN"))
    {
        AudioManager::getInstance().stopBgm();
        AudioManager::getInstance().playSound("BGM_SNOWTOWN", true);
    }
    calculateMap(ResourceManager::getInstance().getResource("TEST_ROOM_TILESET"),4,5,
        { {{5,6,6,6,6,6,8,11,11,12,0,0,0,0,0,0,0,0,0,0,0,0,0,10,11,11,11,12,0,0,0,0},{10,11,11,11,11,11,11,11,11,12,0,2,0,0,0,0,0,0,0,0,0,0,2,10,11,14,16,17,0,0,0,0},{15,16,16,13,11,11,11,11,11,12,0,0,0,0,1,0,0,0,2,0,0,0,0,10,11,12,2,0,0,0,0,0},{1,0,0,10,11,14,13,11,11,12,0,0,0,0,0,0,0,0,0,2,0,0,0,10,11,12,0,2,0,3,0,0},{0,0,2,15,16,17,10,11,11,12,0,0,0,2,0,0,0,0,0,0,0,0,0,10,11,12,0,0,0,0,0,0},{0,3,0,0,0,2,10,11,11,12,0,0,0,0,0,0,0,0,0,0,0,2,0,10,11,12,0,0,0,0,0,2},{6,6,6,6,6,6,8,11,11,9,6,6,6,6,6,6,8,11,11,9,6,6,6,8,11,9,6,6,6,6,6,6},{11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},{11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},{16,16,16,16,16,16,13,11,11,14,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16},{0,0,0,0,0,0,10,11,11,12,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,0},{0,3,0,1,0,0,10,11,11,12,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0},{0,0,0,0,0,0,10,11,11,12,0,0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0,0,0},{0,0,2,0,0,1,10,11,11,12,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,10,11,11,9,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,0,2,0,0},{0,1,0,0,0,0,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,0,0,0,0},{0,0,1,3,0,0,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,0,0,2,0},{0,0,0,0,0,0,15,16,16,16,16,16,16,16,16,16,16,13,11,11,14,16,16,16,16,16,16,17,0,0,0,0}}
        });

    Canvas::getInstance().addObject("background_room_test_1",
        DrawableObject(
            Animation(map, 1, 1, 1, width,height),
            0, 0, RECT({ 0,0,width,height }), 0));

    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 19 * 40,9 * 40 - 10 });
        break;
    case 1:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 30,TILE_GAME_SIZE * 7 + 10 });
        break;
    default:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 19 * 40,9 * 40 - 10 });
        break;
    }
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);
    
    Entity* house = new Entity("House", 600-8, 0+5, { 0,100,256,236 } ,{0,0, 256,236 },
        Animation(ResourceManager::getInstance().getResource("HOUSE"),1,1,1,128,118));
    house->setVisible(true);
    house->setDrawYPrioBias(100);
    addEntity("House",house);


    Entity* airwallTop = new Entity("AirwallTop", 0, MAIN_PLAYER_HEIGHT-30, { 0,0,width,10 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, height, { 0,0,width,10 }, false),
        * airwallRight = new Entity("AirwallRight", width, -10, { 0,0,10,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallRight", airwallRight);

    /*Entity* portal = new Entity("Portal", 500, 200, { 0,0,100,100 }, true);
    portal->setReaction([&]() {GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 100,600 }); }, 1);
    addEntity("Portal",portal);*/
    Entity* portal = new Entity("Portal", 0, TILE_GAME_SIZE*7, { 0,0,10,TILE_GAME_SIZE*2 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().setRoom(ROOM_TEST_2); 
        }, 1);
    addEntity("Portal", portal);

    Entity* portal1 = new Entity("PortalHouse", 600 - 8 +128, 236,{ 0,0,2*TILE_GAME_SIZE,10 }, true);
    portal1->setReaction([&]() {

        GameManager::getInstance().setRoom(ROOM_TEST);
        }, 1);
    addEntity("PortalHouse", portal1);
}
Room_Test_1::~Room_Test_1() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_room_test_1");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}