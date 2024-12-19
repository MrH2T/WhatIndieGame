#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Final::Room_Final() :Room(ROOM_FINAL, NULL, 500, 500/1.4) {
    roomInit();
}
void Room_Final::roomInit() {
    AudioManager::getInstance().stopBgm();

    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    map = rs.getResource("FINALROOM");
    Canvas::getInstance().addObject("background_final",
        DrawableObject(
            Animation(map, 1, 1, 1, 357, 261),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 140,150 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_UP);
        break;
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);
    Entity* bed = new Entity("Bed", 0, 80, { 0,0,75,115 });
    Entity* computer = new Entity("Computer", 120, 140, { 10,10,70,30 });
    Entity* shelf = new Entity("Shelf", 220, 60, { 0,0,90,110 });
    Entity* window = new Entity("Window", 340, 100, { 0,0,80,30 }, true);

    bed->setReaction([&]() {
        Animation niko = Animation(rs.getResource("NIKO_SPEAK_FACE"), 1, 1, 1, 96, 96);
        ConversationSequence::getInstance().setSequence({
            [=]() {Conversation::getInstance().beginConversation(Text(L"* 我的床，很舒适的一张床。"),niko); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    shelf->setReaction([&]() {
        Animation niko = Animation(rs.getResource("NIKO_SPEAK_FACE"), 1, 1, 1, 96, 96);
        ConversationSequence::getInstance().setSequence({
            [=]() {Conversation::getInstance().beginConversation(Text(L"* 书架上放满了我喜欢的书。"),niko); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    window->setReaction([&]() {
        Animation niko = Animation(rs.getResource("NIKO_SPEAK_FACE"), 1, 1, 1, 96, 96);
        ConversationSequence::getInstance().setSequence({
            [=]() {Conversation::getInstance().beginConversation(Text(L"* 阳光明媚。"),niko); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    computer->setReaction([&]() {
        Animation niko = Animation(rs.getResource("NIKO_SPEAK_FACE"), 1, 1, 1, 96, 96);
        ConversationSequence::getInstance().setSequence({
            [=]() {Conversation::getInstance().beginConversation(Text(L"* 是关着的。"),niko); },
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    addEntity(bed);
    addEntity(shelf);
    addEntity(window);
    addEntity(computer);



    Entity* portal = new Entity("Portal", 220, 340, { 0,0,40,5 }, true);
    portal->setReaction([&]() {
        ConversationSequence::getInstance().setSequence({
            [=]() {Conversation::getInstance().beginConversation(Text(L"            要结束游戏吗?"),
                Conversation::Choice(ChoiceItem({
                    Text(L"再等等"),
                    Text(L"确定")
                    }),[](int res) {GameManager::getInstance().globalVar["Choose_Temp"] = res + 1; })
            ); },
            [=]() {
                if (GameManager::getInstance().globalVar["Choose_Temp"] == 1) {
                    ConversationSequence::getInstance().stopConversation();
                }
                else if (GameManager::getInstance().globalVar["Choose_Temp"] == 2) {
                    ConversationSequence::getInstance().stopConversation();
                    GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
                    GameManager::getInstance().setRoom(CUTSCENE_CAST,GAME_STATE_CUTSCENE);

                }
            }
            });
        ConversationSequence::getInstance().startConversation();
        }, 1);
    addEntity("Portal", portal);

    Entity* airwallTop = new Entity("AirwallTop", 0, 125, { 0,0,500,5 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, 350, { 0,0,500,30 }, false),
        * airwallRight = new Entity("AirwallRight", 505, 0, { 0,0,10,height }, false);

    addEntity(airwallTop);
    addEntity(airwallLeft);
    addEntity(airwallBottom);
    addEntity(airwallRight);
}
Room_Final::~Room_Final() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_final");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}