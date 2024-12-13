#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_First::Room_First() :Room(ROOM_FIRST, NULL, 9*TILE_GAME_SIZE, 8*TILE_GAME_SIZE) {
    roomInit();
}
void Room_First::roomInit() {
    calculateMap(ResourceManager::getInstance().getResource("START_TILESET"), 37, 8,
        { {4,4,4,4,4,4,4,32,33,34,4},{4,4,4,4,4,4,4,40,41,42,4},{4,4,4,4,4,4,4,48,49,50,4},{1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1} },32);

    auto& ev = EventManager::getInstance();
    auto& cv = Canvas::getInstance();
    auto& rs = ResourceManager::getInstance();
    auto& gm = GameManager::getInstance();
    Canvas::getInstance().addObject("background_room_first",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0,0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 80,100 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    }

    Entity* glitch1 = new Entity("Glitch1", 10, 30, { 0,0,90,120 }, { 0,0,90,120 }, Animation(rs.getResource("GREEN_GLITCH"), 1, 1, 1, 192, 256), true);
    Entity* glitch2 = new Entity("Glitch2", 200, 70, { 0,0,90,120 }, { 0,0,90,120 }, Animation(rs.getResource("GREEN_GLITCH"), 1, 1, 1, 192, 256), true);
    Entity* glitch3 = new Entity("Glitch3", 150, 150, { 0,0,90,120 }, { 0,0,90,120 }, Animation(rs.getResource("GREEN_GLITCH"), 1, 1, 1, 192, 256), true);

    addEntity("Glitch1",glitch1);
    addEntity("Glitch2",glitch2);
    addEntity("Glitch3",glitch3);

    Entity* bed=new Entity("Bed",0,80,{0,0,75,115},{0,0,80,120},Animation(subBitmap(rs.getResource("START_TILESET"),{96,128,96+64,128+96}),1,1,1,64,96));
    Entity* computer = new Entity("Computer", 120, 80, {10,10,70,70}, {0,0,80,80},Animation(subBitmap(rs.getResource("START_TILESET"), { 0,32 * 7,32 * 2,32 * 9 }), 1, 1, 1, 64, 64));
    Entity* shelf= new Entity("Shelf",200,40,{0,0,70,110},{0,0,80,120},Animation(subBitmap(rs.getResource("START_TILESET"),{32*3, 32*24,32*5,32*27}),1,1,1,64,96));
    Entity* window= new Entity("Window",300,60,{0,0,70,30},true);
    
    bed->setReaction([&]() {
        Animation niko = Animation(rs.getResource("NIKO_SPEAK_FACE"), 1, 1, 1, 96, 96);
        ConversationSequence::getInstance().setSequence({
            [=]() {Conversation::getInstance().beginConversation(Text(L"* 这是我的床，感觉自己还在梦里。"),niko); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    shelf->setReaction([&]() {
        Animation niko = Animation(rs.getResource("NIKO_SPEAK_FACE"), 1, 1, 1, 96, 96);
        ConversationSequence::getInstance().setSequence({
            [=]() {Conversation::getInstance().beginConversation(Text(L"* 我的书架上只有一些书。"),niko); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    window->setReaction([&]() {
        Animation niko = Animation(rs.getResource("NIKO_SPEAK_FACE"), 1, 1, 1, 96, 96);
        ConversationSequence::getInstance().setSequence({
            [=]() {Conversation::getInstance().beginConversation(Text(L"* 窗外漆黑一片，什么也看不见。"),niko); }
            });
        ConversationSequence::getInstance().startConversation();
        }, 0);
    computer->setReaction([&]() {
        Animation niko = Animation(rs.getResource("NIKO_SPEAK_FACE"), 1, 1, 1, 96, 96),
            nikosurprise=Animation(rs.getResource("NIKO_SURPRISED_FACE"),1,1,1,96,96);
        ConversationSequence::getInstance().setSequence({
            [=]() {Conversation::getInstance().beginConversation(Text(L"* 好奇怪，为什么电脑是开着的。"),niko); },
            [=]() {Conversation::getInstance().beginConversation(Text(L"* 我怎么有种奇怪的感觉..."),nikosurprise);},
            [=]() {
                ConversationSequence::getInstance().stopConversation();
                AudioManager::getInstance().playSound("BGM_STRANGE");
                GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_CUTSCENE;
                GameManager::getInstance().addWaiting([=]() {
                    entities["Glitch1"]->setVisible(1);
                    }, 30);
                GameManager::getInstance().addWaiting([=]() {
                    entities["Glitch2"]->setVisible(1);
                    }, 60);
                GameManager::getInstance().addWaiting([=]() {
                    entities["Glitch3"]->setVisible(1);
                    }
                    , 90);
                GameManager::getInstance().addWaiting([=]() {
                    AudioManager::getInstance().stopBgm();
                    }, 135);
                GameManager::getInstance().addWaiting([=]() {
                    GameManager::getInstance().setRoom(CUTSCENE_FALLING);
                    }, 160);
                }

            });
        ConversationSequence::getInstance().startConversation();
        },0);

    addEntity("Bed", bed);
    addEntity("Computer", computer);
    addEntity("Shelf", shelf);
    addEntity("Window", window);
    
    Entity
        * airwallTop = new Entity("AirwallTop", 0, 95, { 0,0,width,5 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,5,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, height+5, { 0,0,width,5 }, false),
        * airwallRight = new Entity("AirwallRight", width+5, 0, { 0,0,width+5,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallRight", airwallRight);
    gm.addWaiting(
        [&]() {
            Canvas::getInstance().getObject("background_room_first").switchState(DRAW_VISIBLE, 1);
            GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);
            bed->setVisible(1);
            computer->setVisible(1);
            shelf->setVisible(1);
            gm.globalVar[GLOBAL_GAME_STATE] = GAME_STATE_CUTSCENE;
        }
        , 20);

    gm.addWaiting([&]() {
        ConversationSequence::getInstance().setSequence({
            []() {Conversation::getInstance().beginConversation(Text(L"* 我怎么醒了呀。"),
                Animation(ResourceManager::getInstance().getResource("NIKO_SURPRISED_FACE"),1,1,1,96,96)); },
            [&]() {ConversationSequence::getInstance().stopConversation();  gm.globalVar[GLOBAL_GAME_STATE] = GAME_STATE_COMMON; }
            });
        ConversationSequence::getInstance().startConversation();
        }, 40);

}
Room_First::~Room_First() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    AudioManager::getInstance().stopBgm();
    Canvas::getInstance().deleteObject("background_room_first");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}