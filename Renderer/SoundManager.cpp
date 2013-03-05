#include "SoundManager.h"

SoundManager::SoundManager() { }

/*
 * Sound API
 */

/* static */ bool SoundManager::registerSound(std::string path, std::string name) {
	SoundManager& self = instance();

	if(self.bufferIndex.find(name) != self.bufferIndex.end()){ //name in use
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
	uint id = self.buffers.size(); // new id
	self.bufferIndex.insert(std::make_pair(name,id));
	self.buffers.push_back(sound_buffer);
	return true;
}

// /* static */ bool SoundManager::registerSound(std::string path) {
//	std::string basename = path.substr(
//			path.find_last_of('/')+1); // strip off directory
//	basename = basename.substr(0,
//			basename.find_last_of('.')); // strip off extension
//
//	return registerSound(path,basename);
//}

/* static */ void SoundManager::playSound(std::string name, float volume) {
	SoundManager& self = instance();
	getQueue().push(sf::Sound());
	sf::Sound& sound = getQueue().back();
	sound.SetBuffer(self.getBuffer(name));
	sound.SetVolume(volume);
	sound.Play();
}

/* static */ void SoundManager::cleanQueue(){
	SoundManager& self = instance();
	while(self.soundQueue.front().GetStatus() == sf::Sound::Stopped ){
		self.soundQueue.pop();
	}
}

sf::SoundBuffer& SoundManager::getBuffer(std::string name) {
	// TODO: Exceptions
	if(bufferIndex.find(name) == bufferIndex.end()) {
		LOG(name + " nie zarejestrowane");
	}
	uint id = bufferIndex.at(name);

	if(id > buffers.size()) {
		LOG(id + " nie zarejestrowane");
	}

	return buffers.at(id);// Will still throw exception
}

/*
 * Music API
 */

//bool SoundManager::registerMusic(std::string path) {
//	std::string basename = path.substr(
//			path.find_last_of('/')+1); // strip off directory
//	basename = basename.substr(0,
//			basename.find_last_of('.')); // strip off extension
//
//	return registerMusic(path,basename);
//}

bool SoundManager::registerMusic(std::string path, std::string name) {
	SoundManager& self = instance();

	if(self.trackIndex.find(name) != self.trackIndex.end()){ //name in use
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
	uint id=self.tracks.size(); // new id
	self.trackIndex.insert(std::make_pair(name,id));
	self.tracks.push_back(m);
	return true;
}

sf::Music* SoundManager::getMusic(std::string name){
	SoundManager& self = instance();
	// TODO: Exceptions
	if (self.trackIndex.find(name) == self.trackIndex.end()) {
		LOG(name + " nie zarejestrowane");
	}

	uint id = self.trackIndex.at(name);

	if (id > self.tracks.size()) {
		LOG(id + " nie zarejestrowane");
	}

	return self.tracks.at(id);
}

