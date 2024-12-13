#include"GameManager.h"
#include"../Utils/Canvas.h"


std::vector<Animation> groupBy4(HBITMAP image, int width, int height) {
	Animation allanimF = Animation(image, 16, 4, 4, width, height);
	Animation allanim4F = Animation(image, 4, 4, 1, width*4,height);
	return { Animation(allanim4F.getFrame(0),4,1,4,width,height,3),
		Animation(allanim4F.getFrame(1),4,1,4,width,height,3),
		Animation(allanim4F.getFrame(2),4,1,4,width,height,3),
		Animation(allanim4F.getFrame(3),4,1,4,width,height,3) };
	
}
std::vector<Animation> firstColumn(HBITMAP image, int width, int height){
	Animation allanimF = Animation(image, 16, 4, 4, width, height);
	return {
		Animation(allanimF.getFrame(0),1,1,1,width,height),
		Animation(allanimF.getFrame(4),1,1,1,width,height),
		Animation(allanimF.getFrame(8),1,1,1,width,height),
		Animation(allanimF.getFrame(12),1,1,1,width,height),
	};
}



bool rectCollide(RECT r1, RECT r2) {
	if (r1.right <= r2.left || r1.bottom <= r2.top || r1.left >= r2.right || r1.top >= r2.bottom)return false;
	return true;
}

GameManager& GameManager::getInstance() {
	static GameManager instance;
	return instance;
}
GameManager::GameManager() {
	globalVar.clear();
	globalVar.clear();
	entities.clear();
	curRoom = NULL;

}
void GameManager::gameUpdate() {
	updateEntityPositions();
	if(globalVar[GLOBAL_GAME_STATE]==GAME_STATE_BATTLE)
	{
		Battle::getInstance().battleUpdate();
	}

	if (curRoom != NULL)curRoom->roomUpdate();
	runWaiting();
}
bool GameManager::checkWalkable(std::string identifier, int x, int y, RECT c_box) {
	if (identifier != ENTITY_MAIN_PLAYER)return true;
	for (auto& ent : entities) {
		if (ent.first == identifier)continue;
		/*if (!(ent.second->getPos().x + ent.second->getCollisionBox().right <= x) && !(x + c_box.right <= ent.second->getPos().x)
			&& !(ent.second->getPos().y + ent.second->getCollisionBox().bottom <= y) && !(y+c_box.bottom <= ent.second->getPos().y )
			&& !ent.second->isPassable()) {
			return false;
		}*/
		RECT r1 = c_box, r2 = ent.second->getCollisionBox();
		r1.left += x, r1.right += x;
		r1.top += y, r1.bottom += y;
		r2.left += ent.second->getPos().x,r2.right+=ent.second->getPos().x;
		r2.top += ent.second->getPos().y, r2.bottom += ent.second->getPos().y;
		//FILE* dbg = NULL;
		//fopen_s(&dbg, "debug.txt", "a");
		///*if(ent.first=="Board1_drawobj")
		//	fprintf(dbg, "%d\n",rectCollide(r1,r2));*/
		//fclose(dbg);
		if (ent.second->isPassable() && ent.second->isOnCollide() && !rectCollide(r1, r2)) {
			ent.second->setOnCollide(false);
		}
		if (!ent.second->isPassable() && rectCollide(r1, r2)) {
			return false;
		}
		if (ent.second->isPassable() && rectCollide(r1, r2) && ent.second->isCollide()&&!ent.second->isOnCollide()) {
			ent.second->setOnCollide(true);
			addWaiting([&]() {ent.second->reactRun(); });
			return true;
		}
	}
	return true;
}
void GameManager::runWaiting() {
	if (waitingList.empty())return;
	std::vector<std::pair<std::function<void()>, int>> temp,temp1;
	temp1 = waitingList;
	waitingList.clear();
	temp.clear();
	for (auto& func : temp1) {
		if (func.second == 0) {
			func.first();
		}
		else {
			func.second--;
			temp.push_back(func);
		}
	}
	for (int i = 0; i < temp.size(); i++)waitingList.push_back(temp[i]);
	temp.clear(), temp1.clear();
}
void GameManager::addWaiting(std::function<void()> func,int delay) {
	waitingList.push_back(std::make_pair(func,delay));
}


void GameManager::addEntity(std::string entname, Entity* ent) {
	entities[entname] = ent;
}
void GameManager::deleteEntity(std::string entname) {
	entities.erase(entname);
}
Entity* GameManager::getEntity(std::string entname) {
	return entities[entname];
}
void GameManager::updateEntityPositions() {
	if (globalVar[GLOBAL_PAUSED] == 1||globalVar[GLOBAL_MENUING]==1)return;
	if (GameManager::getInstance().globalVar[GLOBAL_BATTLE_PREPARING])return;
	if (globalVar[GLOBAL_GAME_STATE] == GAME_STATE_BATTLE || globalVar[GLOBAL_GAME_STATE] == GAME_STATE_SHOP)return;
	for (auto& ent : entities) {
		ent.second->updatePosition();
	}
}
Coord GameManager::getSize() {
	switch (globalVar[GLOBAL_GAME_STATE]) {
	case GAME_STATE_COMMON:
		return { curRoom->getWidth(),curRoom->getHeight() };
	case GAME_STATE_CUTSCENE:
		return { curRoom->getWidth(),curRoom->getHeight() };
	//case GAME_STATE_CONVERSATION:
	//	return { curRoom->getWidth(),curRoom->getHeight() };
	default:
		return { WINDOW_WIDTH,WINDOW_HEIGHT };
	}
}
Coord GameManager::getBias() {
	if (globalVar[GLOBAL_GAME_STATE] != GAME_STATE_COMMON&&globalVar[GLOBAL_GAME_STATE]!=GAME_STATE_CUTSCENE)return {0,0};
	Coord player= entities[ENTITY_MAIN_PLAYER]->getPos();
	player.x += MAIN_PLAYER_WIDTH/2;
	player.y += MAIN_PLAYER_HEIGHT/2;
	int biasx = 0, biasy = 0;
	int reduced_width = WINDOW_WIDTH - 16, reduce_height = WINDOW_HEIGHT - 32;
	if (curRoom->getWidth() < reduced_width)biasx = -(reduced_width- curRoom->getWidth()) / 2;
	else {
		if (player.x < reduced_width / 2)biasx = 0;
		else if (player.x > curRoom->getWidth() - reduced_width / 2)biasx = curRoom->getWidth() - reduced_width;
		else biasx = player.x - reduced_width / 2;
	}
	if (curRoom->getHeight() < reduce_height)biasy = -(reduce_height - curRoom->getHeight())/2 ;
	else {
		if (player.y < reduce_height / 2)biasy = 0;
		else if (player.y > curRoom->getHeight() - reduce_height / 2)biasy = curRoom->getHeight() - reduce_height;
		else biasy = player.y - reduce_height / 2;
	}
	return { biasx,biasy};
}
void GameManager::setRoom(int roomid,int stat){
	globalVar[GLOBAL_GAME_STATE] = GAME_STATE_OTHER;
	if (curRoom != NULL) { 
		delete curRoom;
		curRoom = NULL;
	}
	curRoom = getRoom(roomid);
	globalVar[GLOBAL_GAME_STATE] = stat;
	//addWaiting([=]() {curRoom = getRoom(roomid); GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = stat; },0);
}

void GameManager::addItem(std::string name) {
	if (inventory.size() < INVENTORY_SIZE)inventory.push_back(name);
	else {
		ConversationSequence::getInstance().setSequence({
			[]() {Conversation::getInstance().beginConversation(Text(L"* 背包已经满了。")); }
			});
		ConversationSequence::getInstance().startConversation();
	}
}
void GameManager::eraseItem(std::string name) {
	bool flag = 0;
	std::vector < std::string> temp; temp.clear();
	for (auto i : inventory) {
		if (i == name && !flag) {
			flag = 1;
		}
		else temp.push_back(i);
	}
	inventory = temp;
}
void GameManager::addHP(int v) {
	globalVar[GLOBAL_PLAYER_HP] = std::min(globalVar[GLOBAL_PLAYER_HP] + v, savingVar[GLOBAL_PLAYER_MAXHP]);
}
void GameManager::addEXP(int v) {
	int& exp =savingVar[GLOBAL_PLAYER_EXP];
	exp+= v;
	if (exp >= 100)savingVar[GLOBAL_PLAYER_LV] = 5;
	else if (exp >= 80)savingVar[GLOBAL_PLAYER_LV] = 4;
	else if (exp >= 60)savingVar[GLOBAL_PLAYER_LV] = 3;
	else if (exp >= 30)savingVar[GLOBAL_PLAYER_LV] = 2;
	else if (exp >= 10)savingVar[GLOBAL_PLAYER_LV] = 1;
	else savingVar[GLOBAL_PLAYER_LV] = 0;
}
void GameManager::addGold(int v) {
	savingVar[GLOBAL_PLAYER_GOLD] += v;
}
void GameManager::reactCheck() {
	Entity* pl = entities[ENTITY_MAIN_PLAYER];
	int dir = pl->getDirection();
	RECT rec = pl->getCollisionBox();
	Coord pos = pl->getPos();
	RECT tar = rec;
	tar.left += pos.x, tar.right += pos.x;
	tar.top += pos.y, tar.bottom += pos.y;
	if (dir == DIRECTION_DOWN) {
		tar.top += rec.bottom-rec.top;
		tar.bottom += rec.bottom - rec.top;
	}
	else if (dir == DIRECTION_LEFT) {
		tar.left -= rec.right - rec.left;
		tar.right -= rec.right - rec.left;
	}
	else if (dir == DIRECTION_UP) {
		tar.top -= rec.bottom - rec.top;
		tar.bottom -= rec.bottom - rec.top;
	}
	else if (dir == DIRECTION_RIGHT){
		tar.left += rec.right - rec.left;
		tar.right += rec.right - rec.left;
	}
	for (auto &ent : entities) {
		if (ent.first == ENTITY_MAIN_PLAYER)continue;
		RECT ebox = ent.second->getCollisionBox();
		Coord epos = ent.second->getPos();
		ebox.left += epos.x, ebox.right += epos.x;
		ebox.top += epos.y, ebox.bottom += epos.y;
		if (rectCollide(tar, ebox)&&ent.second->isReact()) {
			//MessageBoxA(NULL,"?", "?", NULL);
			addWaiting([&]() {ent.second->reactRun(); });
		}
	}
}

void GameManager::gameSaving() {

	std::ofstream saving("saving.txt");
	AudioManager::getInstance().playSound("SND_SAVING");
	saving<<curRoom->roomId()<<std::endl;
	for (int i = 0; i < INVENTORY_SIZE; i++) {
		if (i >= inventory.size())saving << "0" << std::endl;
		else saving << inventory[i] << std::endl;
	}
	for (auto& it : savingVar) {
		saving << it.first << std::endl << it.second << std::endl;
	}
	saving.close();
}

bool GameManager::readSaving(){
	std::ifstream saving("saving.txt");
	if (!saving.good())return false;
	inventory.clear();
	savingVar.clear();
	int rmid = 0;
	saving >> rmid;
	for (int i = 0; i < 8; i++) {
		std::string str;
		saving >> str;
		if (str == "0")continue;
		else addItem(str);
	}
	std::string str1, str2;
	std::getline(saving, str1);
	while (std::getline(saving, str1)) {
		std::getline(saving, str2);
		savingVar[str1] = std::stoi(str2);
	}
	saving.close();
	globalVar[GLOBAL_PLAYER_HP] = savingVar[GLOBAL_PLAYER_MAXHP];
	globalVar[ROOM_ENTRANCE] = ROOM_ENTRY_SAVING;
	setRoom(rmid);
	return true;
}

void GameManager::gameOver() {
	setRoom(ROOM_GAMEOVER,GAME_STATE_CUTSCENE);

}
void GameManager::goMainMenu() {
	AudioManager::getInstance().stopBgm();
	setRoom(ROOM_MAINMENU,GAME_STATE_MAINMENU);
}
void GameManager::newGame() {
	inventory.clear();
	savingVar.clear();
	globalVar[GLOBAL_PLAYER_HP]=savingVar[GLOBAL_PLAYER_MAXHP] = 20;
	savingVar[GLOBAL_PLAYER_GOLD] = 0;
	savingVar[GLOBAL_PLAYER_ATK] = 2;
	savingVar[GLOBAL_PLAYER_DEF] = 0;
	savingVar[GLOBAL_PLAYER_EXP] = 0;
	savingVar[GLOBAL_PLAYER_LV] = 0;
	savingVar[GLOBAL_KILLS] = 0;
	
	setRoom(ROOM_FIRST);
}

void GameManager::helpRoom() {
	inventory.clear();

	globalVar[GLOBAL_PLAYER_HP] = savingVar[GLOBAL_PLAYER_MAXHP] = 100;
	savingVar[GLOBAL_PLAYER_GOLD] = 0;
	savingVar[GLOBAL_PLAYER_ATK] = 2;
	savingVar[GLOBAL_PLAYER_DEF] = 0;
	savingVar[GLOBAL_PLAYER_EXP] = 0;
	savingVar[GLOBAL_PLAYER_LV] = 0;

	setRoom(ROOM_HELP);
}
void GameManager::gameEscape() {
	PostQuitMessage(0);
}