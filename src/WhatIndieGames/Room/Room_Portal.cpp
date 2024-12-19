#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Portal::Room_Portal() :Room(ROOM_PORTAL, NULL, WINDOW_WIDTH-16, WINDOW_HEIGHT-32) {
    roomInit();
}
void Room_Portal::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_PORTAL"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_PORTAL", true);
    
    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 440,550 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);

    std::vector<Animation> colors = { Animation(subBitmap(rs.getResource("FINAL_COLORS"),{0,0,20,20}), 1, 1, 1, 20, 20),
               Animation(subBitmap(rs.getResource("FINAL_COLORS"),{20,0,40,20}), 1, 1, 1, 20, 20),
                Animation(subBitmap(rs.getResource("FINAL_COLORS"),{40,0,60,20}), 1, 1, 1, 20, 20),
                 Animation(subBitmap(rs.getResource("FINAL_COLORS"),{40,0,60,20}), 1, 1, 1, 20, 20)};

    Entity* background = new Entity("Background", 0, 0, { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT }, {0,0,WINDOW_WIDTH,WINDOW_HEIGHT},colors,colors);
    background->setLayer(0);
    background->setPassable(1);
    background->setVisible(1);
    background->setDirection(1);
    addEntity(background);

    Entity* ground = new Entity("Ground", WINDOW_WIDTH / 2 - 120, 300, { 0,0,240,340 }, { 0,0,240,340 }, colors, colors);
    ground->setLayer(1);
    ground->setPassable(1);
    ground->setVisible(1);
    ground->setDirection(0);
    addEntity(ground);

    Entity* portal = new Entity("Portal", WINDOW_WIDTH / 2 - 30, 0, { 0,0,60,300 }, { 0,0,60,300 }, colors, colors);
    portal->setDirection(2);
    portal->setPassable(0);
    portal->setVisible(1);
    portal->setReaction([=]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 好像你的灵魂本身正在闪耀光芒。")); },
            [=]() {
                ConversationSequence::getInstance().stopConversation();
                GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_CUTSCENE;
                AudioManager::getInstance().stopBgm();
                AudioManager::getInstance().playSound("SND_USEPORTAL");
                GameManager::getInstance().addWaiting(
                    [=]() {
                        background->setDirection(2);
                    }, 100);
                GameManager::getInstance().addWaiting(
                    [=]() {
                        ground->setDirection(2);
                    }, 160);
                GameManager::getInstance().addWaiting(
                    []() {
                        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
                        GameManager::getInstance().setRoom(ROOM_FINAL);
                    }, 280);
            }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(portal);


    Entity* airwallTop = new Entity("AirwallTop", 330, 290, { 0,0,320,5 }, false),
        * airwallLeft = new Entity("AirwallLeft", 325, 0, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 330, 630, { 0,0,320,10 }, false),
        * airwallRight = new Entity("AirwallRight", 580, 0, { 0,0,10,height }, false);
    addEntity(airwallTop);
    addEntity(airwallLeft);
    addEntity(airwallBottom);
    addEntity(airwallRight);


    GameManager::getInstance().addWaiting([]() {
        
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 看来那就是终点了。"),
                Animation(ResourceManager::getInstance().getResource("NIKO_SPEAK_FACE"),1,1,1,96,96)); },
            []() {ConversationSequence::getInstance().stopConversation();
                GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_COMMON; }
            });
        ConversationSequence::getInstance().startConversation();
        
        }, 40);

}
Room_Portal::~Room_Portal() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}