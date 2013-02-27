#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__

#include "../StdAfx.h"

class TextureInfo {
public:
	TextureInfo(sf::Image _img, bool _animation = false);

	int width;
	int height;

	bool animation;

	sf::Image img;
};

struct SpriteData {
	std::string title;
	unsigned int textureId;
	unsigned int spriteId;

	sf::Vector2i dimensions;
	sf::Vector2i posInTexture;

	bool animation;
	unsigned int frame;

	SpriteData() = default;
	SpriteData(std::string _title, unsigned int _textureId, unsigned int _spriteId, sf::Vector2i dimensions, sf::Vector2i _posInTexture, bool _animation = false, unsigned int _frame = 0);
};

class SpriteManager { /** Half singleton **/
private:
	static SpriteManager *_instance;

	std::vector<TextureInfo> textures;
	std::map<std::string, unsigned int> texturesId;

	std::vector<SpriteData> sprites;
	std::map<std::string, unsigned int> spritesId;

public:
	static SpriteManager* instance();

	SpriteManager() { }
	~SpriteManager();

	bool insertTexture(std::string filename, bool animation = false);
	bool insertSprite(std::string title, std::string textureTitle, sf::Vector2i dimensions, sf::Vector2i posInTexture, bool animation = false, unsigned int frame = 0);
	bool insertSprite(std::string title, std::string textureTitle, unsigned int width, unsigned int height, unsigned int x, unsigned int y, bool animation = false, unsigned int frame = 0);

	// void eraseTexture(std::string name);
	// void eraseTexture(unsigned int id);

	// void eraseSprite(std::string name);
	// void eraseSprite(unsigned int id);

	sf::Sprite getSprite(const unsigned int &id);
	sf::Sprite getSprite(std::string name);

	SpriteData getSpriteData(const unsigned int &id);
	SpriteData getSpriteData(std::string name);

	void showTextureList();
	void showSpriteList();

	int getSpriteSize() { return sprites.size(); }
};

#endif /*__SPRITEMANAGER_H__*/
