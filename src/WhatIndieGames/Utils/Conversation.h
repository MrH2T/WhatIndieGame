#pragma once

#include"Animation.h"
#include"Text.h"
#include"Canvas.h"
#include<string>

#define CONVERSATION_BEGIN_EVENT "CONVERSATION_BEGIN"
#define CONVERSATION_END_EVENT "CONVERSATION_END"
#define CONVERSATION_PROCEED_EVENT "CONVERSATION_PROCEED"

typedef std::vector<std::function<void()>> ConvSeq;

const int CONVERSATION_BOX_X = 5;
const int CONVERSATION_BOX_Y = 425;
const int CONVERSATION_BOX_WIDTH = 886;
const int CONVERSATION_BOX_HEIGHT = 200;
const int CONVERSATION_CURSOR_SIZE = 24;
const int CONVERSATION_CURSOR_POS[5][4][2] = {
	{{0,0},{0,0},{0,0},{0,0}},
	{{0,0},{0,0},{0,0},{0,0}},
	{{CONVERSATION_BOX_X+5+5,CONVERSATION_BOX_Y+5+5 + 40+5},{CONVERSATION_BOX_X+CONVERSATION_BOX_WIDTH/2+5+5,CONVERSATION_BOX_Y + 5 + 5+40+5},{0,0},{0,0}},
	{{CONVERSATION_BOX_X+5+5,CONVERSATION_BOX_Y+5+5 + 40+5},{CONVERSATION_BOX_X+CONVERSATION_BOX_WIDTH/3+5+5,CONVERSATION_BOX_Y+5+5 + 40+5},
		{CONVERSATION_BOX_X+CONVERSATION_BOX_WIDTH*2/3+5+5,CONVERSATION_BOX_Y+5+5 + 40+5},{0,0}},
	{{CONVERSATION_BOX_X + 5 + 5,CONVERSATION_BOX_Y + 5 + 5 + 40+5},{CONVERSATION_BOX_X + CONVERSATION_BOX_WIDTH / 2 + 5 + 5,CONVERSATION_BOX_Y + 5 + 5 + 40+5},
		{CONVERSATION_BOX_X + 5 + 5,CONVERSATION_BOX_Y + 5 + 5 + CONVERSATION_BOX_HEIGHT/2+20+5},
		{CONVERSATION_BOX_X + CONVERSATION_BOX_WIDTH / 2 + 5 + 5,CONVERSATION_BOX_Y + 5 + 5 + CONVERSATION_BOX_HEIGHT/2 + 20+5}}
};

const int CONVERSATION_TEXT_POS[5][2] = {
	{0,0},{CONVERSATION_BOX_X+5+10,CONVERSATION_BOX_Y+5+10},{CONVERSATION_BOX_X+5+10+160,CONVERSATION_BOX_Y+5+10},{0,0},{CONVERSATION_BOX_X+CONVERSATION_BOX_WIDTH/2-150,CONVERSATION_BOX_Y+5+5}
};
const int CONVERSATION_TEXT_BOX[5][2] = {
	{0,0},{CONVERSATION_BOX_WIDTH-30,CONVERSATION_BOX_HEIGHT-30},{CONVERSATION_BOX_WIDTH-200,CONVERSATION_BOX_HEIGHT-30},{0,0},{CONVERSATION_BOX_WIDTH/2,40}
};
const int CONVERSATION_PIC_POS[2] = {CONVERSATION_BOX_X+5+20,CONVERSATION_BOX_Y+5+20};
const int CONVERSATION_PIC_BOX[2] = {120,120};
const int CONVERSATION_CHOICE_POS[5][4][2] =
{
	{{0,0},{0,0},{0,0},{0,0}},
	{{0,0},{0,0},{0,0},{0,0}},
	{{CONVERSATION_BOX_X + 5 + 5 + 24 + 3,CONVERSATION_BOX_Y + 5 + 5 + 40},{CONVERSATION_BOX_X + CONVERSATION_BOX_WIDTH / 2 + 5 + 5 + 24 + 3,CONVERSATION_BOX_Y + 5 + 5 + 40},{0,0},{0,0}},
	{{CONVERSATION_BOX_X + 5 + 5 + 24 + 3,CONVERSATION_BOX_Y + 5 + 5 + 40},{CONVERSATION_BOX_X + CONVERSATION_BOX_WIDTH / 3 + 5 + 5 + 24 + 3,CONVERSATION_BOX_Y + 5 + 5 + 40},
		{CONVERSATION_BOX_X + CONVERSATION_BOX_WIDTH * 2 / 3 + 5 + 5 + 24 + 3,CONVERSATION_BOX_Y + 5 + 5 + 40},{0,0}},
	{{CONVERSATION_BOX_X + 5 + 5 + 24 + 3,CONVERSATION_BOX_Y + 5 + 5 + 40},
		{CONVERSATION_BOX_X + CONVERSATION_BOX_WIDTH / 2 + 5 + 5 + 24 + 3,CONVERSATION_BOX_Y + 5 + 5 + 40},
		{CONVERSATION_BOX_X + 5 + 5 + 24 + 3,CONVERSATION_BOX_Y + CONVERSATION_BOX_HEIGHT / 2 + 5 + 5 + 20},
		{CONVERSATION_BOX_X + CONVERSATION_BOX_WIDTH / 2 + 5 + 5 + 24 + 3,CONVERSATION_BOX_Y + CONVERSATION_BOX_HEIGHT / 2 + 5 + 5 + 20}}
};
const int CONVERSATION_CHOICE_BOX[5][2] = {
	{0,0},{0,0},{CONVERSATION_BOX_WIDTH / 2 - 5 - 5 - 24 - 10,CONVERSATION_BOX_Y - 5 - 5 - 5 - 5 - 5 - 20},
	{CONVERSATION_BOX_WIDTH / 3 - 5 - 5 - 24 - 5,CONVERSATION_BOX_Y - 5 - 5 - 5 - 5 - 5 - 20},
	{CONVERSATION_BOX_WIDTH / 2 - 5 - 5 - 24 - 10, CONVERSATION_BOX_Y / 2 - 5 - 5 - 5 - 5 - 20}
};

const int CONVERSATION_BOX_PRIO = Canvas::MAX_LAYER-1, CONVERSATION_ITEM_PRIO = Canvas::MAX_LAYER;

typedef std::vector<Text> ChoiceItem;
class Conversation {
public:
	static const int CONV_NONE=0, CONV_PLAIN = 1, CONV_PIC = 2, CONV_CHOICE = 3, CONV_CHTEXT = 4;
	struct Choice {
		std::vector<Text> items;
		int cursor_pos;
		std::function<void(int)> proc;
		Choice();
		Choice(std::vector<Text> choice, std::function<void(int)> proc_func);
	};
	static Conversation& getInstance();
	void clearConversation();
	void beginConversation(Text txt);
	void beginConversation(Text txt, Animation pic);
	void beginConversation(Choice ch);
	void beginConversation(Text txt, Choice ch);
	void changeText(Text txt);
	void changePic(Animation pic);
	void drawCursor();
	int nowType();
	void conversationSysInit();
	int ybias;
private:
	Conversation();
	int type;
	// 0:NO CONV; 1: PLAIN TEXT; 2: TEXT WITH PIC; 3: CHOICE; 4: CHOICE WITH TEXT
	Choice choice;
};


class ConversationSequence {
public:
	static ConversationSequence& getInstance();
	void setSequence(ConvSeq seq);
	void stopConversation();
	void startConversation();
	void startBattleConv();
	void stopBattleConv();
private:
	ConversationSequence();
	std::vector < std::function<void()>> procedure;
	int now_line;
};