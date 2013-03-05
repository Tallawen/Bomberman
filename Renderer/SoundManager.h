#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "../StdAfx.h"

/** Singleton. Handles loading sounds from files
 *  stores sound buffers for use in sf::Sound instances
 *  stores music for playback
 * */
class SoundManager {
private:
	SoundManager();

	// Prevents accidental creating of more instances:
	SoundManager(SoundManager const&) = delete;
	void operator=(SoundManager const&) = delete;

public:
	/// Return reference to instance
	static SoundManager& instance() {
		static SoundManager inst; //Initialized on first call
		return inst;
	}

/*
 * Sound API
 *     register sounds from files, play them, clean up regularly
 *
 *     registered sound files are stored as buffers, mapped to their names
 *     playable objects are created by the playSound() method and pushed into a sound queue
 *     sounds that have finished playing are removed in the cleanQueue() method
 */

private:
	/// Sound buffers hold sound file in memory
	std::vector<sf::SoundBuffer> buffers;

	/// mapping names to indexes of buffers vector
	std::map<std::string, uint> bufferIndex;

	/// used for sound playback
	std::queue<sf::Sound> soundQueue;

public:
	/// Return sound queue used for playback
	static std::queue<sf::Sound>& getQueue() {
		return instance().soundQueue;
	}

	/// Loads a sound from file, registers as name.
	static bool registerSound(std::string path, std::string name);

//	/// Loads a sound from file, registers as file's basename.
//	static bool registerSound(std::string path);

	/// Play sound associated with name
	static void playSound(std::string name, float volume=100.0f);

	/// Cleans the soundQueue from Stopped (useless) elements
	static void cleanQueue();

private:
	/// Return sound associated with name
	sf::SoundBuffer& getBuffer(std::string name);

	/// Return sound associated with index
	sf::SoundBuffer& getBuffer(uint id);

/*
 * Music API
 *	   music objects are stored as already playable objects, which can be accesses via getMusic()
 */
private:
	/// Music
	std::vector<sf::Music*> tracks; /* Uses pointers,
	as - sadly sf::Music and std::vector don't like each other.
	sf::Music has a private copy constructor. memleaks aren't an issue,
	resources are loaded on startup anyway */

	std::map<std::string, uint> trackIndex;

public:

	/// Loads a track from file, registers as name.
	static bool registerMusic(std::string path, std::string name);

	/// Return pointer associated with name
	static sf::Music* getMusic(std::string name);

};

#endif /* SOUNDMANAGER_H_ */
