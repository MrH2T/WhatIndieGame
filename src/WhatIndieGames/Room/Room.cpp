#include"Room.h"
#include"../Manager/GameManager.h"
#include"../Manager/ResourceManager.h"

Room::Room(int id, HBITMAP pic, int width_, int height_) {
	room_id = id;
	entities.clear();
	localVar.clear();
	loadMap(pic, width_, height_);
}
Room::Room(int id, HBITMAP tiles, int setrows, int setcols, std::vector<std::vector<int>> tile_info) {
	room_id = id;
	entities.clear();
	localVar.clear();
	calculateMap(tiles, setrows,setcols,tile_info);
}
void Room::addEntity(std::string entname, Entity* ent) {
	entities[entname] = ent;
	GameManager::getInstance().addEntity(entname, ent);

}
void Room::deleteEntity(std::string entname) {
	delete entities[entname];
	entities.erase(entname);
	GameManager::getInstance().deleteEntity(entname);
}
Entity* Room::getEntity(std::string entname) {
	return entities[entname];
}
void Room::loadMap(HBITMAP pic, int width_, int height_) {
	map = pic;
	width = width_;
	height = height_;
}
void Room::calculateMap(HBITMAP tiles, int setrows,int setcols,std::vector<std::vector<int>> tile_info,int size) {
	HDC hdcDest = CreateCompatibleDC(NULL);
	HDC hdcSrc = CreateCompatibleDC(NULL);
	int rows = tile_info.size(),cols= tile_info[0].size();
	for (int i = 0; i < rows; i++)cols = std::max(cols, (int)tile_info[i].size());
	width = cols*TILE_GAME_SIZE;
	height = rows * TILE_GAME_SIZE;
	SelectObject(hdcSrc,tiles);
	map= CreateCompatibleBitmap(hdcSrc, width, height);

	//std::vector<HBITMAP> tileSet = decomposeBitmap(tiles, rows, cols, TILE_FILE_SIZE, TILE_FILE_SIZE);
	SelectObject(hdcDest, map);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			//SelectObject(hdcSrc, tileSet[tile_info[i][j]]);
			if (j >= tile_info[i].size())continue;
			if (tile_info[i][j] == -1)continue;
			int srcR =tile_info[i][j]/setcols, srcC = tile_info[i][j] % setcols;
			StretchBlt(hdcDest,j*TILE_GAME_SIZE, i * TILE_GAME_SIZE, TILE_GAME_SIZE,TILE_GAME_SIZE,
					hdcSrc, srcC * size, srcR* size, size, size, SRCCOPY);
			/*StretchBlt(hdcDest, i * TILE_GAME_SIZE, j * TILE_GAME_SIZE, TILE_GAME_SIZE, TILE_GAME_SIZE,
				hdcSrc, 0, 0, TILE_FILE_SIZE, TILE_FILE_SIZE, SRCCOPY);*/
		}
	}
	DeleteDC(hdcDest);
	DeleteDC(hdcSrc);
}
//void Room::roomInit() {
//	initFunc();
//}
int Room::getWidth() {
	return width;
}
int Room::getHeight() {
	return height;
}
void Room::clearEntities() {
	for (auto& ent : entities) {

		delete ent.second;
		GameManager::getInstance().entities.erase(ent.first);
	}
	entities.clear();
}
const int Room::roomId() {
	return room_id;
}