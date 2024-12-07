// main.cpp : 定义应用程序的入口点。
//
#include"Manager/Managers.h"
#include"Game.h"
#include "framework.h"
#include "Resource.h"
#include"Utils/Conversation.h"
#include"Utils/Canvas.h"
#include"Room/AllRooms.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WHATINDIEGAMES, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WHATINDIEGAMES));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WHATINDIEGAMES));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WHATINDIEGAMES);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, 
       WS_OVERLAPPEDWINDOW&~WS_THICKFRAME&~WS_MAXIMIZEBOX,
      CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

   SetMenu(hWnd, NULL);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE: {
        // 初始化游戏窗体
        initGame(hWnd, wParam, lParam);
        break;
    }
    case WM_KEYDOWN:
        // 键盘按下事件
        keyDown(hWnd, wParam, lParam);
        break;
    case WM_KEYUP:
        // 键盘松开事件
        keyUp(hWnd, wParam, lParam);
        break;
    case WM_TIMER:
        // 定时器事件
        //if (currentStage != NULL && currentStage->timerOn) TimerUpdate(hWnd, wParam, lParam);
   
        timerTick(hWnd,wParam, lParam);
        break;
    case WM_PAINT:
    {
        /*std::string npc = "npc";
        npc+=char(calc + 48);
        calc+=1;
        if(calc<=60)
        Canvas::getInstance().addObject(npc,
            DrawableObject(
                Animation(ResourceManager::getInstance().getResource("NPC"), 4, 1, 4, 19, 26),
                100+100*(calc%7), 100+100*(calc/7), RECT({0,0,19 * 2,26 * 2}), 1));*/

        Canvas::getInstance().renderScene(hWnd);
        break;
    }
    case WM_DESTROY:
        GameManager::getInstance().gameEscape();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void timerTick(HWND hWnd, WPARAM wParam ,LPARAM lParam) {

    static unsigned long long CURRENT_TICK = 0;
    CURRENT_TICK++;
    GameManager::getInstance().gameUpdate();
    EventManager::getInstance().unsubscribeCheck();
    
    
    AudioManager::getInstance().checkStopped();
    


    Canvas::getInstance().tickFrames();
    InvalidateRect(hWnd, NULL, FALSE);
}
// 键盘按下事件处理函数
void keyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
    case VK_UP:
        if (GameManager::getInstance().globalVar["UP_PRESS"] != 1) {
            GameManager::getInstance().globalVar["UP_PRESS"] = 1;
            EventManager::getInstance().emit("UP_PRESS");
        }
        break;
    case VK_DOWN:
        if (GameManager::getInstance().globalVar["DOWN_PRESS"] != 1) {
            GameManager::getInstance().globalVar["DOWN_PRESS"] = 1;
            EventManager::getInstance().emit("DOWN_PRESS");
        }
        break;
    case VK_LEFT:
        if (GameManager::getInstance().globalVar["LEFT_PRESS"] != 1) {
            GameManager::getInstance().globalVar["LEFT_PRESS"] = 1;
            EventManager::getInstance().emit("LEFT_PRESS");
        }
        break;
    case VK_RIGHT:
        if (GameManager::getInstance().globalVar["RIGHT_PRESS"] != 1) {
            GameManager::getInstance().globalVar["RIGHT_PRESS"] = 1;
            EventManager::getInstance().emit("RIGHT_PRESS");
        }
        break;
    case 'Z':
        if (GameManager::getInstance().globalVar["Z_PRESS"] != 1) {
            GameManager::getInstance().globalVar["Z_PRESS"] = 1;
            EventManager::getInstance().emit("Z_PRESS");
        }
        break;
    case 'X':
        if (GameManager::getInstance().globalVar["X_PRESS"] != 1) {
            GameManager::getInstance().globalVar["X_PRESS"] = 1;
            EventManager::getInstance().emit("X_PRESS");
        }
        break;
    case 'C':
        if (GameManager::getInstance().globalVar["C_PRESS"] != 1) {
            GameManager::getInstance().globalVar["C_PRESS"] = 1;
            EventManager::getInstance().emit("C_PRESS");
        }
        break;
    case 'V':
        if (GameManager::getInstance().globalVar["V_PRESS"] != 1) {
            GameManager::getInstance().globalVar["V_PRESS"] = 1;
            EventManager::getInstance().emit("V_PRESS");
        }
        break;
    case VK_ESCAPE:
        if (GameManager::getInstance().globalVar["ESC_PRESS"] != 1) {
            GameManager::getInstance().globalVar["ESC_PRESS"] = 1;
            EventManager::getInstance().emit("ESC_PRESS");
        }
        break;
    default:
        break;
    }
}

// 键盘松开事件处理函数
void keyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    // TODO
    switch (wParam)
    {
    case VK_UP:
        GameManager::getInstance().globalVar["UP_PRESS"] = 0;
        EventManager::getInstance().emit("UP_STOP");
        break;
    case VK_DOWN:
        GameManager::getInstance().globalVar["DOWN_PRESS"] = 0;
        EventManager::getInstance().emit("DOWN_STOP");
        break;
    case VK_LEFT:
        GameManager::getInstance().globalVar["LEFT_PRESS"] = 0;
        EventManager::getInstance().emit("LEFT_STOP");
        break;
    case VK_RIGHT:
        GameManager::getInstance().globalVar["RIGHT_PRESS"] = 0;
        EventManager::getInstance().emit("RIGHT_STOP");
        break;
    case 'Z':
        GameManager::getInstance().globalVar["Z_PRESS"] = 0;
        EventManager::getInstance().emit("Z_STOP");
        break;
    case 'X':
        GameManager::getInstance().globalVar["X_PRESS"] = 0;
        EventManager::getInstance().emit("X_STOP");
        break;
    case 'C':
        GameManager::getInstance().globalVar["C_PRESS"] = 0;
        EventManager::getInstance().emit("C_STOP");
        break;
    case 'V':
        GameManager::getInstance().globalVar["V_PRESS"] = 0;
        EventManager::getInstance().emit("V_STOP");
        break;
    case VK_ESCAPE:
        GameManager::getInstance().globalVar["ESC_PRESS"] = 0;
        EventManager::getInstance().emit("ESC_STOP");
        break;
    default:
        break;
    }
}

void initGame(HWND hWnd, WPARAM wParam, LPARAM lParam) {


    auto bitmap = [&](int id) {
        return LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(id));
        };

#pragma region ResourceLoading
    auto& rs = ResourceManager::getInstance();
    rs.loadResource("BACKGROUND", bitmap(BACKGROUND_BMP));
    rs.loadResource("NPC", bitmap(FRISK_BMP));
    rs.loadResource("CONVERSATION_BOX", bitmap(DIALOG_BOX_BMP));
    rs.loadResource("STAR", bitmap(STAR_BMP));
    rs.loadResource("SANS_FACE", bitmap(SANS_FACE_BMP));
    rs.loadResource("SANS_CLOSEEYE", bitmap(SANS_CLOSEEYE_BMP));
    rs.loadResource("FRISK_WALKING_DOWN", bitmap(FRISK_WALKING_DOWN_BMP));
    rs.loadResource("FRISK_WALKING_LEFT", bitmap(FRISK_WALKING_LEFT_BMP));
    rs.loadResource("FRISK_WALKING_UP", bitmap(FRISK_WALKING_UP_BMP));
    rs.loadResource("FRISK_WALKING_RIGHT", bitmap(FRISK_WALKING_RIGHT_BMP));
    rs.loadResource("PAUSE_MENU_BOX", bitmap(PAUSE_MENU_BOX_BMP));
    rs.loadResource("SANS_IMAGES", bitmap(SANS_WALKING_BMP));
    rs.loadResource("TEST_ROOM_TILESET", bitmap(TEST_ROOM_TILESET_BMP));
    rs.loadResource("HOUSE", bitmap(HOUSE_BMP));
    rs.loadResource("NIKO", bitmap(NIKO_BMP));
    rs.loadResource("BATTLE_BACKGROUND", bitmap(BATTLE_BACKGROUND_BMP));
    rs.loadResource("BATTLE_BOX", bitmap(BATTLE_BOX_BMP));
    rs.loadResource("BATTLE_BULLETS", bitmap(BATTLE_BULLETS_BMP));
    rs.loadResource("BATTLE_BUTTONS", bitmap(BATTLE_BUTTONS_BMP));
    rs.loadResource("BATTLE_CHECKBOX", bitmap(BATTLE_CHECKBOX_BMP));
    rs.loadResource("NIKO_BATTLE", bitmap(NIKO_BATTLE_BMP));
    rs.loadResource("NIKO_DYING", bitmap(NIKO_DYING_BMP));
    rs.loadResource("GAMEOVER_BANNER", bitmap(GAMEOVER_BMP));
    rs.loadResource("KNIFE_SLASH", bitmap(KNIFESLASH_BMP));
    rs.loadResource("MENU_BOX_CHOOSE",bitmap(MENU_BOX_CHOOSE_BMP));
    rs.loadResource("MENU_BOX_STATE",bitmap(MENU_BOX_STATE_BMP));
    rs.loadResource("MENU_BOX_INVENTORY",bitmap(MENU_BOX_INVENTORY_BMP));
    rs.loadResource("MAINMENU_BANNER",bitmap(MAINMENU_BANNER_BMP));
    rs.loadResource("MAINMENU_NIKO",bitmap(MAINMENU_NIKO_BMP));
    rs.loadResource("MAINMENU_PURPLELIGHTS", bitmap(MAINMENU_PURPLELIGHTS_BMP));
    rs.loadResource("MAINMENU_BACKGROUND", bitmap(MAINMENU_BACKGROUND_BMP));

    
#pragma endregion

#pragma region AudioLoading
    auto& am = AudioManager::getInstance();
    am.loadAudio("SND_SANS_SPEAK", "Resource/Audio/snd_sans_speak.wav",1);
    am.loadAudio("SND_CHOOSE", "Resource/Audio/snd_choose.wav",1);
    am.loadAudio("SND_CHOOSE_BIG", "Resource/Audio/snd_choose_big.wav",1);
    am.loadAudio("SND_ENEMYALARM", "Resource/Audio/snd_enemyalarm.wav",1);
    am.loadAudio("SND_PLAYERHURT", "Resource/Audio/snd_playerhurt.wav", 1);
    am.loadAudio("SND_BULLET_DING", "Resource/Audio/snd_bullet_ding.wav", 1);
    am.loadAudio("SND_ATTACK", "Resource/Audio/snd_attack.wav", 1);
    am.loadAudio("SND_ENEMYHIT", "Resource/Audio/snd_enemyhit.wav", 1);
    am.loadAudio("SND_ITEMUSE", "Resource/Audio/snd_itemuse.wav", 1);
    am.loadAudio("SND_SAVING", "Resource/Audio/snd_saving.wav", 1);

    am.loadAudio("BGM_SANS", "Resource/Audio/bgm_sans.wav");
    am.loadAudio("BGM_SNOWTOWN", "Resource/Audio/bgm_snowtown.wav");
    am.loadAudio("BGM_BATTLE", "Resource/Audio/bgm_battle.wav");
    am.loadAudio("BGM_GAMEOVER", "Resource/Audio/bgm_gameover.ogg");
    am.loadAudio("BGM_MAINMENU", "Resource/Audio/bgm_mainmenu.ogg");

#pragma endregion

    auto& cv = Canvas::getInstance();
    auto& ev = EventManager::getInstance();
#pragma region PauseMenuPrepare
    cv.addObject("Pause_Menu_Box",
        DrawableObject(
            Animation(
                ResourceManager::getInstance().getResource("PAUSE_MENU_BOX"),
                1, 1, 1, PAUSE_MENU_BOX_WIDTH, PAUSE_MENU_BOX_HEIGHT),
            PAUSE_MENU_BOX_X, PAUSE_MENU_BOX_Y, { 0,0,PAUSE_MENU_BOX_WIDTH,PAUSE_MENU_BOX_HEIGHT},9, DRAW_ABSOLUTE|DRAW_IGNOREBLANK
        ));
    cv.addObject("Pause_Menu_Resume",
        DrawableObject(
            Text(L"继续游戏",0xffffff,0,L"SimSun",30),
            PAUSE_MENU_BOX_X+40, PAUSE_MENU_BOX_Y+30,{0,0,120,40},10,DRAW_ABSOLUTE
        ));
    cv.addObject("Pause_Menu_Exit",
        DrawableObject(
            Text(L"退出游戏", 0xffffff, 0, L"SimSun", 30),
            PAUSE_MENU_BOX_X + 40, PAUSE_MENU_BOX_Y + 70, { 0,0,120,40 }, 10, DRAW_ABSOLUTE
        ));
    ev.subscribe("UP_PRESS", "PauseMenuSelection", []() {
        if (GameManager::getInstance().globalVar[GLOBAL_PAUSED]) {
            GameManager::getInstance().globalVar["PAUSE_MENU_SELECT"] = 0;
            AudioManager::getInstance().playSound("SND_CHOOSE");
            Canvas::getInstance().getObject("Pause_Menu_Resume").text = Text(L"继续游戏", RGB(255, 255, 0), 0, L"SimSun", 30);
            Canvas::getInstance().getObject("Pause_Menu_Exit").text = Text(L"退出游戏", RGB(255,255,255), 0, L"SimSun", 30);
        }
        });
    ev.subscribe("DOWN_PRESS", "PauseMenuSelection", []() {
        if (GameManager::getInstance().globalVar[GLOBAL_PAUSED]) {
            GameManager::getInstance().globalVar["PAUSE_MENU_SELECT"] = 1;
            AudioManager::getInstance().playSound("SND_CHOOSE");
            Canvas::getInstance().getObject("Pause_Menu_Resume").text = Text(L"继续游戏", RGB(255, 255, 255), 0, L"SimSun", 30);
            Canvas::getInstance().getObject("Pause_Menu_Exit").text = Text(L"退出游戏", RGB(255, 255, 0), 0, L"SimSun", 30);
        }
        });
    ev.subscribe("Z_PRESS", "PauseMenuSelection", [&]() {
        if (GameManager::getInstance().globalVar[GLOBAL_PAUSED]) {
            GameManager::getInstance().globalVar[GLOBAL_PAUSED] = 0;
            Canvas::getInstance().getObject("Pause_Menu_Box").switchState(DRAW_VISIBLE, 0);
            Canvas::getInstance().getObject("Pause_Menu_Resume").switchState(DRAW_VISIBLE, 0);
            Canvas::getInstance().getObject("Pause_Menu_Exit").switchState(DRAW_VISIBLE, 0);
            if (GameManager::getInstance().globalVar["PAUSE_MENU_SELECT"] == 1) {
                GameManager::getInstance().goMainMenu();
                //gameEscape(hWnd,wParam,lParam);
            }
            else {
                EventManager::getInstance().emit("GAME_RESUME");
            }
        }
        });

#pragma endregion

#pragma region MenuPrepare
    cv.addObject("Menu_box_choose", DrawableObject(Animation(rs.getResource("MENU_BOX_CHOOSE"),1,1,1,100,70), MENU_BOX_CHOOSE_X,70,{0,0,100,70},8,DRAW_ABSOLUTE));
    cv.addObject("Menu_box_state", DrawableObject(Animation(rs.getResource("MENU_BOX_STATE"),1,1,1,300,150), MENU_BOX_CHOOSE_X +105,70,{0,0,300,150},8,DRAW_ABSOLUTE));
    cv.addObject("Menu_box_inventory", DrawableObject(Animation(rs.getResource("MENU_BOX_INVENTORY"),1,1,1,300,400), MENU_BOX_CHOOSE_X +105,70,{0,0,300,400},8,DRAW_ABSOLUTE));

    cv.addObject("Menu_box_choose_select_state", DrawableObject(Text(L"状态"),MENU_BOX_CHOOSE_X+20,MENU_BOX_CHOOSE_Y+7,{0,0,100,30},9,DRAW_ABSOLUTE));
    cv.addObject("Menu_box_choose_select_inv", DrawableObject(Text(L"物品"),MENU_BOX_CHOOSE_X+20,MENU_BOX_CHOOSE_Y+37,{0,0,100,30},9,DRAW_ABSOLUTE));
    cv.addObject("Menu_box_state_hp",DrawableObject(Text(),MENU_BOX_CHOOSE_X+105+10,MENU_BOX_CHOOSE_Y+10,{0,0,130,30},9,DRAW_ABSOLUTE));
    cv.addObject("Menu_box_state_gold", DrawableObject(Text(), MENU_BOX_CHOOSE_X + 105 + 10+130, MENU_BOX_CHOOSE_Y + 10, { 0,0,130,30 }, 9, DRAW_ABSOLUTE));
    cv.addObject("Menu_box_state_atk",DrawableObject(Text(),MENU_BOX_CHOOSE_X+105+10,MENU_BOX_CHOOSE_Y+45,{0,0,100,30},9,DRAW_ABSOLUTE));
    cv.addObject("Menu_box_state_def",DrawableObject(Text(),MENU_BOX_CHOOSE_X+105+10+130,MENU_BOX_CHOOSE_Y+45,{0,0,100,30},9,DRAW_ABSOLUTE));
    cv.addObject("Menu_box_state_lv",DrawableObject(Text(),MENU_BOX_CHOOSE_X+105+10,MENU_BOX_CHOOSE_Y+80,{0,0,100,30},9,DRAW_ABSOLUTE));
    cv.addObject("Menu_box_state_exp",DrawableObject(Text(),MENU_BOX_CHOOSE_X+105+10,MENU_BOX_CHOOSE_Y+115,{0,0,100,30},9,DRAW_ABSOLUTE));

    cv.addObject("Menu_box_inv_use",DrawableObject(Text(L"使用"), MENU_BOX_CHOOSE_X + 105 + 40, MENU_BOX_CHOOSE_Y + 365, {0,0,70,30}, 9, DRAW_ABSOLUTE));
    cv.addObject("Menu_box_inv_disc",DrawableObject(Text(L"丢弃"), MENU_BOX_CHOOSE_X + 105 + 120, MENU_BOX_CHOOSE_Y + 365, {0,0,70,30}, 9, DRAW_ABSOLUTE));
    cv.addObject("Menu_box_inv_text",DrawableObject(Text(), MENU_BOX_CHOOSE_X + 105+10, MENU_BOX_CHOOSE_Y + 290, {0,0,200,60}, 9, DRAW_ABSOLUTE));

    for (int i = 0; i < 8; i++) {
        cv.addObject(std::string("Menu_box_inv_")+std::to_string(i), 
            DrawableObject(Text(), MENU_BOX_CHOOSE_X + 105 + 10+20, MENU_BOX_CHOOSE_Y + 10+i*30, {0,0,300,30}, 9, DRAW_ABSOLUTE));
    }

    ev.subscribe("X_PRESS", "MenuBoxRet", []() {
        if (GameManager::getInstance().globalVar[GLOBAL_PAUSED])return;
        if (GameManager::getInstance().globalVar[GLOBAL_MENUING] != 1)return;
        if (GameManager::getInstance().globalVar["MENU_LEVEL"] != 0) {
            GameManager::getInstance().globalVar["MENU_LEVEL"] -= 1;
            gameMenuSwitch(GameManager::getInstance().globalVar["MENU_LEVEL"]);
            AudioManager::getInstance().playSound("SND_CHOOSE");
        }
        else {
            GameManager::getInstance().globalVar["MENU_LEVEL"] = 0;
            GameManager::getInstance().globalVar[GLOBAL_MENUING] = 0;
            hideMenu();
        }
        });
    ev.subscribe("C_PRESS", "MenuBoxCheck", []() {
        if (GameManager::getInstance().globalVar[GLOBAL_PAUSED])return;
        if (GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING])return;
        if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION])return;
        if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE]!=GAME_STATE_COMMON)return;
        AudioManager::getInstance().playSound("SND_CHOOSE");
        if (GameManager::getInstance().globalVar[GLOBAL_MENUING] == 1) {
            GameManager::getInstance().globalVar["MENU_LEVEL"] = 0;
            GameManager::getInstance().globalVar[GLOBAL_MENUING] = 0;
            hideMenu();
        }
        else {
            Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
            ent->setSpeedX(0), ent->setSpeedY(0);
            GameManager::getInstance().updateEntityPositions();
            GameManager::getInstance().globalVar[GLOBAL_MENUING] = 1;
            showMenu();
        }
        });
    ev.subscribe("Z_PRESS", "MenuBoxChoose", []() {

        if (GameManager::getInstance().globalVar[GLOBAL_PAUSED])return;
        if (GameManager::getInstance().globalVar[GLOBAL_MENUING] != 1)return;
        int &lev = GameManager::getInstance().globalVar["MENU_LEVEL"];
        if (lev == 0||lev==1) {
            if (lev == 1 &&GameManager::getInstance().globalVar["MENU_CHOOSE_0"]==1&&GameManager::getInstance().inventory.size()==0)return;
            if (lev == 1 && GameManager::getInstance().globalVar["MENU_CHOOSE_0"] == 0)return;
            lev++;
            gameMenuSwitch(lev);
               AudioManager::getInstance().playSound("SND_CHOOSE");
            return;
        }
        if (lev == 2) {
            if (GameManager::getInstance().globalVar["MENU_CHOOSE_2"] == 0) {
                ItemManager::getInstance().getItem(GameManager::getInstance().inventory[
                    GameManager::getInstance().globalVar["MENU_CHOOSE_1"]
                ]).itemFunc();
                GameManager::getInstance().eraseItem(GameManager::getInstance().inventory[
                    GameManager::getInstance().globalVar["MENU_CHOOSE_1"]
                ]);
                lev = 1;
                gameMenuSwitch(1);
            }
            if (GameManager::getInstance().globalVar["MENU_CHOOSE_2"] == 1) {

                GameManager::getInstance().eraseItem(GameManager::getInstance().inventory[
                    GameManager::getInstance().globalVar["MENU_CHOOSE_1"]
                ]);
                AudioManager::getInstance().playSound("SND_CHOOSE");
                lev = 1;
                gameMenuSwitch(1);
            }
        }

        });
    ev.subscribe("UP_PRESS", "MenuBoxUp", []() {
        if (GameManager::getInstance().globalVar[GLOBAL_PAUSED])return;
        if (GameManager::getInstance().globalVar[GLOBAL_MENUING] != 1)return;
        int lev = GameManager::getInstance().globalVar["MENU_LEVEL"];
        if (lev == 0) {
            GameManager::getInstance().globalVar["MENU_CHOOSE_0"] = 0;
            Canvas::getInstance().getObject("Menu_box_choose_select_state").text.setTColor(RGB(255,255,0));
            Canvas::getInstance().getObject("Menu_box_choose_select_inv").text.setTColor(RGB(255,255,255));
            AudioManager::getInstance().playSound("SND_CHOOSE");
        }
        else if (lev == 1) {
            if (GameManager::getInstance().globalVar["MENU_CHOOSE_0"] == 0)return;
            if (GameManager::getInstance().inventory.size() == 0)return;
            Canvas::getInstance().getObject("Menu_box_inv_" + std::to_string(GameManager::getInstance().globalVar["MENU_CHOOSE_1"])).text.setTColor(RGB(255, 255, 255));
            if (GameManager::getInstance().globalVar["MENU_CHOOSE_1"] > 0)
            {
                GameManager::getInstance().globalVar["MENU_CHOOSE_1"]--;
                AudioManager::getInstance().playSound("SND_CHOOSE");
            }
            Canvas::getInstance().getObject("Menu_box_inv_" + std::to_string(GameManager::getInstance().globalVar["MENU_CHOOSE_1"])).text.setTColor(RGB(255, 255, 0));
        }
        });
    ev.subscribe("DOWN_PRESS", "MenuBoxDown", []() {
        if (GameManager::getInstance().globalVar[GLOBAL_PAUSED])return;
        if (GameManager::getInstance().globalVar[GLOBAL_MENUING] != 1)return;
        int lev = GameManager::getInstance().globalVar["MENU_LEVEL"];
        if (lev == 0) {
            GameManager::getInstance().globalVar["MENU_CHOOSE_0"] = 1;
            Canvas::getInstance().getObject("Menu_box_choose_select_state").text.setTColor(RGB(255, 255, 255));
            Canvas::getInstance().getObject("Menu_box_choose_select_inv").text.setTColor(RGB(255, 255, 0));
            AudioManager::getInstance().playSound("SND_CHOOSE");
        }
        else if (lev == 1) {
            if (GameManager::getInstance().globalVar["MENU_CHOOSE_0"] == 0)return;
            if (GameManager::getInstance().inventory.size() == 0)return;
            Canvas::getInstance().getObject("Menu_box_inv_" + std::to_string(GameManager::getInstance().globalVar["MENU_CHOOSE_1"])).text.setTColor(RGB(255, 255, 255));
            if (GameManager::getInstance().globalVar["MENU_CHOOSE_1"] < GameManager::getInstance().inventory.size()-1)
            {
                GameManager::getInstance().globalVar["MENU_CHOOSE_1"]++;
                AudioManager::getInstance().playSound("SND_CHOOSE");
            }
            Canvas::getInstance().getObject("Menu_box_inv_" + std::to_string(GameManager::getInstance().globalVar["MENU_CHOOSE_1"])).text.setTColor(RGB(255, 255, 0));
        }
        });
    ev.subscribe("LEFT_PRESS", "MenuBoxLeft", []() {
        if (GameManager::getInstance().globalVar[GLOBAL_PAUSED])return;
        if (GameManager::getInstance().globalVar[GLOBAL_MENUING] != 1)return;
        int lev = GameManager::getInstance().globalVar["MENU_LEVEL"];
        if (lev == 2) {
            GameManager::getInstance().globalVar["MENU_CHOOSE_2"] = 0;
            Canvas::getInstance().getObject("Menu_box_inv_use").text.setTColor(RGB(255, 255, 0));
            Canvas::getInstance().getObject("Menu_box_inv_disc").text.setTColor(RGB(255, 255, 255));
            AudioManager::getInstance().playSound("SND_CHOOSE");
        }
        });
    ev.subscribe("RIGHT_PRESS", "MenuBoxRight", []() {
        if (GameManager::getInstance().globalVar[GLOBAL_PAUSED])return;
        if (GameManager::getInstance().globalVar[GLOBAL_MENUING] != 1)return;
        int lev = GameManager::getInstance().globalVar["MENU_LEVEL"]; 
        if (lev == 2) {
            GameManager::getInstance().globalVar["MENU_CHOOSE_2"] = 1;
            Canvas::getInstance().getObject("Menu_box_inv_use").text.setTColor(RGB(255, 255, 255));
            Canvas::getInstance().getObject("Menu_box_inv_disc").text.setTColor(RGB(255, 255, 0));
            AudioManager::getInstance().playSound("SND_CHOOSE");
        }
        });
#pragma endregion
    
#pragma region SystemInitialization
    Conversation::getInstance().conversationSysInit();
    Battle::getInstance().battleSysInit();
#pragma endregion


#pragma region ItemRegistering
    auto& ir = ItemManager::getInstance();
    ir.registerItem("怪物糖果", Item("怪物糖果", "回复5HP", []() {
        auto& gm = GameManager::getInstance();
        gm.addHP(5);
        AudioManager::getInstance().playSound("SND_ITEMUSE");
        if (gm.globalVar[GLOBAL_GAME_STATE] == GAME_STATE_BATTLE) {
            auto& conv = Conversation::getInstance();
            ConversationSequence::getInstance().setSequence({
                [&]() {conv.beginConversation(Text(L"* 恢复了 5 HP.")); },
                [&]() {ConversationSequence::getInstance().stopBattleConv(); Battle::getInstance().switchState(BATTLE_DIALOG); }
                });
            ConversationSequence::getInstance().startBattleConv();
        }
        }));
#pragma endregion


#pragma region EventRegistering
    // Pause Event
    EventManager::getInstance().subscribe("ESC_PRESS", "GamePause", [&]() {
        if (GameManager::getInstance().globalVar[GLOBAL_MENUING])return;
        if (GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING])return;
        Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
        ent->setSpeedX(0), ent->setSpeedY(0);
        GameManager::getInstance().updateEntityPositions();
        gamePause();
        });

    // 
   /* EventManager::getInstance().subscribe("CONVERSATION_END", "ConversationManaging",
        []() {EventManager::getInstance().unsubscribe("CONVERSATION_PROCEED", "Conversation_Lines_Listen"); });*/

#pragma endregion

    Animation allanim = Animation(ResourceManager::getInstance().getResource("NIKO"), 4, 4, 1,168, 58);
    std::vector<Animation> anims({
        Animation(allanim.getFrame(0),4,1,4,42,58,3),
        Animation(allanim.getFrame(1),4,1,4,42,58,3),
        Animation(allanim.getFrame(2),4,1,4,42,58,3),
        Animation(allanim.getFrame(3),4,1,4,42,58,3),
        });
    GameManager::getInstance().entities[ENTITY_MAIN_PLAYER] = new Entity(ENTITY_MAIN_PLAYER, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, { 0,29,42,58 }, {0,0,42,58}, {
        Animation(anims[0].getFrame(0),1,1,1,42,58),Animation(anims[1].getFrame(0),1,1,1,42,58),Animation(anims[2].getFrame(0),1,1,1,42,58),Animation(anims[3].getFrame(0),1,1,1,42,58) },anims);
    //GameManager::getInstance().entities[ENTITY_MAIN_PLAYER]->setVisible(true);
    GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_MAINMENU;
    int SPEED = 10;
#pragma region PlayerMoveEventBind
        EventManager::getInstance().subscribe("DOWN_PRESS", "Player_DOWNKEY", [=]() {
            if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_COMMON)return;
            if (GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING])return;
            if (GameManager::getInstance().globalVar[GLOBAL_PAUSED] == 1 || GameManager::getInstance().globalVar[GLOBAL_MENUING] == 1
                ||GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;
            Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
            //ent->setDirection(DIRECTION_DOWN);
            ent->setSpeedY(SPEED);
            //ent->setStatus(ENTITY_WALKING);
            });
        EventManager::getInstance().subscribe("LEFT_PRESS", "Player_LEFTKEY", [=]() {
            if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_COMMON)return;
            if (GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING])return;
            if (GameManager::getInstance().globalVar[GLOBAL_PAUSED] == 1 || GameManager::getInstance().globalVar[GLOBAL_MENUING] == 1
                || GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;
            Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
            //ent->setDirection(DIRECTION_LEFT);
            ent->setSpeedX(-SPEED);
            //ent->setStatus(ENTITY_WALKING);
            });
        EventManager::getInstance().subscribe("UP_PRESS", "Player_UPKEY", [=]() {
            if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_COMMON)return;
            if (GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING])return;
            if (GameManager::getInstance().globalVar[GLOBAL_PAUSED] == 1 || GameManager::getInstance().globalVar[GLOBAL_MENUING] == 1
                || GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;
            Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
            //ent->setDirection(DIRECTION_UP);
            ent->setSpeedY(-SPEED);
            //ent->setStatus(ENTITY_WALKING);
            });
        EventManager::getInstance().subscribe("RIGHT_PRESS", "Player_RIGHTKEY", [=]() {
            if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_COMMON)return;
            if (GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING])return;
            if (GameManager::getInstance().globalVar[GLOBAL_PAUSED] == 1 || GameManager::getInstance().globalVar[GLOBAL_MENUING] == 1
                || GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;            
            Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
            //ent->setDirection(DIRECTION_RIGHT);
            ent->setSpeedX(SPEED);
            //ent->setStatus(ENTITY_WALKING);
            });

        EventManager::getInstance().subscribe("DOWN_STOP", "Player_DOWNKEY", [&]() {
            if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_COMMON)return;
            if (GameManager::getInstance().globalVar[GLOBAL_PAUSED] == 1 || GameManager::getInstance().globalVar[GLOBAL_MENUING] == 1
                || GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;           
            Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
            ent->setSpeedY(0);
            //ent->setStatus(ENTITY_STATIC);
            });
        EventManager::getInstance().subscribe("LEFT_STOP", "Player_LEFTKEY", [&]() {
            if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_COMMON)return;
            if (GameManager::getInstance().globalVar[GLOBAL_PAUSED] == 1 || GameManager::getInstance().globalVar[GLOBAL_MENUING] == 1
                || GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;            
            Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
            ent->setSpeedX(0);
            //ent->setStatus(ENTITY_STATIC);
            });
        EventManager::getInstance().subscribe("UP_STOP", "Player_UPKEY", [&]() {
            if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_COMMON)return;
            if (GameManager::getInstance().globalVar[GLOBAL_PAUSED] == 1 || GameManager::getInstance().globalVar[GLOBAL_MENUING] == 1
                || GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;            
            Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
            ent->setSpeedY(0);
            //ent->setStatus(ENTITY_STATIC);
            });
        EventManager::getInstance().subscribe("RIGHT_STOP", "Player_RIGHTKEY", [&]() {
            if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_COMMON)return;
            if (GameManager::getInstance().globalVar[GLOBAL_PAUSED] == 1 || GameManager::getInstance().globalVar[GLOBAL_MENUING] == 1
                || GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;            
            Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
            ent->setSpeedX(0);
            //ent->setStatus(ENTITY_STATIC);
            });
        EventManager::getInstance().subscribe(CONVERSATION_BEGIN_EVENT, "StopEverything", []() {
            Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
            ent->setSpeedX(0), ent->setSpeedY(0);
            GameManager::getInstance().updateEntityPositions();
            });
        EventManager::getInstance().subscribe("Z_PRESS", "Player_ZKEY", [&]() {
            if (GameManager::getInstance().globalVar[GLOBAL_PAUSED] == 1 || GameManager::getInstance().globalVar[GLOBAL_MENUING] == 1
                || GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] == 1)return;            
            Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
            switch (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE]) {
            case GAME_STATE_COMMON:
                GameManager::getInstance().reactCheck();
                break;
            case GAME_STATE_MAINMENU:
                break;
            //case GAME_STATE_CONVERSATION:
            //    break;
            case GAME_STATE_CUTSCENE:
                break;
            case GAME_STATE_BATTLE:
                break;
            default:
                break;
            }
            
            });
   
#pragma endregion


    //EventManager::getInstance().subscribe("Z_PRESS", "GoIntoTest",[&]() {
    //    if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] == GAME_STATE_MAINMENU) {
    //        //GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_COMMON;
    //        GameManager::getInstance().setRoom(ROOM_TEST);
    //    }
    //    });

    GameManager::getInstance().setRoom(ROOM_MAINMENU,GAME_STATE_MAINMENU);

    SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);

}

void gamePause() {
    Entity* ent = GameManager::getInstance().entities[ENTITY_MAIN_PLAYER];
    ent->setSpeedX(0), ent->setSpeedY(0);
    if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_COMMON)return;
    if (GameManager::getInstance().globalVar[GLOBAL_MENUING] ||GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION])return;
    AudioManager::getInstance().playSound("SND_CHOOSE_BIG");
    if (GameManager::getInstance().globalVar[GLOBAL_PAUSED]) {
        GameManager::getInstance().globalVar[GLOBAL_PAUSED] = 0;
        Canvas::getInstance().getObject("Pause_Menu_Box").switchState(DRAW_VISIBLE, 0);
        Canvas::getInstance().getObject("Pause_Menu_Resume").switchState(DRAW_VISIBLE, 0);
        Canvas::getInstance().getObject("Pause_Menu_Exit").switchState(DRAW_VISIBLE, 0);
        EventManager::getInstance().emit("GAME_RESUME");
    }
    else {
        GameManager::getInstance().globalVar["PAUSE_MENU_SELECT"] = 0;
        GameManager::getInstance().globalVar[GLOBAL_PAUSED] = 1;
        Canvas::getInstance().getObject("Pause_Menu_Resume").text = Text(L"继续游戏", RGB(255, 255, 0), 0, L"SimSun", 30);
        Canvas::getInstance().getObject("Pause_Menu_Exit").text = Text(L"退出游戏", RGB(255, 255, 255), 0, L"SimSun", 30);
        Canvas::getInstance().getObject("Pause_Menu_Box").switchState(DRAW_VISIBLE, 1);
        Canvas::getInstance().getObject("Pause_Menu_Resume").switchState(DRAW_VISIBLE, 1);
        Canvas::getInstance().getObject("Pause_Menu_Exit").switchState(DRAW_VISIBLE, 1);
        EventManager::getInstance().emit("GAME_PAUSE");
    }
}
void showMenu() {
    auto& gm = GameManager::getInstance();
    gameMenuSwitch(0);
}
void hideMenu() {
    auto& cv = Canvas::getInstance();
    cv.getObject("Menu_box_choose").switchState(DRAW_VISIBLE,0);
    cv.getObject("Menu_box_state").switchState(DRAW_VISIBLE, 0);
    cv.getObject("Menu_box_inventory" ).switchState(DRAW_VISIBLE, 0);
    cv.getObject("Menu_box_choose_select_state").switchState(DRAW_VISIBLE, 0);
    cv.getObject("Menu_box_choose_select_inv").switchState(DRAW_VISIBLE, 0);
    cv.getObject("Menu_box_state_hp").switchState(DRAW_VISIBLE, 0);
    cv.getObject("Menu_box_state_gold").switchState(DRAW_VISIBLE, 0);

    cv.getObject("Menu_box_state_atk").switchState(DRAW_VISIBLE, 0);
    cv.getObject("Menu_box_state_def").switchState(DRAW_VISIBLE, 0);
    cv.getObject("Menu_box_state_lv").switchState(DRAW_VISIBLE, 0);
    cv.getObject("Menu_box_state_exp").switchState(DRAW_VISIBLE, 0);
       
    cv.getObject("Menu_box_inv_use").switchState(DRAW_VISIBLE, 0);
    cv.getObject("Menu_box_inv_disc").switchState(DRAW_VISIBLE, 0);
    cv.getObject("Menu_box_inv_text").switchState(DRAW_VISIBLE, 0);
    for (int i = 0; i < 8; i++) {
        cv.getObject("Menu_box_inv_" + std::to_string(i)).switchState(DRAW_VISIBLE, 0);
    }

}
void gameMenuSwitch(int lev) {
    auto& cv = Canvas::getInstance();
    auto& gm = GameManager::getInstance();
    if (lev == 0) {
        if(gm.globalVar["MENU_CHOOSE_0"]==0)
        {
            cv.getObject("Menu_box_choose_select_state").text.setTColor(RGB(255, 255, 0));
            cv.getObject("Menu_box_choose_select_inv").text.setTColor(RGB(255, 255, 255));
        }
        else {
            cv.getObject("Menu_box_choose_select_state").text.setTColor(RGB(255, 255, 255));
            cv.getObject("Menu_box_choose_select_inv").text.setTColor(RGB(255, 255, 0));

        }

        cv.getObject("Menu_box_choose").switchState(DRAW_VISIBLE,1);
        cv.getObject("Menu_box_choose_select_state").switchState(DRAW_VISIBLE, 1);
        cv.getObject("Menu_box_choose_select_inv").switchState(DRAW_VISIBLE, 1);
        cv.getObject("Menu_box_state_hp").switchState(DRAW_VISIBLE, 0);
        cv.getObject("Menu_box_state_gold").switchState(DRAW_VISIBLE, 0);
        cv.getObject("Menu_box_state_atk").switchState(DRAW_VISIBLE, 0);
        cv.getObject("Menu_box_state_def").switchState(DRAW_VISIBLE, 0);
        cv.getObject("Menu_box_state_lv").switchState(DRAW_VISIBLE, 0);
        cv.getObject("Menu_box_state_exp").switchState(DRAW_VISIBLE, 0);
        cv.getObject("Menu_box_state").switchState(DRAW_VISIBLE, 0);
        cv.getObject("Menu_box_inventory").switchState(DRAW_VISIBLE, 0);
           
        cv.getObject("Menu_box_inv_use").switchState(DRAW_VISIBLE, 0);
        cv.getObject("Menu_box_inv_disc").switchState(DRAW_VISIBLE, 0);
        cv.getObject("Menu_box_inv_text").switchState(DRAW_VISIBLE, 0);
        for (int i = 0; i < 8; i++) {
            cv.getObject("Menu_box_inv_" + std::to_string(i)).switchState(DRAW_VISIBLE, 0);
        }
    }
    else if (lev == 1) {
        if(gm.globalVar["MENU_CHOOSE_0"]==0)
        {
            cv.getObject("Menu_box_state_hp").text.setContent(L"HP:" + std::to_wstring(gm.globalVar[GLOBAL_PLAYER_HP]) + L"/" +
                std::to_wstring(gm.savingVar[GLOBAL_PLAYER_MAXHP]));
            cv.getObject("Menu_box_state_gold").text.setContent(L"GOLD:" + std::to_wstring(gm.savingVar[GLOBAL_PLAYER_GOLD]));
            cv.getObject("Menu_box_state_atk").text.setContent(L"ATK:" + std::to_wstring(gm.savingVar[GLOBAL_PLAYER_ATK]));
            cv.getObject("Menu_box_state_def").text.setContent(L"DEF:" + std::to_wstring(gm.savingVar[GLOBAL_PLAYER_DEF]));
            cv.getObject("Menu_box_state_lv").text.setContent(L"LV:" + std::to_wstring(gm.savingVar[GLOBAL_PLAYER_LV]));
            cv.getObject("Menu_box_state_exp").text.setContent(L"EXP:" + std::to_wstring(gm.savingVar[GLOBAL_PLAYER_EXP]));

            cv.getObject("Menu_box_state_hp").switchState(DRAW_VISIBLE, 1);
            cv.getObject("Menu_box_state_gold").switchState(DRAW_VISIBLE, 1);
            cv.getObject("Menu_box_state_atk").switchState(DRAW_VISIBLE, 1);
            cv.getObject("Menu_box_state_def").switchState(DRAW_VISIBLE, 1);
            cv.getObject("Menu_box_state_lv").switchState(DRAW_VISIBLE, 1);
            cv.getObject("Menu_box_state_exp").switchState(DRAW_VISIBLE, 1);
            cv.getObject("Menu_box_state").switchState(DRAW_VISIBLE, 1);
        }
        else if (gm.globalVar["MENU_CHOOSE_0"] == 1) {

            cv.getObject("Menu_box_inventory").switchState(DRAW_VISIBLE,1);
            cv.getObject("Menu_box_inv_text").switchState(DRAW_VISIBLE, 0);

            cv.getObject("Menu_box_inv_use").text.setTColor(RGB(255, 255, 255));
            cv.getObject("Menu_box_inv_disc").text.setTColor(RGB(255,255,255));
            cv.getObject("Menu_box_inv_use").switchState(DRAW_VISIBLE, 1);
            cv.getObject("Menu_box_inv_disc").switchState(DRAW_VISIBLE, 1);
            cv.getObject("Menu_box_inv_text").text.setContent(L"");
            cv.getObject("Menu_box_inv_text").switchState(DRAW_VISIBLE, 1);
            for (int i = 0; i < 8; i++) {
                cv.getObject("Menu_box_inv_" + std::to_string(i)).text.setContent(L"");
                cv.getObject("Menu_box_inv_" + std::to_string(i)).text.setTColor(RGB(255,255,255));
                if (i >= gm.inventory.size())continue;
                cv.getObject("Menu_box_inv_" + std::to_string(i)).text.setContent(to_wide_string(gm.inventory[i]));
                cv.getObject("Menu_box_inv_" + std::to_string(i)).switchState(DRAW_VISIBLE, 1);
            }
            gm.globalVar["MENU_CHOOSE_1"] = 0;
            cv.getObject("Menu_box_inv_0").text.setTColor(RGB(255, 255, 0));
        }
    }
    else if (lev == 2) {
        gm.globalVar["MENU_CHOOSE_2"] = 0;
        cv.getObject("Menu_box_inv_use").text.setTColor(RGB(255,255,0));
        cv.getObject("Menu_box_inv_disc").text.setTColor(RGB(255,255,255));
        cv.getObject("Menu_box_inv_text").text.setContent(to_wide_string(ItemManager::getInstance().getItem(gm.inventory[
            gm.globalVar["MENU_CHOOSE_1"]
        ]).itemDescription));
        cv.getObject("Menu_box_inv_text").switchState(DRAW_VISIBLE, 1);
    }
}