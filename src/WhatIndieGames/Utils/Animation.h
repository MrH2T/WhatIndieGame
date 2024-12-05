#pragma once


#include<windows.h>
#include<vector>
#include<utility>

typedef HBITMAP Frame;

class Animation {
public:
	Animation();
	Animation(int width, int height);
	Animation(const HBITMAP& resource, int tot, int rows, int cols, int width, int height);
	Animation(const HBITMAP& resource, int tot, int rows, int cols, int width, int height, std::vector<int> seq);
	Animation(const HBITMAP& resource, int tot, int rows, int cols, int width, int height,int stretch);
	void loadAnimFromResource(const HBITMAP& resource, int tot, int rows,int cols, int width, int height);
	void appendFrame(const HBITMAP& resource);	//manually append a frame
	int getWidth();
	int getHeight();
	void setCurFrame(int frame);
	int getCurFrame();
	void tickFrame();
	Frame getFrame();
	Frame getFrame(int frame);
private:
	int curFrame,frame_width, frame_height;
	std::vector<Frame> frames;
	std::vector<int> sequence;
};