#pragma once

#pragma region ��������
#define WINDOW_TITLEBARHEIGHT	32			//�������߶�
#define WINDOW_WIDTH			(896+16)		//��Ϸ���ڿ��
#define WINDOW_HEIGHT			(640+32)		//��Ϸ���ڸ߶�

#define PAUSE_MENU_BOX_X	336
#define PAUSE_MENU_BOX_Y	256
#define PAUSE_MENU_BOX_WIDTH	224
#define PAUSE_MENU_BOX_HEIGHT	128

#define MENU_BOX_CHOOSE_X		30
#define MENU_BOX_CHOOSE_Y		70
#define MENU_INV_HEIGHT			400

#define MAIN_PLAYER_WIDTH 42
#define MAIN_PLAYER_HEIGHT 58


#define TIMER_GAMETIMER				1		//��Ϸ��Ĭ�ϼ�ʱ��ID
#define TIMER_GAMETIMER_ELAPSE		40		//Ĭ�ϼ�ʱ��ˢ�¼���ĺ�����

#define INVENTORY_SIZE 8
//�ߴ�




#pragma endregion



void initGame(HWND hWnd, WPARAM wParam, LPARAM lParam);
void gamePause();

void gameMenuSwitch(int lev);
void showMenu();
void hideMenu();


void timerTick(HWND hWnd, WPARAM wParam, LPARAM lParam);
void keyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);
void keyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);