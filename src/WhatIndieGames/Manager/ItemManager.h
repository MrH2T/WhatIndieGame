#pragma once
#include<string>
#include<functional>
#include<unordered_map>


struct Item {
	std::string itemName;
	std::string itemDescription;
	std::function<void()> itemFunc;
	Item() { itemName = "", itemDescription = "", itemFunc = NULL; }
	Item(std::string name, std::string desc, std::function<void()> func) {
		itemName = name;
		itemDescription = desc;
		itemFunc = func;
	}
};
class ItemManager {
public:
	static ItemManager& getInstance();
	void registerItem(std::string name, Item item);
	Item getItem(std::string name);
private:
	ItemManager() { registeredItems.clear(); };
	std::unordered_map<std::string, Item> registeredItems;
};