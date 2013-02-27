#include "SoundManager.h"

SoundManager::SoundManager() {
	// TODO Auto-generated constructor stub
}

//SoundManager::~SoundManager() {
//	// TODO Auto-generated destructor stub
//}

bool SoundManager::registerSound(std::string path) {
	std::string basename = path.substr(
			path.find_last_of('/')+1); // strip off directory
	basename = basename.substr(0,
			basename.find_last_of('.')); // strip off extension

	return registerSound(path,basename);
}

bool SoundManager::registerSound(std::string path, std::string name) {
	if(bufferIndex.find(name) != bufferIndex.end()){ //name in use
		//TODO: Exceptions
		LOG("Nazwa " + name + " jest juz w uzyciu");
		return false;
	}

	sf::SoundBuffer sound_buffer;

	if(!sound_buffer.LoadFromFile(path)){ //failed to load
		//TODO: Exceptions
		LOG("Nie mozna zaladowac pliku "+path);
		return false;
	}

	//Register:
	uint id = buffers.size(); // new id
	bufferIndex.insert(std::make_pair(name,id));
	buffers.push_back(sound_buffer);
	return true;

}

sf::SoundBuffer& SoundManager::getSoundBuffer(std::string name) {
	// TODO: Exceptions
	if(bufferIndex.find(name) == bufferIndex.end()) {
		LOG(name + " nie zarejestrowane");
	}
	return getSoundBuffer(bufferIndex.at(name)); // Will still throw exception
}

sf::SoundBuffer& SoundManager::getSoundBuffer(uint id) {
	// TODO: Exceptions
	if(id > buffers.size()) {
		LOG(id + " nie zarejestrowane");
	}
	return buffers.at(id); // Will still throw exception
}

// Music

bool SoundManager::registerMusic(std::string path) {
	std::string basename = path.substr(
			path.find_last_of('/')+1); // strip off directory
	basename = basename.substr(0,
			basename.find_last_of('.')); // strip off extension

	return registerMusic(path,basename);
}

bool SoundManager::registerMusic(std::string path, std::string name) {
	if(trackIndex.find(name) != trackIndex.end()){ //name in use
		//TODO: Exceptions
		LOG("Nazwa " + name + " jest juz w uzyciu");
		return false;
	}

	sf::Music* m = new sf::Music;

	if(!m->OpenFromFile(path)){ //failed to load
		//TODO: Exceptions
		LOG("Nie mozna zaladowac pliku "+path);
		return false;
	}

	//Register:
	uint id=tracks.size(); // new id
	trackIndex.insert(std::make_pair(name,id));
	tracks.push_back(m);
	return true;
}

sf::Music* SoundManager::getMusic(std::string name){
	// TODO: Exceptions
	if(trackIndex.find(name) == trackIndex.end()) {
		LOG(name + " nie zarejestrowane");
	}
	return getMusic(trackIndex.at(name)); // Will still throw exception
}

sf::Music* SoundManager::getMusic(uint id){
	// TODO: Exceptions
	if(id > tracks.size()) {
		LOG(id + " nie zarejestrowane");
	}

	return tracks.at(id); // Will still throw exception
}
