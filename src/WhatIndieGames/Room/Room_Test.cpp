#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Test::Room_Test():Room(ROOM_TEST,NULL,2*WINDOW_WIDTH,2*WINDOW_HEIGHT) {
    roomInit();
}
void Room_Test::roomInit() {
	//if(!AudioManager::getInstance().isPlaying("BGM_SANS"))AudioManager::getInstance().stopBgm(),AudioManager::getInstance().playSound("BGM_SANS", true);
    map = ResourceManager::getInstance().getResource("BACKGROUND");
    Canvas::getInstance().addObject("background_room_test",
        DrawableObject(
            Animation(map, 1, 1, 1, 240, 160),
            0, 0, RECT({ 0,0,width,height }), 0));

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({500,300});
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);


    Entity* airwallTop = new Entity("AirwallTop", 0, MAIN_PLAYER_HEIGHT, { 0,0,width,10 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, height, { 0,0,width,10 }, false),
        * airwallRight = new Entity("AirwallRight", width, -10, { 0,0,10,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallRight", airwallRight);

    Entity* portal = new Entity("Portal", 500, 200, { 0,0,100,100 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE]=0;
        GameManager::getInstance().setRoom(ROOM_RUINS_TORIEL); }, 1);
    addEntity("Portal",portal);

}
Room_Test::~Room_Test () {
    //MessageBoxA(0,"FUCKYOU","FUCK",0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_room_test");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setSpeedX(0);
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setSpeedY(0);
    EventManager::getInstance().unsubscribe("BATTLE_DIALOG_START", "BattleDialogCheck");
    EventManager::getInstance().unsubscribe("BATTLE_NEW_TURN", "BattleTurnHandler");
    EventManager::getInstance().unsubscribe("BATTLE_END_MERCY", "BattleMercyListen");
    EventManager::getInstance().unsubscribe("BATTLE_END", "BattleEndListen");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}