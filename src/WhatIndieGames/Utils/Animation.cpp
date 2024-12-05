#include"Animation.h"
#include"../Manager/ResourceManager.h"

Animation::Animation():curFrame(0),frame_width(0),frame_height(0) {}

Animation::Animation(int width, int height) {
	frame_width = width;
	frame_height = height;
	curFrame = 0;
	sequence.clear();
}
Animation::Animation(const HBITMAP& resource, int tot, int rows, int cols, int width, int height) {
	sequence.clear();
	loadAnimFromResource(resource, tot, rows, cols, width, height);
	for (int index = 0; index < tot; index++)sequence.push_back(index);

}
Animation::Animation(const HBITMAP& resource, int tot, int rows, int cols, int width, int height, std::vector<int> seq) {
	sequence.clear();
	loadAnimFromResource(resource, tot, rows, cols, width, height);
	sequence = seq;
}
Animation::Animation(const HBITMAP& resource, int tot, int rows, int cols, int width, int height,int stretch) {
	sequence.clear();
	loadAnimFromResource(resource, tot, rows, cols, width, height);
	for (int index = 0; index < tot; index++)for (int _ = 0; _ < stretch;_++)sequence.push_back(index);
}
void Animation::setCurFrame(int frame) {
	curFrame = frame;
}
void Animation::loadAnimFromResource(const HBITMAP& resource, int tot, int rows, int cols, int width, int height) {

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			frames.push_back(subBitmap(resource, RECT{ width * c,height*r, width*c+width, height*r+height}));
		}
	}
	frame_width = width;
	frame_height = height;
	curFrame = 0;
}
//manually append a frame
void Animation::appendFrame(const HBITMAP& resource) {
	frames.push_back(resource);

}
int Animation::getWidth() {
	return frame_width;
}
int Animation::getHeight() {
	return frame_height;
}
int Animation::getCurFrame() {
	return curFrame;
}
void Animation::tickFrame() {
	//if (sequence.size() == 0)return;
	
	curFrame = (curFrame + 1) % sequence.size();
}
//return frame
Frame Animation::getFrame(int frame) {
	return frames[sequence[frame]];
}
Frame Animation::getFrame() {
	return frames[sequence[curFrame]];
}