#include"EventManager.h"


EventManager & EventManager::getInstance() {
	static EventManager instance;
	return instance;
}
//subscribe specific function to some events
void EventManager::subscribe(const std::string& event, const std::string& name, std::function<void()> handler) {
	listeners[event][name]=(handler);
	std::vector<std::pair<std::string, std::string> >::iterator it;
	bool flag = 0;
	for (int i = 0; i < waitingList.size(); i++) {
		if (waitingList[i].second == name){
			it = waitingList.begin() + i;
			flag = 1;
			break;
		}
	}
	if(flag)waitingList.erase(it);
}
//emit the event
void EventManager::emit(const std::string& event) {
	if (listeners[event].empty())return;
	for (auto& val : listeners[event]) {
		val.second();
	}
}
void EventManager::unsubscribe(const std::string& event, const std::string& name) {
	waitingList.push_back(std::make_pair(event, name));
}
void EventManager::unsubscribeCheck() {
	if (waitingList.empty())return;
	for (auto i : waitingList) {
		auto it = listeners[i.first].find(i.second);
		if (it != listeners[i.first].end())
			listeners[i.first].erase(it);
	}
	waitingList.clear();
}