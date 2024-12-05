#include"AudioManager.h"


AudioManager& AudioManager::getInstance() {
    static AudioManager instance;
    return instance;
}
void AudioManager::playSound(const std::string name, bool isLoop)
{
    if (sounds.find(name) != sounds.end()) {
        sf::Sound *sound=new sf::Sound();
        sound->setBuffer(sounds[name]);
        sound->play();
        soundPlaying.insert(sound);
        return;
    }

    if (audios.find(name) == audios.end())return;

    sf::Music* music = new sf::Music();
    if (!music->openFromFile(audios[name])) {
        return; // Fail to load
    }
    music->setLoop(isLoop);
    music->play();
    musics[name] = music;
}
void AudioManager::loadAudio(const std::string& name, std::string filename,bool store) {
    if (store) {
        sounds[name].loadFromFile(filename);
    }
    else { 
        audios[name] = filename;
    }
}
void AudioManager::stopBgm() {
    for (auto& pl : musics) {
        pl.second->stop();
        delete pl.second;
    }
    musics.clear();
}
void AudioManager::stopBgm(std::string identifier) {
    if (musics.find(identifier) == musics.end())return;
    musics[identifier]->stop();
    delete musics[identifier];
    musics.erase(identifier);
}
bool AudioManager::isPlaying(const std::string name) {
    if (musics.find(name) == musics.end())return false;
    return musics[name]->getStatus() == sf::Music::Playing;
}
void AudioManager::checkStopped() {
    std::vector<std::string>* temp = new std::vector<std::string>;
    for (auto& pl : musics) {
        if (pl.second->getStatus() == sf::Music::Stopped) {
            temp->push_back(pl.first);
        }
    }
    for (auto& pl : *temp) {
        stopBgm(pl);
    }
    temp->clear();
    delete temp;

    std::vector<sf::Sound*> temp2;
    for (auto& sd : soundPlaying) {
        if (sd->getStatus() == sf::Music::Stopped) {
            temp2.push_back(sd);
        }
    }
    for (auto& sd : temp2) {
        delete sd;
        soundPlaying.erase(sd);
    }
}