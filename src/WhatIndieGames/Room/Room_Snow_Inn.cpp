#include"AllRooms.h"

Room_Snow_Inn::Room_Snow_Inn() :Room(ROOM_SNOW_INN, NULL, 319 * 2, 240 * 2) {
    roomInit();
}
void Room_Snow_Inn::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_SNOWTOWN"))AudioManager::getInstance().stopBgm(),
        AudioManager::getInstance().playSound("BGM_SNOWTOWN", 1);
    map = ResourceManager::getInstance().getResource("BG_INN");
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    auto& gm = GameManager::getInstance();
    cv.addObject("room_snow_inn", DrawableObject(Animation(map, 1, 1, 1, 319, 240),
        0, 0, RECT({ 0,0,width,height }), 0));


    switch (gm.globalVar[ROOM_ENTRANCE]) {
    case 0:
        gm.entities[ENTITY_MAIN_PLAYER]->setPos({ 260,380 });
        gm.entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    }
    gm.entities[ENTITY_MAIN_PLAYER]->setVisible(true);

    Entity* innkeep = new Entity("Innkeep", 280, 133, { 0,0,16 * 2,34 * 2+20 }, { 0,0,16 * 2,34 * 2 }, Animation(
        ResourceManager::getInstance().getResource("INNKEEP"), 1, 1, 1, 16, 34));
    innkeep->setVisible(1);
    innkeep->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 真是抱歉，小店已经住满了。")); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(innkeep);

    Entity* sofa = new Entity("Sofa", 410, 287, { 0,0,30,100 }, false);
    sofa->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 很旧但很舒服的沙发。")); }
            });
        ConversationSequence::getInstance().startConversation();
        },0);
    addEntity(sofa);


    Entity* airwallTop = new Entity("AirwallTop", 80, 230, { 0,0,width,5 }, false),
        * airwallLeft = new Entity("AirwallLeft", 70, 240, { 0,0,10,200 }, false),
        * airwallBottom = new Entity("AirwallBottom", 70, 330, { 0,0,120,80 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 170, 410, { 0,0,60,70 }, false),
        * airwallBottom2 = new Entity("AirwallBottom2", 330, 410, { 0,0,200,100 }, false),
        * airwallRight = new Entity("AirwallRight", 440, 70, { 0,0,10,height }, false);
        //* airwallRight1 = new Entity("AirwallRight1", 310, 120, { 0,0,100,130 }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallBottom1", airwallBottom1);
    addEntity(airwallBottom2);
    addEntity("AirwallRight", airwallRight);

    Entity* portal = new Entity("Portal", 240, 460, { 0,0,100,10 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 3;
        GameManager::getInstance().setRoom(ROOM_SNOW_TOWN); }, 1);
    addEntity("Portal", portal);



}
Room_Snow_Inn::~Room_Snow_Inn() {
    clearEntities();;
    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
    cv.deleteObject("room_snow_inn");

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}