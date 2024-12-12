#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Ruins_Puzzle::Room_Ruins_Puzzle() :Room(ROOM_RUINS_PUZZLE, NULL, 19 * TILE_GAME_SIZE, 14 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Ruins_Puzzle::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_RUINS"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_RUINS", true);
    calculateMap(ResourceManager::getInstance().getResource("RUINS_TILESET"), 19, 8,
        { {22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22},
           {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,44,45,2,2,2,2,2,2,2,2,2,2,2},
        {10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,10,10,10},
        {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,16,8,8,8},
        {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,16,8,8,8},
        {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,16,8,8,8},
        {134,134,134,7,8,8,8,8,8,8,8,8,8,8,8,5,6,6,6},
        {-1,-1,-1,143,8,8,8,8,8,8,8,8,8,8,8,13},
        {-1,-1,-1,143,8,8,8,8,8,8,8,8,8,8,8,13},
        {-1,-1,-1,15,80,81,81,81,81,81,81,81,81,81,82,13},
        {-1,-1,-1,15,83,84,84,84,84,84,84,84,84,84,85,13},
        {-1,-1,-1,15,83,84,84,84,84,84,84,84,84,84,85,13},
        {-1,-1,-1,15,83,84,84,84,84,84,84,84,84,84,85,13},
        {-1,-1,-1,37,6,6,6,6,6,6,6,6,6,6,6,38} });

    Canvas::getInstance().addObject("background_ruins_puzzle",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 60,180 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_RIGHT);
        break;
    case 1:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 670,180 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_LEFT);
        break;
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);

    Entity* tipboard = new Entity("Tipboard", 240,110,{0,0,70,30},false);
    tipboard->setReaction([]() {
        ConversationSequence::getInstance().setSequence({
            []() {
                Conversation::getInstance().beginConversation(Text(L"* 当所有红花变成黄花，门就会打开。"));
            } });
        ConversationSequence::getInstance().startConversation();
        }
        , 0);
    addEntity("Tipboard", tipboard);

    Animation tileset= Animation(ResourceManager::getInstance().getResource("RUINS_TILESET"), 19*8,19,8,20,20);
    HBITMAP board = tileset.getFrame(119),
        yellow=subBitmap(ResourceManager::getInstance().getResource("RUINS_TILESET"),{20*6,20*12+10,20*7,20*13+10}), red = tileset.getFrame(97);
    //01001
    std::vector<Animation> anim = { Animation(red, 1, 1, 1, 20, 20), Animation(yellow, 1, 1, 1, 20, 20) ,
     Animation(yellow, 1, 1, 1, 20, 20) , Animation(yellow, 1, 1, 1, 20, 20) };
    
    Entity* flower1 = new Entity("Flower1", 200, 440, { 5,5,35,35 }, { 0,0,40,40 }, anim, anim);
    Entity* flower2 = new Entity("Flower2", 280, 440, { 5,5,35,35 }, { 0,0,40,40 }, anim, anim);
    Entity* flower3 = new Entity("Flower3", 360, 440, { 5,5,35,35 }, { 0,0,40,40 }, anim, anim);
    Entity* flower4 = new Entity("Flower4", 440, 440, { 5,5,35,35 }, { 0,0,40,40 }, anim, anim);
    Entity* flower5 = new Entity("Flower5", 520, 440, { 5,5,35,35 }, { 0,0,40,40 }, anim, anim);
    if (GameManager::getInstance().savingVar.find("RUINS_PUZZLE_SOLVED") == GameManager::getInstance().savingVar.end()) {
        flower1->setDirection(DIRECTION_DOWN),
        flower2->setDirection(DIRECTION_RIGHT),
        flower3->setDirection(DIRECTION_DOWN),
        flower4->setDirection(DIRECTION_DOWN),
        flower5->setDirection(DIRECTION_RIGHT);
    }
    else {
        flower1->setDirection(DIRECTION_RIGHT),
            flower2->setDirection(DIRECTION_RIGHT),
            flower3->setDirection(DIRECTION_RIGHT),
            flower4->setDirection(DIRECTION_RIGHT),
            flower5->setDirection(DIRECTION_RIGHT);
    }
    flower1->setVisible(1);
    flower2->setVisible(1);
    flower3->setVisible(1);
    flower4->setVisible(1);
    flower5->setVisible(1);
    addEntity("Flower1", flower1);
    addEntity("Flower2", flower2);
    addEntity("Flower3", flower3);
    addEntity("Flower4", flower4);
    addEntity("Flower5", flower5);

    Entity* board1 = new Entity("Board1", 200, 320, { 5,5,35,35 }, { 0,0,40,40 },Animation(board,1,1,1,20,20),true);
    Entity* board2 = new Entity("Board2", 280, 320, { 5,5,35,35 }, { 0,0,40,40 },Animation(board,1,1,1,20,20),true);
    Entity* board3 = new Entity("Board3", 360, 320, { 5,5,35,35 }, { 0,0,40,40 },Animation(board,1,1,1,20,20),true);
    Entity* board4 = new Entity("Board4", 440, 320, { 5,5,35,35 }, { 0,0,40,40 },Animation(board,1,1,1,20,20),true);
    Entity* board5 = new Entity("Board5", 520, 320, { 5,5,35,35 }, { 0,0,40,40 },Animation(board,1,1,1,20,20),true);
    board1->setVisible(true), board1->setLayer(1);
    board2->setVisible(true), board2->setLayer(1);
    board3->setVisible(true), board3->setLayer(1);
    board4->setVisible(true), board4->setLayer(1);
    board5->setVisible(true), board5->setLayer(1);
    board1->setReaction([=]() {
        if (GameManager::getInstance().savingVar.find("RUINS_PUZZLE_SOLVED") == GameManager::getInstance().savingVar.end()) {
            AudioManager::getInstance().playSound("SND_SPIKEOPEN");
            flower1->setDirection(3 - flower1->getDirection());
            flower2->setDirection(3 - flower2->getDirection());
        }
        }, 1);
    board2->setReaction([=]() {
        if (GameManager::getInstance().savingVar.find("RUINS_PUZZLE_SOLVED") == GameManager::getInstance().savingVar.end()) {
            AudioManager::getInstance().playSound("SND_SPIKEOPEN");
            flower1->setDirection(3 - flower1->getDirection());
            flower2->setDirection(3 - flower2->getDirection());
            flower3->setDirection(3 - flower3->getDirection());
        }
        }, 1);
    board3->setReaction([=]() {
        if (GameManager::getInstance().savingVar.find("RUINS_PUZZLE_SOLVED") == GameManager::getInstance().savingVar.end()) {
            AudioManager::getInstance().playSound("SND_SPIKEOPEN");
            flower2->setDirection(3 - flower2->getDirection());
            flower3->setDirection(3 - flower3->getDirection());
            flower4->setDirection(3 - flower4->getDirection());
        }
        }, 1);
    board4->setReaction([=]() {
        if (GameManager::getInstance().savingVar.find("RUINS_PUZZLE_SOLVED") == GameManager::getInstance().savingVar.end()) {
            AudioManager::getInstance().playSound("SND_SPIKEOPEN");
            flower3->setDirection(3 - flower3->getDirection());
            flower4->setDirection(3 - flower4->getDirection());
            flower5->setDirection(3 - flower5->getDirection());
        }
        }, 1);
    board5->setReaction([=]() {
        if (GameManager::getInstance().savingVar.find("RUINS_PUZZLE_SOLVED") == GameManager::getInstance().savingVar.end()) {
            AudioManager::getInstance().playSound("SND_SPIKEOPEN");
            flower4->setDirection(3 - flower4->getDirection());
            flower5->setDirection(3 - flower5->getDirection());
        }
        }, 1);
    
    addEntity("Board1",board1);
    addEntity("Board2",board2);
    addEntity("Board3",board3);
    addEntity("Board4",board4);
    addEntity("Board5",board5);


    Entity* airwallTop = new Entity("AirwallTop", 0, MAIN_PLAYER_HEIGHT - 5, { 0,0,width,105 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,10,height }, false),
        * airwallLeft1 = new Entity("AirwallLeft1", 150, 40*7+10, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, 400, { 0,0,width,10 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 0, 40*7, { 0,0,40*4-10,10 }, false),
        * airwallBottom2 = new Entity("AirwallBottom2", 610, 40*7, { 0,0,40*4,10 }, false),
        * airwallRight = new Entity("AirwallRight", width, -10, { 0,0,10,height }, false),
        * airwallRight1 = new Entity("AirwallRight1", 610, 40*7+10, { 0,0,10,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallLeft1", airwallLeft1);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallBottom1", airwallBottom1);
    addEntity("AirwallBottom2", airwallBottom2);
    addEntity("AirwallRight", airwallRight);
    addEntity("AirwallRight1", airwallRight1);

    Animation spike = Animation(ResourceManager::getInstance().getResource("SPIKE"),2,1,2,20,20);
    std::vector<Animation> animspike = { 
        Animation(spike.getFrame(0),1,1,1,20,20),Animation(spike.getFrame(0),1,1,1,20,20),
        Animation(spike.getFrame(1),1,1,1,20,20),Animation(spike.getFrame(1),1,1,1,20,20) };
    Entity* spike0 = new Entity("Spike0", 600, 160, { 5,5,35,35 }, { 0,0,40,40 }, animspike, animspike);
    Entity* spike1 = new Entity("Spike1", 600, 200, { 5,5,35,35 }, { 0,0,40,40 }, animspike, animspike);
    Entity* spike2 = new Entity("Spike2", 600, 240, { 5,5,35,35 }, { 0,0,40,40 }, animspike, animspike);

    if (GameManager::getInstance().savingVar.find("RUINS_PUZZLE_SOLVED") == GameManager::getInstance().savingVar.end()) {
        spike0->setPassable(false), spike0->setDirection(DIRECTION_DOWN),
        spike1->setPassable(false), spike1->setDirection(DIRECTION_DOWN),
        spike2->setPassable(false), spike2->setDirection(DIRECTION_DOWN);
    }
    else {
        spike0->setPassable(true), spike0->setDirection(DIRECTION_RIGHT),
        spike1->setPassable(true), spike1->setDirection(DIRECTION_RIGHT),
        spike2->setPassable(true), spike2->setDirection(DIRECTION_RIGHT);
    }
    spike0->setVisible(true), spike0->setLayer(1);
    spike1->setVisible(true), spike1->setLayer(1);
    spike2->setVisible(true), spike2->setLayer(1);
    addEntity("Spike0", spike0);
    addEntity("Spike1", spike1);
    addEntity("Spike2", spike2);
    Entity* portal = new Entity("Portal", 0, 180, { 0,0,5,100 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 1;
        GameManager::getInstance().setRoom(ROOM_RUINS_BATTLE); }, 1);
    addEntity("Portal", portal);
}
Room_Ruins_Puzzle::~Room_Ruins_Puzzle() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_ruins_puzzle");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}
void Room_Ruins_Puzzle::roomUpdate() {
    if (GameManager::getInstance().savingVar.find("RUINS_PUZZLE_SOLVED") == GameManager::getInstance().savingVar.end() &&
        entities["Flower1"]->getDirection() == DIRECTION_RIGHT &&
        entities["Flower2"]->getDirection() == DIRECTION_RIGHT &&
        entities["Flower3"]->getDirection() == DIRECTION_RIGHT &&
        entities["Flower4"]->getDirection() == DIRECTION_RIGHT &&
        entities["Flower5"]->getDirection() == DIRECTION_RIGHT) {
        GameManager::getInstance().savingVar["RUINS_PUZZLE_SOLVED"] = 1;
        entities["Spike0"]->setPassable(true), entities["Spike0"]->setDirection(DIRECTION_RIGHT),
        entities["Spike1"]->setPassable(true), entities["Spike1"]->setDirection(DIRECTION_RIGHT),
        entities["Spike2"]->setPassable(true), entities["Spike2"]->setDirection(DIRECTION_RIGHT);
        AudioManager::getInstance().playSound("SND_SPIKEOPEN");
    }
}