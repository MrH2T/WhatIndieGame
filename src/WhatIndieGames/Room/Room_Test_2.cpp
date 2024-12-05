#include"AllRooms.h"
#include"../Utils/Conversation.h"


Room_Test_2::Room_Test_2():Room(ROOM_TEST_2,NULL,20*TILE_GAME_SIZE, 15 * TILE_GAME_SIZE) {
    roomInit();
}
void Room_Test_2::roomInit() {
    if (!AudioManager:: getInstance().isPlaying("BGM_SANS"))AudioManager::getInstance().stopBgm(),AudioManager::getInstance().playSound("BGM_SANS", true);
    calculateMap(ResourceManager::getInstance().getResource("TEST_ROOM_TILESET"),4,5,
        { {14,16,16,16,16,16,16,16,16,13,11,11,11,11,11,11,11,11,11,11},
{12,0,0,0,2,0,0,0,0,10,11,11,11,11,11,11,11,11,11,11},
{12,0,0,0,0,0,0,1,0,10,11,11,11,11,11,11,11,11,11,11},
{12,0,1,0,3,0,0,3,0,10,11,11,11,11,11,11,11,11,11,11},
{12,0,0,3,0,0,3,0,0,10,11,11,11,11,11,11,11,11,11,11},
{12,0,0,0,0,0,0,0,1,10,11,11,11,11,11,11,11,11,11,11},
{12,0,0,0,1,3,0,0,0,10,11,11,11,11,11,11,11,11,11,11},
{12,0,0,3,0,0,0,1,0,10,11,11,11,11,11,11,11,11,11,11},
{12,1,0,0,0,0,0,0,2,15,16,16,16,16,16,16,16,16,16,16},
{12,0,0,0,2,0,0,3,0,1,0,2,0,0,3,0,0,2,0,0},
{9,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
{11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
{11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
{11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
{11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11}
        });

    Canvas::getInstance().addObject("background_room_test_2",
        DrawableObject(
            Animation(map, 1, 1, 1, width,height),
            0, 0, RECT({ 0,0,width,height }), 0));
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setPos({19*40-20,9 * 40-10});
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setDirection(DIRECTION_LEFT);
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);
    
    Animation allanim = Animation(ResourceManager::getInstance().getResource("SANS_IMAGES"), 16, 4, 4, 23, 30);
    Animation allanim4 = Animation(ResourceManager::getInstance().getResource("SANS_IMAGES"), 4, 4, 1, 23 * 4, 30);
    std::vector<Animation> anims({
        Animation(allanim.getFrame(0),1,1,1,23,30),
        Animation(allanim.getFrame(4),1,1,1,23,30),
        Animation(allanim.getFrame(8),1,1,1,23,30),
        Animation(allanim.getFrame(12),1,1,1,23,30),
        });
    Entity* npcman = new Entity("NPC", 300, 300, { 0,30,23 * 2,30 * 2 }, { 0, 0, 23 * 2,30 * 2 },
        anims, {
        Animation(allanim4.getFrame(0),4,1,4,23,30),
        Animation(allanim4.getFrame(1),4,1,4,23,30),
        Animation(allanim4.getFrame(2),4,1,4,23,30),
        Animation(allanim4.getFrame(3),4,1,4,23,30),
        });
    npcman->setVisible(true);
    npcman->setReaction([&]() {
        if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;
        Animation sansface = Animation(ResourceManager::getInstance().getResource("SANS_FACE"), 1, 1, 1, 32, 30);
        ConversationSequence::getInstance().setSequence(ConvSeq({
            [=]() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                Conversation::getInstance().beginConversation(Text(L"* wanna some ketchup?",RGB(255,255,255),RGB(0,0,0),L"Comic Sans MS",40),sansface); },
            [=]() {Conversation::getInstance().beginConversation(

                Conversation::Choice(ChoiceItem({
                    Text(L"Yes",RGB(255,255,255),RGB(0,0,0),L"Determination Regular",40),
                    Text(L"No",RGB(255,255,255),RGB(0,0,0),L"Determination Regular",40)
                    }),[](int res) {GameManager::getInstance().globalVar["Choose_Temp"] = res + 1; })
            ); },
            [=]() {
                AudioManager::getInstance().playSound("SND_SANS_SPEAK",false);
                if (GameManager::getInstance().globalVar["Choose_Temp"] == 1) {
                    Conversation::getInstance().beginConversation(Text(L"* here you are.", RGB(255, 255, 255), RGB(0, 0, 0), L"Comic Sans MS", 40),sansface);
                }
                else if (GameManager::getInstance().globalVar["Choose_Temp"] == 2) {
                    Conversation::getInstance().beginConversation(Text(L"* pity.", RGB(255, 255, 255), RGB(0, 0, 0), L"Comic Sans MS", 40),
                        Animation(ResourceManager::getInstance().getResource("SANS_CLOSEEYE"), 1, 1, 1, 32, 30));
                }
            },
            [=]() {
                if (GameManager::getInstance().globalVar["Choose_Temp"] == 1) {
                    Conversation::getInstance().beginConversation(Text(L"* (You drink the ketchup. )", 0xffffff, 0x000000, L"Determination Regular", 40));
                }
                else ConversationSequence::getInstance().stopConversation();
                GameManager::getInstance().globalVar.erase("Choose_Temp");
            },
            [=]() {
                 Conversation::getInstance().beginConversation(Text(L"* (The sweetness fills you with determination. )", 0xffffff, 0x000000, L"Determination Regular", 40));
               }
            }
        ));
        ConversationSequence::getInstance().startConversation();
        }, 0);
    npcman->setDirection(DIRECTION_DOWN);
    addEntity("npc", npcman);

    






    Entity* airwallTop = new Entity("AirwallTop", 0, MAIN_PLAYER_HEIGHT-5, { 0,0,width,10 }, false),
        * airwallLeft = new Entity("AirwallLeft", -10, 0, { 0,0,10,height }, false),
        * airwallBottom = new Entity("AirwallBottom", 0, height, { 0,0,width,10 }, false),
        * airwallRight = new Entity("AirwallRight", width, -10, { 0,0,10,height }, false);
    addEntity("AirwallTop", airwallTop);
    addEntity("AirwallLeft", airwallLeft);
    addEntity("AirwallBottom", airwallBottom);
    addEntity("AirwallRight", airwallRight);

    Entity* portal = new Entity("Portal", width-10,8*TILE_GAME_SIZE, { 0,0,10,2*TILE_GAME_SIZE }, true);
    portal->setReaction([&]() {
        GameManager::getInstance().globalVar[ROOM_ENTRANCE] = 1;
        GameManager::getInstance().setRoom(ROOM_TEST_1);
        }, 1);
    addEntity("Portal",portal);
}
Room_Test_2::~Room_Test_2() {
    //MessageBoxA(0, "FUCKYOU", "FUCK", 0);
    clearEntities();
    Canvas::getInstance().deleteObject("background_room_test_2");
    //AudioManager::getInstance().stopBgm("BGM_SANS");
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(false);
}