#pragma once

#include<unordered_map>
#include<string>
#include"../framework.h"


class AudioManager {
public:
	static AudioManager& getInstance();
	void loadAudio(const std::string& name, std::string filename,bool store=0);
    void playSound(const std::string name, bool isLoop = 0);
	void stopBgm();
    void stopBgm(const std::string identifier);
	void checkStopped();
	bool isPlaying(const std::string name);
private:
	AudioManager() { }
	std::unordered_map<std::string, std::string > audios;
    std::unordered_map<std::string, sf::Music*> musics;
	std::unordered_map<std::string, sf::SoundBuffer> sounds;
	std::set<sf::Sound*> soundPlaying;
	AudioManager(const AudioManager&) = delete;
	void operator=(const AudioManager&) = delete;
};


