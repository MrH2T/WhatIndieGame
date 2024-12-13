#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Ruins_Candy::Room_Ruins_Candy() :Room(ROOM_RUINS_CANDY, NULL, 19 * TILE_GAME_SIZE, 14 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Ruins_Candy::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_RUINS"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_RUINS", true);
    calculateMap(ResourceManager::getInstance().getResource("RUINS_TILESET"), 19, 8,
        { {-1,29,22,22,22,22,22,22,22,22,30},{-1,15,57,57,57,57,57,57,57,57,13},{-1,15,57,57,57,57,57,57,57,57,13},{-1,15,67,68,68,68,68,68,68,69,13},{22,23,83,76,76,76,76,76,76,85,13},{2,4,83,84,84,84,84,84,84,85,13},{10,12,16,16,16,16,16,16,16,16,13},{16,16,16,16,16,16,24,25,16,16,13},{16,16,16,16,16,16,32,33,16,16,13},{6,7,16,16,16,16,16,16,16,16,13},{-1,15,80,81,81,81,81,81,81,82,13},{-1,15,83,84,84,84,84,84,84,85,13},{-1,37,6,6,6,6,6,6,6,6,38} });

    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    Canvas::getInstance().addObject("background_ruins_candy",
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

    Entity* candydish = new Entity("Candydish", 257, 290, {0,27,40,54}, { 0, 0, 40, 54 }, Animation(rs.getResource("CANDYDISH"), 1, 1, 1, 20, 27));
    candydish->setReaction([]() {
        ConversationSequence::getInstance().setSequence(ConvSeq({
            [=]() {
                Conversation::getInstance().beginConversation(Text(L"* 怪物糖果，一人一颗。")); },
            [=]() {Conversation::getInstance().beginConversation(Text(L"              要拿一颗吗？"),
                Conversation::Choice(ChoiceItem({
                    Text(L"拿一颗"),
                    Text(L"不拿")
                    }),[](int res) {GameManager::getInstance().globalVar["Choose_Temp"] = res + 1; })); },
            [=]() {
                if (GameManager::getInstance().globalVar["Choose_Temp"] == 1) {
                    if (GameManager::getInstance().inventory.size() == INVENTORY_SIZE) {
                        Conversation::getInstance().beginConversation(Text(L"* 你拿不下了。"));
                    }
                    else {
                        if (GameManager::getInstance().savingVar.find("RUINS_CANDY_GET") == GameManager::getInstance().savingVar.end()) {
                            Conversation::getInstance().beginConversation(Text(L"* 你拿了一颗糖。"));
                            GameManager::getInstance().savingVar["RUINS_CANDY_GET"] = 1;
                        }
                        else {
                            Conversation::getInstance().beginConversation(Text(L"* 你拿了一颗糖，即使你的良心拒绝了。"));
                            GameManager::getInstance().savingVar["RUINS_CANDY_GET"] += 1;
                        }
                        GameManager::getInstance().addItem("怪物糖果");
                    }
                }
                else if (GameManager::getInstance().globalVar["Choose_Temp"] == 2) {
                    ConversationSequence::getInstance().stopConversation();
                }
            } }
        ));
        ConversationSequence::getInstance().startConversation();

        },0);
    
    candydish->setVisible(1);
    addEntity("Candydish",candydish);


    
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
        * airwallRight = new Entity("AirwallRight", 410,0, { 0,0,10,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallTop1", airwallTop1);
    //addEntity("AirwallLeft", airwallLeft);
    //addEntity("AirwallLeft1", airwallLeft1);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallBottom1", airwallBottom1);
    //addEntity("AirwallBottom2", airwallBottom2);
    addEntity("AirwallRight", airwallRight);

}
Room_Ruins_Candy::~Room_Ruins_Candy() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_ruins_candy");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}