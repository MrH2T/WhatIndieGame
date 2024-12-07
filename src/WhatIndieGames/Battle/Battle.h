#pragma once
#include"../Manager/Managers.h"
#include"../Utils/Canvas.h"
#include"../Utils/Conversation.h"

#define BULLET_START_HEIGHT (400-5)
#define BULLET_NORMAL_LENGTH 10

#define BATTLE_DETECT_HEIGHT 40

#define BATTLE_ACTING 0
#define BATTLE_DIALOG 1
#define BATTLE_BULLET 2
#define BATTLE_FINISH 3
#define BATTLE_DESCRI 4

#define BATTLE_MERCY 0
#define BATTLE_WIN 1
#define BATTLE_LOSE 2

#define BATTLE_BOX_X (WINDOW_WIDTH/2-100)
#define BATTLE_BOX_Y (50)
#define BATTLE_BOX_WIDTH (200)
#define BATTLE_BOX_HEIGHT (400)
#define BATTLE_BOX_ENDLINE  (BATTLE_BOX_Y+BATTLE_BOX_HEIGHT-5)

#define BATTLE_DIALOG_BOX_X 5
#define BATTLE_DIALOG_BOX_Y 335
#define BATTLE_DIALOG_BOX_WIDTH 886
#define BATTLE_DIALOG_BOX_HEIGHT 200

#define BATTLE_PLAYER_POS_X 100
#define BATTLE_PLAYER_POS_Y 300
#define BATTLE_ENEMY_POS_X 700
#define BATTLE_ENEMY_POS_Y 300

#define MERCY_USE "MERCY_USE_VAR"
#define ATTACK_USE "ATTACK_USE_VAR"


//#define BATTLE_DIALOG_PROCEED_EVENT "Battle_Dialog_Proceed"

#define ENEMY_DRAWOBJ "BattleEnemyDrawobj"
#define PLAYER_DRAWOBJ "BattlePlayerDrawobj"

std::function<bool()> chgLine(int bid,int posL,int posR,int from,int to);

const int BATTLE_STRIP_POS[3] = { BATTLE_BOX_X + 7 ,BATTLE_BOX_X +7 + 63 ,BATTLE_BOX_X + 7 + 63 + 63 };
const int BATTLE_BUTTON_POS[4][2] = { {25,WINDOW_HEIGHT - 80-32},{25 + 171 + 50,WINDOW_HEIGHT - 80-32},
	{25 + 171 + 50 + 171 + 50, WINDOW_HEIGHT - 80-32},
	{25 + 171 + 50 + 171 + 50 + 171 + 50,WINDOW_HEIGHT - 80-32} };
const int BATTLE_ITEM_POS[4][2] = { {BATTLE_DIALOG_BOX_X + 5 + 5 + 24 + 3,BATTLE_DIALOG_BOX_Y + 5 + 5 + 40},
		{BATTLE_DIALOG_BOX_X + BATTLE_DIALOG_BOX_WIDTH / 2 + 5 + 5 + 24 + 3,BATTLE_DIALOG_BOX_Y + 5 + 5 + 40},
		{BATTLE_DIALOG_BOX_X + 5 + 5 + 24 + 3,BATTLE_DIALOG_BOX_Y + BATTLE_DIALOG_BOX_HEIGHT / 2 + 5 + 5 + 20},
		{BATTLE_DIALOG_BOX_X + BATTLE_DIALOG_BOX_WIDTH / 2 + 5 + 5 + 24 + 3,BATTLE_DIALOG_BOX_Y + BATTLE_DIALOG_BOX_HEIGHT / 2 + 5 + 5 + 20} };
#define BATTLE_ITEM_WIDTH (WINDOW_WIDTH/2)
#define BATTLE_ITEM_HEIGHT 60

class Battle {
public:
	class Attack {
	public:
		struct Bullet {
			//type 0: normal, 1: long, 2: hard, 3: change
			int id,type,state;
			// speed for Bullet
			int speed,damage,length;
			//pos: 0,1,2;  posY: (bottom posY) falling down, default a Set Value
			int pos, posY;

			bool hasSpecial;
			//specialFunc: if something interesting happens
			std::function<bool()> specialFunc;
			Bullet();
			Bullet(int id,int sp, int pos,int dm,int length=BULLET_NORMAL_LENGTH, int type=0);
			Bullet(int id,int sp, int pos, int dm, int length, std::function<bool()> func, int type=3);
		};
		//int: st time; Bullet: 
		std::vector<std::pair<int,Bullet> > bullets;
		//the existing bullet
		std::vector<Bullet> bullet_going[3];
		int curTime,curBul;
		//updateBullet: will do
		// 1. check bullet dropping from bullet_going
		// 2. check bullet spawn from bullets
		//		by: a cur_time var, add each update, check if equal to current position bullet
		//	bullets has normal length "taps" and long length "drags", long length can be determined, and normal length
		// should be fixed at ***(default)
		void addBullet(Bullet& bul);
		void moveBullet(int id, int posA, int posB,int posBY);
		void updateBullets();
		void updateBulletDraw(Bullet& bul);
		void setBullets(std::vector<std::pair<int, Bullet>> bul);
		void clearBullets();
		Bullet getBullet(int id);

		void battleCheck(int pos,int type=0);

		// if return true, the bullet is ended
		bool checkBulletState(Bullet& bul,int type);
		Attack(std::vector<std::pair<int, Bullet>> bul);
		Attack();
	};
	static Battle& getInstance();

	//run at beginning, init the system
	void battleSysInit();

	// enemy: name linked to canvas; 
	// anims: including: normal, attacking, being attacked
	// will do: create a drawobj at certain place
	void setEnemy(std::string enemy, int hp, int def,std::vector<Animation> anims,RECT eBox);



	void setConv(ConvSeq conv);
	void runConv();
	void setAttack(Attack atk);
	void runAttack();

	Attack& getCurAttack() ;
	// player use inventory 
	// relative: GameManager inventory managing
	void useInventory();
	
	// player do mercy
	// relative: mercy check
	void useMercy();

	//player do act
	// relative: <string,func> actions
	void useAct();


	//player do attack
	//relative: player.atk
	void useAttack();

	void handleChoose();



	// TODO
	void drawingUpdate();

	void battleUpdate();

	void switchState(int st);

	int& battleState();

	//to player
	void causeDamage(int dm);
	//to enemy
	int causeAttack();
	void checkPlayer();
	void checkEnemy();

	void showScene();
	void hideScene();

	void battleFinish(int what);

	void clearVars();


	std::vector<std::pair<std::string,std::function<void()>>> actions;
	std::map<std::string, int> localVar;
	std::function<bool()> mercible;
	std::string text;
	std::string enemy_name;
	int press_height; 
	int enemy_hp,enemy_def,enemy_maxhp;
private:
	Battle() { 
		actions.clear(), localVar.clear();
		button_choice = item_choice = choice_level = 0;
		press_height = 0;
		enemy_hp = enemy_def = 0;
		battle_state = 0;
	}
	std::vector<std::pair<std::string, std::function<void()>>> item_func;
	int button_choice,item_choice,choice_level;
	int inv_page; //0: 0-3, 1:4-7

	//detect height, has a default, may be changed

	//0: battle acting   1: battle dialog  2: battle bulletting   3: battle ending(die/win)
	int battle_state;


	//0: normal, 1: attacking, 2: hurt
	std::vector<Animation> enemy_anims,player_anims;
	Animation player_dying;

	Attack curAttack;
	ConvSeq battleConv;

};
class BattleController {
public:
	static BattleController& getInstance();
	// set a battle, many things to do, like bullets, actions, awards/results, 
	void setProcess(std::function<void()> func);
	// start the battle with given process
	void startBattle();
	// end the battle after 
	void endBattle();
private:
	BattleController() { process = NULL; }
	std::function<void()> process;
};