#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Snow_Snowman::Room_Snow_Snowman() :Room(ROOM_SNOW_SNOWMAN, NULL, 19 * TILE_GAME_SIZE, 14 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Snow_Snowman::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_SNOWTOWN"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_SNOWTOWN", true);
    calculateMap(ResourceManager::getInstance().getResource("SNOW_TILESET"), 63, 9,
        { {171,172,173,171,172,173,171,172,173},{180,181,182,180,181,182,180,181,182},{189,190,191,189,190,191,189,190,191},{198,199,200,198,199,200,198,199,200},{0,9,10,10,10,10,10,11,0},{0,18,19,19,19,19,19,20,0},{0,18,19,19,19,19,19,20,0},{0,27,28,28,28,28,28,29,0},{0,0,0,0,0,0,0,0,0},{-1,-1,-1,-1,0},{-1,-1,-1,-1,0} });

    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    Canvas::getInstance().addObject("background_snow_snowtown",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 160,360 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);

    Entity* snowman = new Entity("Snowman", 165, 190, { 0,30,38,60 }, { 0, 0, 38, 60 }, Animation(rs.getResource("SNOWMAN"), 1, 1, 1, 19, 30));
    snowman->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 这里孤零零地站着一个雪人。")); },
            []() {Conversation::getInstance().beginConversation(Text(L"* 看样子很久没人来看它了。")); },
            []() {
                if (GameManager::getInstance().savingVar.find("MEET_SNOWMAN") == GameManager::getInstance().savingVar.end()) {
                Conversation::getInstance().beginConversation(Text(L"* 但是你在旁边的地上找到了 10G。"));
                }
                else ConversationSequence::getInstance().stopConversation();
            },
            []() {
                ConversationSequence::getInstance().stopConversation();
                GameManager::getInstance().addGold(10);
                GameManager::getInstance().savingVar["MEET_SNOWMAN"] = 1;
            }
            }
        );
        ConversationSequence::getInstance().startConversation();

        }, 0);

    snowman->setVisible(1);
    addEntity(snowman);



    Entity* portal = new Entity("Portal", 160, 420, { 0,0,40,5 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 2;
        GameManager::getInstance().setRoom(ROOM_SNOW_TOWN); }, 1);
    addEntity("Portal", portal);

    Entity* airwallTop = new Entity("AirwallTop", 0, 130, { 0,0,width,5 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, 360, { 0,0,150,70 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 210, 360, { 0,0,150,70 }, false),
        * airwallRight = new Entity("AirwallRight", width+5, 0, { 0,0,10,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallBottom1", airwallBottom1);
    addEntity("AirwallRight", airwallRight);

}
Room_Snow_Snowman::~Room_Snow_Snowman() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_snow_snowtown");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}