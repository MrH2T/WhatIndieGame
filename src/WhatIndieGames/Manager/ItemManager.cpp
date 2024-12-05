#include"ItemManager.h"

ItemManager& ItemManager::getInstance() {
	static ItemManager instance;
	return instance;
}
void ItemManager::registerItem(std::string name, Item item) {
	registeredItems[name] = item;
}
Item ItemManager::getItem(std::string name) {
	return registeredItems[name];
}