#include"Conversation.h"
#include"../Manager/Managers.h"

Conversation::Choice::Choice() {
	proc = NULL;
	cursor_pos = -1;
}
Conversation::Choice::Choice(std::vector<Text> choice, std::function<void(int)> proc_func) {
	items = choice;
	proc=proc_func;
	cursor_pos = -1;
}
Conversation& Conversation::getInstance() {
	static Conversation instance;
	return instance;
}
void Conversation::clearConversation() {
	if (type == CONV_NONE)return;
	Canvas::getInstance().getObject("conversation_box").switchState(DRAW_VISIBLE, 0);
	if (type == CONV_PLAIN) {
		Canvas::getInstance().getObject("conversation_text").switchState(DRAW_VISIBLE,0);
	}
	if (type == CONV_PIC) {
		Canvas::getInstance().getObject("conversation_text").switchState(DRAW_VISIBLE,0);
		Canvas::getInstance().getObject("conversation_pic").switchState(DRAW_VISIBLE,0);
	}
	if (type == CONV_CHOICE) {
		for(int i=0;i<choice.items.size();i++)
		{
			std::string name = "conversation_choice";name+= char(i + 48);
			Canvas::getInstance().getObject(name).switchState(DRAW_VISIBLE,0);
		}
		Canvas::getInstance().getObject("conversation_cursor").switchState(DRAW_VISIBLE,0);
	}
	if (type == CONV_CHTEXT) {
		Canvas::getInstance().getObject("conversation_text").switchState(DRAW_VISIBLE, 0);
		for (int i = 0; i < choice.items.size(); i++)
		{
			std::string name = "conversation_choice"; name += char(i+48);
			Canvas::getInstance().getObject(name).switchState(DRAW_VISIBLE, 0);
		}
		Canvas::getInstance().getObject("conversation_cursor").switchState(DRAW_VISIBLE, 0);
	}
	type = CONV_NONE;
}
void Conversation::beginConversation(Text txt){
	clearConversation();
	type = CONV_PLAIN;
	Canvas::getInstance().getObject("conversation_box").switchState(DRAW_VISIBLE);
	DrawableObject& obj = Canvas::getInstance().getObject("conversation_text");
	obj.switchState(DRAW_VISIBLE);
	obj.posX = CONVERSATION_TEXT_POS[1][0];
	obj.posY = CONVERSATION_TEXT_POS[1][1]+ybias;
	obj.text = txt;
	obj.expandBox = RECT({ 0,0,CONVERSATION_TEXT_BOX[1][0],CONVERSATION_TEXT_BOX[1][1] });

}
void Conversation::beginConversation(Text txt, Animation pic) {
	clearConversation();
	type = CONV_PIC; 
	Canvas::getInstance().getObject("conversation_box").switchState(DRAW_VISIBLE);
	DrawableObject& obj = Canvas::getInstance().getObject("conversation_text");
	obj.switchState(DRAW_VISIBLE);
	obj.posX = CONVERSATION_TEXT_POS[2][0];
	obj.posY = CONVERSATION_TEXT_POS[2][1] + ybias;
	obj.text = txt;
	obj.expandBox = RECT({ 0,0,CONVERSATION_TEXT_BOX[2][0],CONVERSATION_TEXT_BOX[2][1] });

	DrawableObject& obj2 = Canvas::getInstance().getObject("conversation_pic");
	obj2.switchState(DRAW_VISIBLE);
	obj2.posX = CONVERSATION_PIC_POS[0];
	obj2.posY = CONVERSATION_PIC_POS[1] + ybias;
	obj2.anim = pic;
	obj2.expandBox = RECT({ 0,0,CONVERSATION_PIC_BOX[0],CONVERSATION_PIC_BOX[1]});
}
void Conversation::beginConversation(Choice ch) {
	clearConversation();
	type = CONV_CHOICE;
	Canvas::getInstance().getObject("conversation_box").switchState(DRAW_VISIBLE);
	choice = ch;
	choice.cursor_pos = 0;
	int count = choice.items.size();
	for (int i = 0; i < count; i++) {
		std::string name = "conversation_choice";name+= char(i + 48);
		//MessageBoxA(NULL, name.c_str(), "", NULL);
		DrawableObject& obj2 = Canvas::getInstance().getObject(name);
		obj2.switchState(DRAW_VISIBLE);
		obj2.text = choice.items[i];
		obj2.posX = CONVERSATION_CHOICE_POS[count][i][0];
		obj2.posY = CONVERSATION_CHOICE_POS[count][i][1] + ybias;
		obj2.expandBox = RECT({ 0,0,CONVERSATION_CHOICE_BOX[count][0],CONVERSATION_CHOICE_BOX[count][1] });
	}
	AudioManager::getInstance().playSound("SND_CHOOSE");
	drawCursor();
}
void Conversation::beginConversation(Text txt, Choice ch) {
	clearConversation();
	type = CONV_CHTEXT;
	Canvas::getInstance().getObject("conversation_box").switchState(DRAW_VISIBLE);
	choice = ch;
	choice.cursor_pos = 0;
	DrawableObject& obj = Canvas::getInstance().getObject("conversation_text");
	obj.switchState(DRAW_VISIBLE);
	obj.posX = CONVERSATION_TEXT_POS[2][0];
	obj.posY = CONVERSATION_TEXT_POS[2][1] + ybias;
	obj.text = txt;
	obj.expandBox = RECT({ 0,0,CONVERSATION_TEXT_BOX[4][0],CONVERSATION_TEXT_BOX[4][1]});

	int count = choice.items.size();
	for (int i = 0; i < count; i++) {
		std::string name = "conversation_choice"; name += char(i + 48);
		DrawableObject& obj2 = Canvas::getInstance().getObject(name);
		obj2.switchState(DRAW_VISIBLE);
		obj2.text = choice.items[i];
		obj2.posX = CONVERSATION_CHOICE_POS[count][i][0];
		obj2.posY = CONVERSATION_CHOICE_POS[count][i][1] + ybias;
		obj2.expandBox = RECT({ 0,0,CONVERSATION_CHOICE_BOX[count][0],CONVERSATION_CHOICE_BOX[count][1] });
	}
	AudioManager::getInstance().playSound("SND_CHOOSE");
	drawCursor();
}
void Conversation::changeText(Text txt) {
	Canvas::getInstance().getObject("conversation_text").text=txt;
}
void Conversation::changePic(Animation pic) {
	Canvas::getInstance().getObject("conversation_pic").anim = pic;

}
int Conversation::nowType() {
	return type;
}
Conversation::Conversation() {
	type = 0;
}
void Conversation::drawCursor() {
	DrawableObject& obj = Canvas::getInstance().getObject("conversation_cursor");
	obj.switchState(DRAW_VISIBLE);
	int count = choice.items.size(),pos=choice.cursor_pos;
	obj.posX = CONVERSATION_CURSOR_POS[count][pos][0];
	obj.posY = CONVERSATION_CURSOR_POS[count][pos][1] + ybias;
	
}
void Conversation::conversationSysInit() {
	Canvas::getInstance().addObject("conversation_box",
		DrawableObject(
			Animation(ResourceManager::getInstance().getResource("CONVERSATION_BOX"), 1, 1, 1, 886, 200),
			CONVERSATION_BOX_X, CONVERSATION_BOX_Y, { 0,0,CONVERSATION_BOX_WIDTH,CONVERSATION_BOX_HEIGHT}, CONVERSATION_BOX_PRIO,  DRAW_IGNOREBLANK| DRAW_ABSOLUTE));
	Canvas::getInstance().addObject("conversation_cursor",
		DrawableObject(
			Animation(ResourceManager::getInstance().getResource("STAR"), 1, 1, 1, 16, 16),
			0, 0, { 0,0,CONVERSATION_CURSOR_SIZE,CONVERSATION_CURSOR_SIZE }, CONVERSATION_ITEM_PRIO, DRAW_ABSOLUTE));
	Canvas::getInstance().addObject("conversation_text",
		DrawableObject(
			Text(L"", RGB(255, 255, 255), RGB(0, 0, 0), L"SimSun"), 0, 0, { 0,0,0,0 },CONVERSATION_ITEM_PRIO,DRAW_ABSOLUTE));
	Canvas::getInstance().addObject("conversation_choice0",
		DrawableObject(
			Text(L"", RGB(255, 255, 255), RGB(0, 0, 0), L"SimSun"), 0, 0, { 0,0,0,0 }, CONVERSATION_ITEM_PRIO, DRAW_ABSOLUTE));
	Canvas::getInstance().addObject("conversation_choice1",
		DrawableObject(
			Text(L"", RGB(255, 255, 255), RGB(0, 0, 0), L"SimSun"), 0, 0, { 0,0,0,0 }, CONVERSATION_ITEM_PRIO, DRAW_ABSOLUTE));
	Canvas::getInstance().addObject("conversation_choice2",
		DrawableObject(
			Text(L"", RGB(255, 255, 255), RGB(0, 0, 0), L"SimSun"), 0, 0, { 0,0,0,0 }, CONVERSATION_ITEM_PRIO, DRAW_ABSOLUTE));
	Canvas::getInstance().addObject("conversation_choice3",
		DrawableObject(
			Text(L"", RGB(255, 255, 255), RGB(0, 0, 0), L"SimSun"), 0, 0, { 0,0,0,0 }, CONVERSATION_ITEM_PRIO, DRAW_ABSOLUTE));
	Canvas::getInstance().addObject("conversation_pic",
		DrawableObject(
			Animation(),0, 0, { 0,0,0,0 }, CONVERSATION_ITEM_PRIO, DRAW_AUTOTICK| DRAW_ABSOLUTE));

	EventManager::getInstance().subscribe("UP_PRESS", "Conversation_Choice", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_PAUSED])return;
		if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] != 1
			&& !(GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] == GAME_STATE_BATTLE &&
				(Battle::getInstance().battleState() == BATTLE_DIALOG
					|| Battle::getInstance().battleState() == BATTLE_DESCRI)))return;
		if (type != CONV_CHOICE && type != CONV_CHTEXT)return;
		int count = choice.items.size();
		if (count==4) {
			if (choice.cursor_pos > 1)choice.cursor_pos -= 2, AudioManager::getInstance().playSound("SND_CHOOSE");
		}
		drawCursor();
		});
	EventManager::getInstance().subscribe("DOWN_PRESS", "Conversation_Choice", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_PAUSED])return;
		if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] != 1
			&& !(GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] == GAME_STATE_BATTLE &&
				(Battle::getInstance().battleState() == BATTLE_DIALOG
					|| Battle::getInstance().battleState() == BATTLE_DESCRI)))return;
		if (type != CONV_CHOICE && type != CONV_CHTEXT)return;
		int count = choice.items.size();
		if (count == 4) {
			if (choice.cursor_pos < 2)choice.cursor_pos += 2, AudioManager::getInstance().playSound("SND_CHOOSE");
		}
		drawCursor();
		});
	EventManager::getInstance().subscribe("LEFT_PRESS", "Conversation_Choice", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_PAUSED])return;
		if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] != 1
			&& !(GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] == GAME_STATE_BATTLE &&
				(Battle::getInstance().battleState() == BATTLE_DIALOG
					|| Battle::getInstance().battleState() == BATTLE_DESCRI)))return;
		if (type != CONV_CHOICE && type != CONV_CHTEXT)return;
		int count = choice.items.size();
		if (count == 2 || count == 3) {
			if (choice.cursor_pos > 0)choice.cursor_pos--, AudioManager::getInstance().playSound("SND_CHOOSE");
		}
		if (count == 4) {
			if (choice.cursor_pos & 1)choice.cursor_pos--, AudioManager::getInstance().playSound("SND_CHOOSE");
		}
		drawCursor();
		});
	EventManager::getInstance().subscribe("RIGHT_PRESS", "Conversation_Choice", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_PAUSED])return;
		if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] != 1
			&& !(GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] == GAME_STATE_BATTLE &&
				(Battle::getInstance().battleState() == BATTLE_DIALOG
					|| Battle::getInstance().battleState() == BATTLE_DESCRI)))return;
		if (type != CONV_CHOICE && type != CONV_CHTEXT)return;
		
		int count = choice.items.size();
		if (count == 2 || count == 3) {
			if (choice.cursor_pos <count-1)choice.cursor_pos++, AudioManager::getInstance().playSound("SND_CHOOSE");
		}
		if (count == 4) {
			if ((choice.cursor_pos & 1)==0)choice.cursor_pos++;
		}
		drawCursor();
		});
	EventManager::getInstance().subscribe("Z_PRESS", "Conversation_Choice", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_PAUSED]||GameManager::getInstance().globalVar[GLOBAL_MENUING])return;
		if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] != 1
			&& !(GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] == GAME_STATE_BATTLE &&
				(Battle::getInstance().battleState() == BATTLE_DIALOG
					|| Battle::getInstance().battleState() == BATTLE_DESCRI)))return;
		if (type == CONV_CHOICE || type == CONV_CHTEXT)	choice.proc(choice.cursor_pos);
		EventManager::getInstance().emit(CONVERSATION_PROCEED_EVENT);
		});
	
}


ConversationSequence& ConversationSequence::getInstance() {
	static ConversationSequence instance;
	return instance;
}
ConversationSequence::ConversationSequence() {
	procedure.clear();
	now_line = 0;
}
void ConversationSequence::setSequence(ConvSeq seq) {
	procedure = seq;
	now_line = 0;
}
void ConversationSequence::startConversation() {
	if (procedure.empty())return;
	now_line = 0;
	Conversation::getInstance().ybias = 0;
	Canvas::getInstance().getObject("conversation_box").posY = CONVERSATION_BOX_Y;
	EventManager::getInstance().subscribe(CONVERSATION_PROCEED_EVENT, "Conversation_Lines_Listen", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] != 1)return;
		now_line++;
		if (now_line >= procedure.size()) {
			ConversationSequence::getInstance().stopConversation();
			return;
		}
		procedure[now_line]();
		});
	EventManager::getInstance().emit(CONVERSATION_BEGIN_EVENT);
	GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] = 1;
	procedure[now_line]();
}
void ConversationSequence::stopConversation() {
	procedure.clear();
	now_line = 0;
	Conversation::getInstance().clearConversation();
	GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] = GAME_STATE_COMMON;
	GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] = 0;
	EventManager::getInstance().emit(CONVERSATION_END_EVENT);
	EventManager::getInstance().unsubscribe("CONVERSATION_PROCEED", "Conversation_Lines_Listen");
}
void ConversationSequence::startBattleConv() {
	if (procedure.empty())return;
	now_line = 0;
	Conversation::getInstance().ybias = -90;
	Canvas::getInstance().getObject("conversation_box").posY = BATTLE_DIALOG_BOX_Y;
	EventManager::getInstance().subscribe(CONVERSATION_PROCEED_EVENT, "Conversation_Lines_Listen", [&]() {
		if (GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] != 1
			&& !(GameManager::getInstance().globalVar[GLOBAL_GAME_STATE] == GAME_STATE_BATTLE && 
				(Battle::getInstance().battleState() == BATTLE_DIALOG
					||Battle::getInstance().battleState()==BATTLE_DESCRI)))return;
		now_line++;
		if (now_line >= procedure.size()) {
			ConversationSequence::getInstance().stopBattleConv();
			return;
		}
		procedure[now_line]();
		});

	GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] = 1;
	EventManager::getInstance().emit(CONVERSATION_BEGIN_EVENT);
	procedure[now_line]();
}
void ConversationSequence::stopBattleConv() {
	procedure.clear();
	now_line = 0;
	Conversation::getInstance().clearConversation();
	GameManager::getInstance().globalVar[GLOBAL_INCONVERSATION] = 0;
	EventManager::getInstance().emit(CONVERSATION_END_EVENT);
	EventManager::getInstance().unsubscribe("CONVERSATION_PROCEED", "Conversation_Lines_Listen");
}