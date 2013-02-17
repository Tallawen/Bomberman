#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "../StdAfx.h"

/** Singleton. Handles loading sounds from files
 *  stores sound buffers for use in sf::Sound instances
 * */
class SoundManager {
public:

private:
	/// Sound buffers hold sound file in memory
	std::vector<sf::SoundBuffer> buffers;

	/// mapping names to indexes of buffers vector
	std::map<std::string, uint> nameIndex;

	std::queue<sf::Sound> soundQueue;

/*
 * Methods:
 */
public:
	/// Return reference to instance
	static SoundManager& instance() {
		static SoundManager inst; //Initialized on first call
		return inst;
	}

	static std::queue<sf::Sound>& getQueue() {
		return instance().soundQueue;
	}

	/// Loads a sound from file, registers as file's basename.
	bool registerSound(std::string path);

	/// Loads a sound from file, registers as name.
	bool registerSound(std::string path, std::string name);

	/// Return sound associated with name
	sf::SoundBuffer& getSoundBuffer(std::string name);

	/// Return sound associated with index
	sf::SoundBuffer& getSoundBuffer(uint id);

private:
	SoundManager();

	// Prevents accidental creating of more instances:
	SoundManager(SoundManager const&) = delete;
	void operator=(SoundManager const&) = delete;

};

#endif /* SOUNDMANAGER_H_ */
