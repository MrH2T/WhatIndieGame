#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Ruins_Puzzle_2::Room_Ruins_Puzzle_2() :Room(ROOM_RUINS_PUZZLE_2, NULL, 19 * TILE_GAME_SIZE, 14 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Ruins_Puzzle_2::roomInit() {
    if (!AudioManager::getInstance().isPlaying("BGM_RUINS"))AudioManager::getInstance().stopBgm(), AudioManager::getInstance().playSound("BGM_RUINS", true);
    calculateMap(ResourceManager::getInstance().getResource("RUINS_TILESET"), 19, 8,
        { {29,22,22,22,22,22,22,23,8,8,21,22,22,22,22,22,22,30},{15,2,2,2,2,2,2,4,8,8,1,2,2,2,2,2,2,13},{15,2,2,2,2,2,2,4,8,8,1,2,2,2,2,2,2,13},{15,10,10,10,10,10,10,12,8,8,9,10,10,10,10,10,10,13},{15,16,16,16,16,16,16,16,32,33,16,16,16,16,16,16,16,16},{15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,13},{15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,13},{37,6,6,6,6,6,6,7,16,16,5,6,6,6,6,6,6,38},{-1,-1,-1,-1,-1,29,22,23,8,8,21,22,30},{-1,-1,-1,-1,-1,15,2,4,8,8,1,2,13},{-1,-1,-1,-1,-1,15,10,12,8,8,9,10,13},{-1,-1,-1,-1,-1,15,8,8,8,8,8,8,13},{-1,-1,-1,-1,-1,15,8,8,8,8,8,8,13},{-1,-1,-1,-1,-1,37,6,6,6,6,6,6,38} });

    Canvas::getInstance().addObject("background_ruins_puzzle_2",
        DrawableObject(
            Animation(map, 1, 1, 1, width, height),
            0, 0, RECT({ 0,0,width,height }), 0));
    switch (GameManager::getInstance().globalVar[ROOM_ENTRANCE]) {
    case 0:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 340,30 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_DOWN);
        break;
    case 1:

        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({ 640,180 });
        GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_LEFT);
        break;
    }

    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);


    Animation tileset = Animation(ResourceManager::getInstance().getResource("RUINS_TILESET"), 19 * 8, 19, 8, 20, 20);
    HBITMAP board = tileset.getFrame(119),
        yellow = subBitmap(ResourceManager::getInstance().getResource("RUINS_TILESET"), { 20 * 6,20 * 12 + 10,20 * 7,20 * 13 + 10 }), red = tileset.getFrame(97),
        leftwall=tileset.getFrame(13);
    std::vector<Animation> anim = { Animation(red, 1, 1, 1, 20, 20), Animation(yellow, 1, 1, 1, 20, 20) ,
     Animation(yellow, 1, 1, 1, 20, 20) , Animation(yellow, 1, 1, 1, 20, 20) };

    int dirs[15] = {0,0,0,3,3,0,0,3,3,0,3,0,0,0,3};

    Entity* flowers[15], *boards[15];
    for (int i = 0; i < 15; i++) {
        std::string namef = "Flower" + std::to_string(i);
        int r = i / 5, c = i % 5;
        int posx = 80 + 120 * c, posy = 200 + 80 * r;
        flowers[i] = new Entity(namef, posx, posy, { 0,0,0,0 }, { 0,0,40,40 }, anim,anim);
        flowers[i]->setPassable(1);
        if (GameManager::getInstance().savingVar.find("RUINS_PUZZLE_2_SOLVED") == GameManager::getInstance().savingVar.end())
        {
            flowers[i]->setDirection(dirs[i]);
        }
        else flowers[i]->setDirection(DIRECTION_RIGHT);
        flowers[i]->setVisible(1);
        flowers[i]->setLayer(1);
        addEntity(flowers[i]);
    }
    for (int i = 0; i < 15; i++) {
        std::string nameb = "Board" + std::to_string(i);
        int r = i / 5, c = i % 5;
        int posx = 120 + 120 * c, posy = 200 + 80 * r;
        boards[i] = new Entity(nameb, posx, posy, { 5,5,35,35 }, { 0,0,40,40 }, Animation(board, 1, 1, 1, 20, 20), true);

        boards[i]->setReaction(
            [=]() {
                if (GameManager::getInstance().savingVar.find("RUINS_PUZZLE_2_SOLVED") != GameManager::getInstance().savingVar.end())return;
                AudioManager::getInstance().playSound("SND_SPIKEOPEN");
                int r = i / 5, c = i % 5;
                if (r >= 1)flowers[(r - 1) * 5 + c]->setDirection(3 - flowers[(r - 1) * 5 + c]->getDirection());
                if (c >= 1)flowers[r * 5 + c - 1]->setDirection(3 - flowers[r * 5 + c - 1]->getDirection());
                if (r <= 1)flowers[(r + 1) * 5 + c]->setDirection(3 - flowers[(r + 1) * 5 + c]->getDirection());
                if (c <= 3)flowers[r * 5 + c + 1]->setDirection(3 - flowers[r * 5 + c + 1]->getDirection());
                flowers[r * 5 + c]->setDirection(3 - flowers[r * 5 + c]->getDirection());
            }
        , 1);
        boards[i]->setVisible(1);
        boards[i]->setLayer(1);
        addEntity(boards[i]);
    }


    Entity
        * airwallTop = new Entity("AirwallTop", 0, 0, { 0,0,315,140 }, false),
        * airwallTop1 = new Entity("AirwallTop1", 410, 0, { 0,0,310,145 }, false),
        * airwallLeft = new Entity("AirwallLeft", 30, 0, { 0,0,10,height }, false),
        * airwallLeft1 = new Entity("AirwallLeft1", 230, 540, { 0,0,10,200 }, false),
        * airwallBottom = new Entity("AirwallBottom", 230, 720, { 0,0,270,10 }, false),
        * airwallBottom1 = new Entity("AirwallBottom1", 20, 480, { 0,0,290,150 }, false),
        * airwallBottom2 = new Entity("AirwallBottom2", 405, 480, { 0,0,290,150 }, false),
        * airwallRight = new Entity("AirwallRight", 690, 200, { 0,0,10,height }, false),
        * airwallRight1 = new Entity("AirwallRight1", 490, 540, { 0,0,10,200 }, false);
    addEntity(airwallTop);
    addEntity(airwallTop1);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallLeft1", airwallLeft1);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallBottom1", airwallBottom1);
    addEntity("AirwallBottom2", airwallBottom2);
    addEntity("AirwallRight", airwallRight);
    addEntity("AirwallRight1", airwallRight1);


    Entity* fakewall = new Entity("Fakewall", 680, 160, { 10,10,40,40 }, { 0,0,40,40 }, Animation(leftwall, 1, 1, 1, 20, 20));
    if (GameManager::getInstance().savingVar.find("RUINS_SECRET_REVEALED") == GameManager::getInstance().savingVar.end()) {
        fakewall->setVisible(1);
        fakewall->setPassable(0);
    }
    else {
        fakewall->setPassable(1);
    }
    addEntity(fakewall);

    Animation spike = Animation(ResourceManager::getInstance().getResource("SPIKE"), 2, 1, 2, 20, 20);
    std::vector<Animation> animspike = {
        Animation(spike.getFrame(0),1,1,1,20,20),Animation(spike.getFrame(0),1,1,1,20,20),
        Animation(spike.getFrame(1),1,1,1,20,20),Animation(spike.getFrame(1),1,1,1,20,20) };
    Entity* spike0 = new Entity("Spike0", 320, 520, { 5,5,35,35 }, { 0,0,40,40 }, animspike, animspike);
    Entity* spike1 = new Entity("Spike1", 360, 520, { 5,5,35,35 }, { 0,0,40,40 }, animspike, animspike);

    if (GameManager::getInstance().savingVar.find("RUINS_PUZZLE_2_SOLVED") == GameManager::getInstance().savingVar.end()) {
        spike0->setPassable(false), spike0->setDirection(DIRECTION_DOWN),
            spike1->setPassable(false), spike1->setDirection(DIRECTION_DOWN);
    }
    else {
        spike0->setPassable(true), spike0->setDirection(DIRECTION_RIGHT),
            spike1->setPassable(true), spike1->setDirection(DIRECTION_RIGHT);
    }
    spike0->setVisible(true), spike0->setLayer(1);
    spike1->setVisible(true), spike1->setLayer(1);
    addEntity("Spike0", spike0);
    addEntity("Spike1", spike1);
    Entity* portal = new Entity("Portal", 320, 10, { 0,0,100,5 }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 2;
        GameManager::getInstance().setRoom(ROOM_RUINS_TORIEL); }, 1);
    addEntity("Portal", portal);
    Entity* portal2 = new Entity("Portal2", 640, 200, { 0,0,5,40}, true);
    portal2->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 0;
        GameManager::getInstance().setRoom(ROOM_RUINS_SECRET); }, 1);
    //addEntity("Portal2", portal2);
}
Room_Ruins_Puzzle_2::~Room_Ruins_Puzzle_2() {
    clearEntities();
    Canvas::getInstance().deleteObject("background_ruins_puzzle_2");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}
void Room_Ruins_Puzzle_2::roomUpdate() {
    if (GameManager::getInstance().savingVar.find("RUINS_PUZZLE_2_SOLVED") == GameManager::getInstance().savingVar.end())
    {
        int flag0 = 0, flag1 = 0;
        for (int i = 0; i < 15; i++) {
            std::string name = "Flower" + std::to_string(i);
            if (entities[name]->getDirection() == DIRECTION_RIGHT)flag1 = 1;
            if (entities[name]->getDirection() == DIRECTION_DOWN)flag0 = 1;
        }
        if (flag0 == 1 && flag1 == 0 &&
            GameManager::getInstance().savingVar.find("RUINS_SECRET_REVEALED") == GameManager::getInstance().savingVar.end()) {
            GameManager::getInstance().savingVar["RUINS_SECRET_REVEALED"] = 1;
            entities["Fakewall"]->setVisible(0);
            entities["Fakewall"]->setPassable(1);
            AudioManager::getInstance().playSound("SND_PLAYERHURT");
            GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setSpeedX(0);
            GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setSpeedY(0);
            GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_CUTSCENE;
            GameManager::getInstance().addWaiting(
                [](){ConversationSequence::getInstance().setSequence({
                    []() {Conversation::getInstance().beginConversation(Text(L"* 这居然有密道???"),
                           Animation(ResourceManager::getInstance().getResource("NIKO_SHOCK_FACE"),1,1,1,96,96)); }
                    });
            ConversationSequence::getInstance().startConversation();
            },20);
        }
        if (flag0 == 0 && flag1 == 1) {
            GameManager::getInstance().savingVar["RUINS_PUZZLE_2_SOLVED"] = 1;
            entities["Spike0"]->setPassable(true), entities["Spike0"]->setDirection(DIRECTION_RIGHT),
                entities["Spike1"]->setPassable(true), entities["Spike1"]->setDirection(DIRECTION_RIGHT),
            AudioManager::getInstance().playSound("SND_SPIKEOPEN");
        }
    }
}