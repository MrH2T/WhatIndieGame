#define _CRT_SECURE_NO_WARNINGS
#include"Battle.h"

#include"../Manager/Managers.h"
#include"../Utils/Canvas.h"
#include<codecvt>


Battle::Attack::Bullet::Bullet() {
	id=speed = damage = length = 0;
	state = 0;
	type = 0;
	pos = posY = 0;
	hasSpecial = 0;
	specialFunc = NULL;
}
Battle::Attack::Bullet::Bullet(int id,int sp, int pos, int dm, int length,int type) {
	this->id = id;
	speed = sp, damage = dm, this->length = length;
	state = 0;
	this->pos = pos;
	posY = BULLET_START_HEIGHT;
	hasSpecial = 0;
	specialFunc = NULL;
	if (length == BULLET_NORMAL_LENGTH) this->type = type;
	else this->type = 1;
}
Battle::Attack::Bullet::Bullet(int id, int sp, int pos, int dm, int length, std::function<bool()> func,int type) {
	this->id = id;
	speed = sp, damage = dm, this->length = length;
	state = 0;
	this->pos = pos;
	posY = BULLET_START_HEIGHT;
	hasSpecial = 1;
	specialFunc = func;
	this->type = 3;
}
void Battle::Attack::addBullet(Bullet& bul) {
	bullet_going[bul.pos].push_back(bul);
	Canvas::getInstance().addObject("Bullet" + std::to_string(bul.id),
		DrawableObject(Animation(
			subBitmap(ResourceManager::getInstance().getResource("BATTLE_BULLETS"),{0,bul.type*10,60,bul.type*10+10}),1,1,1,60,10
		), BATTLE_STRIP_POS[bul.pos], std::max(BATTLE_BOX_ENDLINE - bul.posY - bul.length, BATTLE_BOX_ENDLINE - 390),
			{0,0,60,std::min(bul.length,std::max(0,BATTLE_BOX_HEIGHT-bul.posY))},7,DRAW_ABSOLUTE|DRAW_VISIBLE));

}
bool Battle::Attack::checkBulletState(Bullet& bul,int type) {
	//normal check
	if(type==0)
	{
		if (bul.type != 1 && bul.posY < -5 || bul.type == 1 && bul.posY < -5 && bul.state == 0) {
			Battle::getInstance().causeDamage(bul.damage);
			Canvas::getInstance().deleteObject("Bullet" + std::to_string(bul.id));
			AudioManager::getInstance().playSound("SND_PLAYERHURT");
			return true;
		}
		if (bul.type == 1 && bul.posY + bul.length < Battle::getInstance().press_height &&bul.state==1) {
			AudioManager::getInstance().playSound("SND_BULLET_DING");
			Canvas::getInstance().deleteObject("Bullet" + std::to_string(bul.id));
			return true;
		}
		return false;
	}
	// press button check
	else if (type == 1) {
		if (bul.posY > BATTLE_DETECT_HEIGHT)return false;
		if (bul.type != 1) {

			if (bul.posY > Battle::getInstance().press_height+3)
			{
				Battle::getInstance().causeDamage(bul.damage);
				AudioManager::getInstance().playSound("SND_PLAYERHURT");
			}
			else AudioManager::getInstance().playSound("SND_BULLET_DING");
			Canvas::getInstance().deleteObject("Bullet" + std::to_string(bul.id));
			return true;
		}
		else {
			bul.state = 1;
			return false;
		}
	}
	//stop button check
	else if (type == 2) {
		if (bul.type == 1 && bul.state == 1) {
			Battle::getInstance().causeDamage(bul.damage);
			AudioManager::getInstance().playSound("SND_PLAYERHURT");
			Canvas::getInstance().deleteObject("Bullet" + std::to_string(bul.id));
			return true;
		}
	}
	return false;
}
void Battle::Attack::updateBulletDraw(Bullet& bul) {
	auto& buldraw = Canvas::getInstance().getObject("Bullet" + std::to_string(bul.id));
	buldraw.posX = BATTLE_STRIP_POS[bul.pos];
	buldraw.posY = std::max(BATTLE_BOX_ENDLINE - bul.posY - bul.length, BATTLE_BOX_ENDLINE - 390);
	buldraw.expandBox = { 0,0,60,
		std::min( 
			bul.length+std::min(0,bul.posY),
			std::max(0,BATTLE_BOX_HEIGHT - std::max(0,bul.posY)))};
}
void Battle::Attack::updateBullets() {
	curTime++;
	static bool checker = 0;
	if (curBul >= bullets.size()) {
		bool flag = 1;
		for (int i = 0; i < 3; i++)if (!bullet_going[i].empty())flag = 0;
		if (flag && !checker) {
			checker = 1;
			GameManager::getInstance().addWaiting([]() {
			Battle::getInstance().localVar["ATTACK_STATE"] = 2;}, 10);
			return;
		}
		else if (checker)return;
	}
	checker = 0;
	while (curBul < bullets.size() && curTime == bullets[curBul].first) {
		addBullet(bullets[curBul].second);
		curBul++;
	}

	std::vector<Bullet> temp1[3];
	temp1[0].clear(), temp1[1].clear(), temp1[2].clear();

	for(int i=0;i<3;i++)
	for (auto& bl : bullet_going[i]) {
		if (bl.hasSpecial)
		{
			bool ret=bl.specialFunc();
			if (ret == true) {
				bl.state = 3;
				continue;
			}
		}
		bl.posY -= bl.speed;
		bool flag=checkBulletState(bl,0);
		if (flag) bl.state = 3;	
	}
	for (int i = 0; i < 3; i++)
		for (auto& bl : bullet_going[i]) {
			if (bl.state != 3)temp1[i].push_back(bl),updateBulletDraw(bl);

		}
	bullet_going[0].clear(), bullet_going[1].clear(), bullet_going[2].clear();
	for(int i=0;i<3;i++)
	{
		for (int j = 0; j < temp1[i].size(); j++)bullet_going[i].push_back(temp1[i][j]);
	}
}
void Battle::Attack::setBullets(std::vector<std::pair<int, Bullet>> bul) {
	bullets = bul;
}
void Battle::Attack::moveBullet(int id, int posA, int posB, int posBY) {
	auto temp = bullet_going[posA];
	temp.clear();
	for (int i = 0; i < bullet_going[posA].size(); i++) {
		if (bullet_going[posA][i].id == id) {
			bullet_going[posA][i].pos = posB;
			bullet_going[posA][i].posY = posBY;
			bullet_going[posB].push_back(bullet_going[posA][i]);
			sort(bullet_going[posB].begin(), bullet_going[posB].end(), [](Bullet a, Bullet b) {return a.posY < b.posY; });
		}
		else temp.push_back(bullet_going[posA][i]);
	}
	//bullet_going[posA] = temp;
}
void Battle::Attack::battleCheck(int pos, int type) {
	if (bullet_going[pos].empty())return;
	bool flag=checkBulletState(bullet_going[pos][0], type+1);
	if (flag)bullet_going[pos].erase(bullet_going[pos].begin());
}
Battle::Attack::Attack() {
	curTime = curBul=0;
	bullets.clear();
	bullet_going[0].clear(), bullet_going[1].clear(), bullet_going[2].clear();
}
Battle::Attack::Attack(std::vector<std::pair<int, Bullet>> bul) {
	setBullets(bul);
	bullet_going[0].clear(), bullet_going[1].clear(), bullet_going[2].clear();
	curTime = curBul=0;
}
void Battle::Attack::clearBullets() {
	for (int i = 0; i < 3; i++) {
		for (auto bul : bullet_going[i]) {
			Canvas::getInstance().deleteObject("Bullet" + std::to_string(bul.id));
		}
	}
}
Battle::Attack::Bullet Battle::Attack::getBullet(int id) {
	for (int i = 0; i < 2; i++) {
		for (auto bl : bullet_going[i]) {
			if (bl.id == id) {
				return bl;
			}
		}
	}
	return Bullet();
}
Battle& Battle::getInstance() {
	static Battle instance;
	return instance;
}
void Battle::battleSysInit() {
	/* what to do?
	* canvas add: background, battle conversation (8 slots), battle buttons, cursor_btn and cursor_item, 
	*	attack box, detect_light*3(with two states),   player_battle draw, enemy_battle draw
	* event: Z press, X press
	*/

#pragma region CanvasBinding
	auto &cv = Canvas::getInstance();
	auto& rs = ResourceManager::getInstance();
	cv.addObject("Battle_background",
		DrawableObject(Animation(rs.getResource("BATTLE_BACKGROUND"),1,1,1,240,160)
			, 0, 0, {0,0,WINDOW_WIDTH,WINDOW_HEIGHT}, 5, DRAW_ABSOLUTE));
	cv.addObject("Battle_box",
		DrawableObject(Animation(rs.getResource("BATTLE_BOX"), 1, 1, 1, BATTLE_BOX_WIDTH, BATTLE_BOX_HEIGHT),
			BATTLE_BOX_X, BATTLE_BOX_Y, { 0,0,BATTLE_BOX_WIDTH,BATTLE_BOX_HEIGHT }, 6, DRAW_ABSOLUTE));
	cv.addObject("Battle_checkbox_0",
		DrawableObject(Animation(rs.getResource("BATTLE_CHECKBOX"), 2, 2, 1, 60, 10),
			BATTLE_STRIP_POS[0], BATTLE_BOX_Y + BATTLE_BOX_HEIGHT - 5 - 10, {0,0,63,10}, 8, DRAW_ABSOLUTE));
	cv.addObject("Battle_checkbox_1",
		DrawableObject(Animation(rs.getResource("BATTLE_CHECKBOX"), 2, 2, 1, 60, 10),
			BATTLE_STRIP_POS[1], BATTLE_BOX_Y + BATTLE_BOX_HEIGHT - 5 - 10, { 0,0,63,10 }, 8, DRAW_ABSOLUTE));
	cv.addObject("Battle_checkbox_2",
		DrawableObject(Animation(rs.getResource("BATTLE_CHECKBOX"), 2, 2, 1, 60, 10),
			BATTLE_STRIP_POS[2], BATTLE_BOX_Y + BATTLE_BOX_HEIGHT - 5 - 10, { 0,0,63,10 }, 8, DRAW_ABSOLUTE));
	cv.addObject("Battle_cursor",
		DrawableObject(
			Animation(ResourceManager::getInstance().getResource("STAR"), 1, 1, 1, 16, 16),
			0, 0, { 0,0,48,48 }, 7, DRAW_ABSOLUTE));
	cv.addObject("Battle_button_0",
		DrawableObject(Animation(subBitmap(rs.getResource("BATTLE_BUTTONS"),{0,0,228,46}),2,1,2,114,46),
			BATTLE_BUTTON_POS[0][0],BATTLE_BUTTON_POS[0][1],{0,0,171,69},6,DRAW_ABSOLUTE));
	cv.addObject("Battle_button_1",
		DrawableObject(Animation(subBitmap(rs.getResource("BATTLE_BUTTONS"), { 0,46,228,46*2 }), 2, 1, 2, 114, 46),
			BATTLE_BUTTON_POS[1][0], BATTLE_BUTTON_POS[1][1], { 0,0,171,69 }, 6, DRAW_ABSOLUTE));
	cv.addObject("Battle_button_2",
		DrawableObject(Animation(subBitmap(rs.getResource("BATTLE_BUTTONS"), { 0,46*2,228,46*3 }), 2, 1, 2, 114, 46),
			BATTLE_BUTTON_POS[2][0], BATTLE_BUTTON_POS[2][1], { 0,0,171,69 }, 6, DRAW_ABSOLUTE));
	cv.addObject("Battle_button_3",
		DrawableObject(Animation(subBitmap(rs.getResource("BATTLE_BUTTONS"), { 0,46*3,228,46*4 }), 2, 1, 2, 114, 46),
			BATTLE_BUTTON_POS[3][0], BATTLE_BUTTON_POS[3][1], { 0,0,171,69 }, 6, DRAW_ABSOLUTE));
	cv.addObject("Battle_dialog_box",
		DrawableObject(
			Animation(ResourceManager::getInstance().getResource("CONVERSATION_BOX"), 1, 1, 1, 886, 200),
			BATTLE_DIALOG_BOX_X, BATTLE_DIALOG_BOX_Y, 
			{ 0,0,BATTLE_DIALOG_BOX_WIDTH,BATTLE_DIALOG_BOX_HEIGHT }, 6, DRAW_ABSOLUTE));
	cv.addObject("Battle_text",
		DrawableObject(
			Text(L"", RGB(255, 255, 255), RGB(0, 0, 0), L"SimSun",25),
			BATTLE_DIALOG_BOX_X + 20, BATTLE_DIALOG_BOX_Y + 20, { 0,0,BATTLE_DIALOG_BOX_WIDTH - 40,BATTLE_DIALOG_BOX_HEIGHT - 40 }, 7, DRAW_ABSOLUTE));
	cv.addObject("Battle_HPBar",
		DrawableObject(
			Text(L"", RGB(255, 255, 255), RGB(0, 0, 0), L"SimSun",23,0,TEXT_BOLD),
			WINDOW_WIDTH-250, BATTLE_DIALOG_BOX_Y + BATTLE_DIALOG_BOX_HEIGHT, { 0,0,140,30 }, 7, DRAW_ABSOLUTE
		));



	//TODO
	cv.addObject(ENEMY_DRAWOBJ,
		DrawableObject(Animation(), BATTLE_ENEMY_POS_X, BATTLE_ENEMY_POS_Y, {0,0,0,0}, 7, DRAW_ABSOLUTE|DRAW_AUTOTICK));
	//TO BE REPLACED BY BATTLE ANIMS

	Animation sub3 = Animation(rs.getResource("NIKO_BATTLE"), 3, 3, 1, 168, 58);
	player_anims = {
		Animation(sub3.getFrame(0),4,1,4,42,58,3),
		Animation(sub3.getFrame(1),4,1,4,42,58,3),
		Animation(sub3.getFrame(2),4,1,4,42,58,3),
	};
	player_dying = Animation(rs.getResource("NIKO_DYING"), 1,1, 1, 42, 58);
	cv.addObject(PLAYER_DRAWOBJ,
		DrawableObject(player_anims[0], BATTLE_PLAYER_POS_X, BATTLE_PLAYER_POS_Y-116, {0,0,42*2,58*2}, 7, DRAW_ABSOLUTE | DRAW_AUTOTICK));


	for (int i = 0; i < 4; i++) {
		cv.addObject(std::string("Battle_item_")+char(i+48),
			DrawableObject(
				Text(L"", RGB(255, 255, 255), RGB(0, 0, 0), L"SimSun",25), 
				BATTLE_ITEM_POS[i][0], BATTLE_ITEM_POS[i][1], {0,0,BATTLE_ITEM_WIDTH,BATTLE_ITEM_HEIGHT}, 7, DRAW_ABSOLUTE));
	}
#pragma endregion

#pragma region EventBinding
	auto& ev = EventManager::getInstance();
	ev.subscribe("Z_PRESS", "BattleZP", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_BATTLE)return;
		if (battleState() == BATTLE_ACTING) {
			if (choice_level == 0) {
				AudioManager::getInstance().playSound("SND_CHOOSE_BIG");
				Canvas::getInstance().getObject("Battle_text").switchState(DRAW_VISIBLE, 0);
				if (button_choice == 0) {
					choice_level = 1;
					useAttack();
				}
				else if (button_choice == 1) {
					choice_level = 1;
					useAct();
				}
				else if (button_choice == 2) {
					choice_level = 1;
					useInventory();
				}
				else if (button_choice == 3) {
					choice_level = 0;
					useMercy();
				}
			}
			else if(choice_level==1){
				handleChoose();
			}
		}
		});
	ev.subscribe("X_PRESS", "BattleXP", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_BATTLE)return;
		if (battle_state != BATTLE_ACTING)return;
		if (choice_level == 1) {
			item_choice = 0;
			choice_level = 0;
			auto& cv = Canvas::getInstance();
			for (int i = 0; i < 4; i++) {
				cv.getObject("Battle_item_" + std::to_string(i)).switchState(DRAW_VISIBLE,0 );
				
			}
			AudioManager::getInstance().playSound("SND_CHOOSE_BIG");
			Canvas::getInstance().getObject("Battle_text").switchState(DRAW_VISIBLE, 1);
			drawingUpdate();
		}
		});
	ev.subscribe("UP_PRESS", "BattleUP", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_BATTLE)return;
		if (battleState() == BATTLE_ACTING) {
			if (choice_level == 1) {
				if (item_choice == 2 || item_choice == 3) {
					AudioManager::getInstance().playSound("SND_CHOOSE");
					item_choice -= 2;
				}
			}
		}
		else if (battleState() == BATTLE_BULLET) {
			cv.getObject("Battle_checkbox_1").anim.setCurFrame(1);
			curAttack.battleCheck(1);
		}
		});
	ev.subscribe("UP_STOP", "BattleUS", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_BATTLE)return;
		if (battleState() == BATTLE_BULLET) {
			cv.getObject("Battle_checkbox_1").anim.setCurFrame(0);
			curAttack.battleCheck(1,1);
		}
		});
	ev.subscribe("DOWN_PRESS", "BattleDP", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_BATTLE)return;
		if (battleState() == BATTLE_ACTING) {
			if (choice_level == 1) {
				if (item_choice == 0 || item_choice == 1) {
					if(item_func.size()>item_choice+4*inv_page+2)
					{
						AudioManager::getInstance().playSound("SND_CHOOSE");
						item_choice += 2;
					}
				}
			}
		}
		});
	ev.subscribe("LEFT_PRESS", "BattleLP", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_BATTLE)return;
		if (battleState() == BATTLE_ACTING) {
			if (choice_level == 0) {
				if (button_choice > 0)button_choice--, AudioManager::getInstance().playSound("SND_CHOOSE");
			}
			else if (choice_level == 1) {
				if (item_choice == 1 || item_choice == 3) {
					AudioManager::getInstance().playSound("SND_CHOOSE");
					item_choice--;
				}
				else if (inv_page == 1 && (item_choice == 0 || item_choice == 2)) {
					AudioManager::getInstance().playSound("SND_CHOOSE");
					item_choice++;
					inv_page = 0;
				}
			}
			drawingUpdate();
		}
		else if (battleState() == BATTLE_BULLET) {
			cv.getObject("Battle_checkbox_0").anim.setCurFrame(1);
			curAttack.battleCheck(0);
		}
		});
	ev.subscribe("LEFT_STOP", "BattleLS", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_BATTLE)return;
		if (battleState() == BATTLE_BULLET) {
			cv.getObject("Battle_checkbox_0").anim.setCurFrame(0);
			curAttack.battleCheck(0, 1);
		}
		});
	ev.subscribe("RIGHT_PRESS", "BattleRP", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_BATTLE)return;
		if (battleState() == BATTLE_ACTING) {
			if (choice_level == 0) {
				if (button_choice < 3)button_choice++, AudioManager::getInstance().playSound("SND_CHOOSE");
			}
			else if (choice_level == 1) {
				if (item_choice == 0 || item_choice == 2) {
					if (item_func.size() > item_choice+4 * inv_page + 1)
					{
						AudioManager::getInstance().playSound("SND_CHOOSE");
						item_choice++;
					}
				}
				else if (inv_page == 0 && (item_choice == 1 || item_choice == 3)) {
					if(item_func.size()>item_choice+ 4 * inv_page +3)
					{
						AudioManager::getInstance().playSound("SND_CHOOSE");
						item_choice--;
						inv_page = 1;
					}
				}
			}
			drawingUpdate();
		}
		else if (battleState() == BATTLE_BULLET) {
			cv.getObject("Battle_checkbox_2").anim.setCurFrame(1);
			curAttack.battleCheck(2);
		}
		});
	ev.subscribe("RIGHT_STOP", "BattleRS", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_BATTLE)return;
		if (battleState() == BATTLE_BULLET) {
			cv.getObject("Battle_checkbox_2").anim.setCurFrame(0);
			curAttack.battleCheck(2, 1);
		}
		});

#pragma endregion
}

void Battle::setEnemy(std::string enemy, int hp, int def,std::vector<Animation> anims,RECT eBox) {
	enemy_name = enemy;
	enemy_hp = enemy_maxhp=hp,enemy_def=def;
	enemy_anims = anims;
	Canvas::getInstance().getObject(ENEMY_DRAWOBJ).expandBox = eBox;
	Canvas::getInstance().getObject(ENEMY_DRAWOBJ).posY = BATTLE_ENEMY_POS_Y-eBox.bottom;
}
Battle::Attack& Battle::getCurAttack() {
	return curAttack;
}
void Battle::setAttack(Attack atk) {
	curAttack = atk;
}
void Battle::runAttack(){
	localVar["ATTACK_STATE"] = 1;
}
void Battle::setConv(ConvSeq conv) {
	battleConv = conv;
}
void Battle::runConv() {
	ConversationSequence::getInstance().setSequence(battleConv);
	ConversationSequence::getInstance().startBattleConv();
}

void Battle::switchState(int st) {
	drawingUpdate();
	auto& cv = Canvas::getInstance();
	if (battle_state == BATTLE_ACTING) {
		cv.getObject("Battle_dialog_box").switchState(DRAW_VISIBLE,0);
		cv.getObject("Battle_text").switchState(DRAW_VISIBLE, 0);
		cv.getObject("Battle_cursor").switchState(DRAW_VISIBLE, 0);
		for (int i = 0; i < 4; i++) {
			cv.getObject("Battle_item_" + std::to_string(i)).switchState(DRAW_VISIBLE, 0);
		}
		for (int i = 0; i < 4; i++) {
			cv.getObject("Battle_button_" + std::to_string(i)).anim.setCurFrame(0);
		}
	}
	else if (battle_state == BATTLE_DIALOG) {

	}
	else if (battle_state == BATTLE_BULLET) {
		cv.getObject("Battle_box").switchState(DRAW_VISIBLE, 0);
		cv.getObject("Battle_checkbox_0").switchState(DRAW_VISIBLE, 0);
		cv.getObject("Battle_checkbox_1").switchState(DRAW_VISIBLE, 0);
		cv.getObject("Battle_checkbox_2").switchState(DRAW_VISIBLE, 0);
		cv.getObject("Battle_checkbox_0").anim.setCurFrame(0);
		cv.getObject("Battle_checkbox_1").anim.setCurFrame(0);
		cv.getObject("Battle_checkbox_2").anim.setCurFrame(0);
		
	}
	if (st == BATTLE_ACTING) {
		cv.getObject("Battle_cursor").switchState(DRAW_VISIBLE, 1);
		cv.getObject("Battle_dialog_box").switchState(DRAW_VISIBLE, 1);
		cv.getObject("Battle_text").switchState(DRAW_VISIBLE, 1);
		choice_level = 0;
		button_choice = 0;
		item_choice = 0;
	}
	else if (st == BATTLE_DIALOG) {
		
	}
	else if (st == BATTLE_BULLET) {
		cv.getObject("Battle_box").switchState(DRAW_VISIBLE, 1);
		cv.getObject("Battle_checkbox_0").posY= BATTLE_BOX_Y + BATTLE_BOX_HEIGHT - 5 - press_height;
		cv.getObject("Battle_checkbox_1").posY = BATTLE_BOX_Y + BATTLE_BOX_HEIGHT - 5 - press_height;
		cv.getObject("Battle_checkbox_2").posY = BATTLE_BOX_Y + BATTLE_BOX_HEIGHT - 5 - press_height;
		cv.getObject("Battle_checkbox_0").expandBox = { 0,0,60,press_height };
		cv.getObject("Battle_checkbox_1").expandBox = { 0,0,60,press_height };
		cv.getObject("Battle_checkbox_2").expandBox = { 0,0,60,press_height };
		cv.getObject("Battle_checkbox_0").switchState(DRAW_VISIBLE, 1);
		cv.getObject("Battle_checkbox_1").switchState(DRAW_VISIBLE, 1);
		cv.getObject("Battle_checkbox_2").switchState(DRAW_VISIBLE, 1);
		cv.getObject(PLAYER_DRAWOBJ).anim=player_anims[0];
		cv.getObject(PLAYER_DRAWOBJ).anim.setCurFrame(0);
	}
	battle_state = st;
	if (st == BATTLE_DIALOG)EventManager::getInstance().emit("BATTLE_DIALOG_START");
	drawingUpdate();

}
void Battle::causeDamage(int dm) {
	int realDamage = std::max(1, dm-GameManager::getInstance().savingVar[GLOBAL_PLAYER_DEF]);
	GameManager::getInstance().globalVar[GLOBAL_PLAYER_HP] = std::max(0,
		GameManager::getInstance().globalVar[GLOBAL_PLAYER_HP] - realDamage);
	Canvas::getInstance().getObject(PLAYER_DRAWOBJ).anim = player_anims[2];
	Canvas::getInstance().getObject(PLAYER_DRAWOBJ).anim.setCurFrame(0);
	GameManager::getInstance().addWaiting([]() {
		if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] != GAME_STATE_DYING)
			Canvas::getInstance().getObject(PLAYER_DRAWOBJ).anim = Battle::getInstance().player_anims[0]; }, 10);
	checkPlayer();
}
int Battle::causeAttack() {
	int realDamage = std::max(1,GameManager::getInstance().savingVar[GLOBAL_PLAYER_ATK] - enemy_def + rand()%11-5);
	enemy_hp = std::max(0, enemy_hp - realDamage);
	Canvas::getInstance().getObject(PLAYER_DRAWOBJ).anim = player_anims[1];
	Canvas::getInstance().getObject(PLAYER_DRAWOBJ).anim.setCurFrame(0);
	Canvas::getInstance().addObject("BATTLE_KNIFESLASH",
		DrawableObject(Animation(ResourceManager::getInstance().getResource("KNIFE_SLASH"), 2, 1, 2, 14, 70, 7),
			BATTLE_ENEMY_POS_X + 30, BATTLE_ENEMY_POS_Y - 140, { 0,0,28,140 }, 8, DRAW_ABSOLUTE | DRAW_VISIBLE|DRAW_AUTOTICK)
	);

	GameManager::getInstance().addWaiting([]() {
		Canvas::getInstance().getObject(PLAYER_DRAWOBJ).anim = Battle::getInstance().player_anims[0]; }, 20);
	checkEnemy();
	return realDamage;
}
void Battle::checkPlayer() {
	if (GameManager::getInstance().globalVar[GLOBAL_PLAYER_HP] <= 0) {
		GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_DYING;
		Canvas::getInstance().getObject(PLAYER_DRAWOBJ).anim = player_dying;
		AudioManager::getInstance().stopBgm();
		GameManager::getInstance().addWaiting([&]() {
			battleFinish(BATTLE_LOSE);
			GameManager::getInstance().gameOver(); }, 35);
	}
	drawingUpdate();
}
void Battle::checkEnemy() {
	if (enemy_hp <= 0) {
		battleFinish(BATTLE_WIN);
	}
}

void Battle::battleFinish(int what) {
	if (what == BATTLE_MERCY) {
		switchState(BATTLE_DIALOG);
		EventManager::getInstance().emit("BATTLE_END_MERCY");
	}
	else if (what == BATTLE_WIN) {
		switchState(BATTLE_DIALOG);
		EventManager::getInstance().emit("BATTLE_END_WIN");
	}
	else if (what == BATTLE_LOSE) {
		auto& bt = Battle::getInstance();
		bt.curAttack.clearBullets();
		bt.hideScene();
		bt.clearVars();
	}
}
void Battle::useMercy() {
	localVar[MERCY_USE] += 1;
	if (mercible()) {
		battleFinish(BATTLE_MERCY);
	}
	else {
		switchState(BATTLE_DIALOG);
		ConversationSequence::getInstance().setSequence(ConvSeq({
			[=]() {
				Conversation::getInstance().beginConversation(Text(L"* 似乎现在还不能饶恕它。"));
			},
			[]() {
				ConversationSequence::getInstance().stopBattleConv();
				Battle::getInstance().switchState(BATTLE_BULLET);
			}
			}));
		ConversationSequence::getInstance().startBattleConv();
	}
}

void Battle::useAct() {
	if (actions.empty()) {
		choice_level = 0;
		Canvas::getInstance().getObject("Battle_text").switchState(DRAW_VISIBLE, 1);
		return;
	}
	item_func = actions;
	item_choice = 0;
	auto& cv = Canvas::getInstance();
	for (int i = 0; i < 4; i++) {
		if (i >= item_func.size())break;
		if (item_func[i].first != "") {
			cv.getObject("Battle_item_" + std::to_string(i)).switchState(DRAW_VISIBLE, 1);
		}
	}
	drawingUpdate();
}

void Battle::useInventory() {
	item_func.clear();
	auto& inv = GameManager::getInstance().inventory;
	if (inv.empty()) {
		choice_level = 0;
		Canvas::getInstance().getObject("Battle_text").switchState(DRAW_VISIBLE, 1);
		return;
	}

	//add inventory
	for (int i = 0; i < inv.size(); i++) {
		auto item = ItemManager::getInstance().getItem(inv[i]);
		item_func.push_back({ item.itemName, [=]() {
			item.itemFunc(); 
			GameManager::getInstance().eraseItem(item.itemName); } });
	}
	item_choice = 0;
	inv_page = 0;
	auto& cv = Canvas::getInstance();
	for (int i = 0; i < 4; i++) {
		cv.getObject("Battle_item_" + std::to_string(i)).text.setContent(L"");
		if (i >= item_func.size())continue;
		if (item_func[i].first != "") {
			cv.getObject("Battle_item_" + std::to_string(i)).switchState(DRAW_VISIBLE, 1);
		}
	}
}

void Battle::useAttack() {
	item_func.clear();
	std::string str = (enemy_name) + "(HP " + std::to_string(enemy_hp) + "/" + std::to_string(enemy_maxhp)+")";
	item_choice = inv_page = 0;
	item_func.push_back(std::make_pair(str,
		[]() {
			int damage=Battle::getInstance().causeAttack(); 
			Battle::getInstance().localVar[ATTACK_USE] += 1;
			AudioManager::getInstance().playSound("SND_ATTACK");
			GameManager::getInstance().addWaiting([]() {AudioManager::getInstance().playSound("SND_ENEMYHIT"); Canvas::getInstance().deleteObject("BATTLE_KNIFESLASH"); }, 10);
			GameManager::getInstance().addWaiting([=]() {
				ConversationSequence::getInstance().setSequence(ConvSeq{ [=]() {Conversation::getInstance().beginConversation(Text(L"* 造成了" + std::to_wstring(damage) + L"点伤害")); },
					[]() {ConversationSequence::getInstance().stopBattleConv(); Battle::getInstance().switchState(BATTLE_DIALOG); } });
				ConversationSequence::getInstance().startBattleConv();
				},20);
			
		}));
	auto& cv = Canvas::getInstance();
	for (int i = 0; i < 4; i++) {
		if (i >= item_func.size())break;
		if (item_func[i].first != "") {
			cv.getObject("Battle_item_" + std::to_string(i)).switchState(DRAW_VISIBLE, 1);
		}
	}
	drawingUpdate();
}


void Battle::drawingUpdate() {
	auto& cv = Canvas::getInstance();
	cv.getObject("Battle_HPBar").text.setContent(std::wstring(L"HP: ") + std::to_wstring(GameManager::getInstance().globalVar[GLOBAL_PLAYER_HP])
		+ L"/" + std::to_wstring(GameManager::getInstance().savingVar[GLOBAL_PLAYER_MAXHP]));
	if (battle_state == BATTLE_ACTING) {
	//set cursor
		if (choice_level == 0) {
			cv.getObject("Battle_cursor").expandBox = { 0,0,36,36 };
			cv.getObject("Battle_cursor").posX = BATTLE_BUTTON_POS[button_choice][0]+5;
			cv.getObject("Battle_cursor").posY = BATTLE_BUTTON_POS[button_choice][1]+15;
		}
		else if (choice_level == 1) {
			cv.getObject("Battle_cursor").expandBox = { 0,0,24,24 };
			cv.getObject("Battle_cursor").posX = BATTLE_ITEM_POS[item_choice][0]-24;
			cv.getObject("Battle_cursor").posY = BATTLE_ITEM_POS[item_choice][1];
		}
		if (choice_level == 0) {
			cv.getObject("Battle_text").text.setContent(to_wide_string(text).c_str());
		}
		else {
			for (int i = 0; i < 4; i++) {
				
				if (i +4*inv_page>= item_func.size()) {
					cv.getObject("Battle_item_" + std::to_string(i)).text.setContent(L"");
					continue;
				}
				if (item_func[i].first != "") {
					cv.getObject("Battle_item_" + std::to_string(i)).text.setContent(to_wide_string(item_func[i+4*inv_page].first).c_str());
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			cv.getObject("Battle_button_" + std::to_string(i)).anim.setCurFrame(i==button_choice);
		}

	}
	else if (battle_state == BATTLE_DIALOG) {

	}
	else if (battle_state == BATTLE_BULLET) {

	}
	

}
void Battle::handleChoose() {
	switchState(BATTLE_DESCRI);
	item_func[item_choice].second();

}
int& Battle::battleState() {
	return battle_state;
}

void Battle::showScene() {
	auto& cv = Canvas::getInstance();
	cv.getObject("Battle_background").switchState(DRAW_VISIBLE, 1);
	cv.getObject("Battle_button_0").switchState(DRAW_VISIBLE, 1);
	cv.getObject("Battle_button_1").switchState(DRAW_VISIBLE, 1);
	cv.getObject("Battle_button_2").switchState(DRAW_VISIBLE, 1);
	cv.getObject("Battle_button_3").switchState(DRAW_VISIBLE, 1);
	cv.getObject("Battle_HPBar").switchState(DRAW_VISIBLE, 1);
	cv.getObject(ENEMY_DRAWOBJ).anim = enemy_anims[0];

	cv.getObject(ENEMY_DRAWOBJ).switchState(DRAW_VISIBLE, 1);
	cv.getObject(PLAYER_DRAWOBJ).switchState(DRAW_VISIBLE, 1);
}
void Battle::hideScene() {
	auto& cv = Canvas::getInstance();
	cv.getObject("Battle_background").switchState(DRAW_VISIBLE, 0);
	cv.getObject("Battle_button_0").switchState(DRAW_VISIBLE, 0);
	cv.getObject("Battle_button_1").switchState(DRAW_VISIBLE, 0);
	cv.getObject("Battle_button_2").switchState(DRAW_VISIBLE, 0);
	cv.getObject("Battle_button_3").switchState(DRAW_VISIBLE, 0);
	cv.getObject("Battle_HPBar").switchState(DRAW_VISIBLE, 0);
	cv.getObject(ENEMY_DRAWOBJ).switchState(DRAW_VISIBLE, 0);
	cv.getObject(PLAYER_DRAWOBJ).switchState(DRAW_VISIBLE, 0);
	cv.getObject("Battle_box").switchState(DRAW_VISIBLE, 0);
	cv.getObject("Battle_checkbox_0").switchState(DRAW_VISIBLE, 0);
	cv.getObject("Battle_checkbox_1").switchState(DRAW_VISIBLE, 0);
	cv.getObject("Battle_checkbox_2").switchState(DRAW_VISIBLE, 0);
	cv.getObject("Battle_cursor").switchState(DRAW_VISIBLE, 0);
	cv.getObject("Battle_dialog_box").switchState(DRAW_VISIBLE, 0);
	cv.getObject("Battle_text").switchState(DRAW_VISIBLE, 0);
	for (int i = 0; i < 4; i++) {
		cv.getObject(std::string("Battle_item_") + char(i + 48)).switchState(DRAW_VISIBLE, 0);
	}

}
void Battle::clearVars() {
	actions.clear();
	localVar.clear();
	mercible = NULL;
	battle_state = 0;
	text = "";
	button_choice = item_choice = choice_level = 0;
	curAttack = Attack();
	Canvas::getInstance().getObject("Battle_checkbox_0").anim.setCurFrame(0);
	Canvas::getInstance().getObject("Battle_checkbox_1").anim.setCurFrame(0);
	Canvas::getInstance().getObject("Battle_checkbox_2").anim.setCurFrame(0);
}
void Battle::battleUpdate() {
	if (GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] == GAME_STATE_DYING) {
		return;
	}
	if(localVar["ATTACK_STATE"]==1)
	{
		// attacking
		curAttack.updateBullets();
	}
	else if (localVar["ATTACK_STATE"] == 2) {
		// just finished
		localVar["ATTACK_STATE"] = 0;
		EventManager::getInstance().emit("BATTLE_NEW_TURN");
	}
	drawingUpdate();
}
BattleController& BattleController::getInstance() {
	static BattleController instance;
	return instance;
}
void BattleController::setProcess(std::function<void()> func) {
	process = func;
}
void BattleController::startBattle() {
	GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_BATTLE;
	auto& bt = Battle::getInstance();
	bt.clearVars();
	EventManager::getInstance().emit("BATTLE_START");
	process();
}
void BattleController::endBattle() {
	EventManager::getInstance().emit("BATTLE_END");

	auto& bt = Battle::getInstance();
	bt.hideScene();
	bt.clearVars();

	GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_COMMON;
}