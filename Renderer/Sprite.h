#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "../StdAfx.h"

class TextureInfo {
public:
	TextureInfo(sf::Image _img, bool _animation = false);

	unsigned int width;
	unsigned int height;

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

	SpriteData() { }
	SpriteData(std::string _title, unsigned int _textureId, unsigned int _spriteId, sf::Vector2i dimensions, sf::Vector2i _posInTexture, bool _animation = false, unsigned int _frame = 0);
};

class Sprite { /* Half singleton */
public:

private:
	static Sprite *_instance;

	std::vector<TextureInfo> texture;
	std::map<std::string, unsigned int> textureId;

	std::vector<SpriteData> sprite;
	std::map<std::string, unsigned int> spriteId;

public:
	static Sprite* instance();

	Sprite() { }
	~Sprite() { }

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

	int getSpriteSize() { return sprite.size(); }

private:

};

#endif /*__SPRITE_H__*/
