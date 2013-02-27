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
	std::map<std::string, uint> bufferIndex;

	std::queue<sf::Sound> soundQueue;

	///Music
	std::vector<sf::Music*> tracks; /* Use pointers,
	as - sadly sf::Music and std::vector don't like each other.
	sf::Music has a private copy constructor. memleaks aren't an issue,
	resources are loaded on startup anyway */

	std::map<std::string, uint> trackIndex;

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

	/* Music handling is a little different, as music objects are non-copy-able
	 * Usage:
	 * 1. Register:
	 * SoundManager::instance().registerMusic("file.ogg", "example");
	 *
	 * 2. Later, get the pointer:
	 * sf::Music* example_theme = SoundManager::instance().getMusic("example");
	 *
	 * 3. Use freely:
	 * example_theme->Play();
	 * example_theme->Pause();
	 * example_theme->Stop();
	 **/

	/// Loads a track from file, registers as file's basename.
	bool registerMusic(std::string path);

	/// Loads a track from file, registers as name.
	bool registerMusic(std::string path, std::string name);

	/// Return pointer associated with name
	sf::Music* getMusic(std::string name);

	/// Return pointer associated with index
	sf::Music* getMusic(uint id);

private:
	SoundManager();

	// Prevents accidental creating of more instances:
	SoundManager(SoundManager const&) = delete;
	void operator=(SoundManager const&) = delete;

};

#endif /* SOUNDMANAGER_H_ */
