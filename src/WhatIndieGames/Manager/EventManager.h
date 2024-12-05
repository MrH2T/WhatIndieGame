#pragma once
#include<string>
#include<functional>
#include<unordered_map>
#include<vector>
class EventManager {
public:
	static EventManager& getInstance();
	void subscribe(const std::string& event, const std::string&name, std::function<void()> handler);
	void unsubscribe(const std::string& event, const std::string& name);
	void emit(const std::string& event);
	void unsubscribeCheck();
private:
	std::unordered_map<std::string, std::unordered_map<std::string,std::function<void()>>> listeners;
	std::vector<std::pair<std::string,std::string> > waitingList;
};