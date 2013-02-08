#include "Sprite.h"

/***********************************************************************************
 TextureInfo :: methods
 *********************/
TextureInfo::TextureInfo(sf::Image _img, bool _animation) : img(_img), animation(_animation) {
	width = img.GetWidth();
	height = img.GetHeight();
}


/***********************************************************************************
 SpriteData :: methods
 *********************/
SpriteData::SpriteData(std::string _title, unsigned int _textureId, unsigned int _spriteId, sf::Vector2i _dimensions, sf::Vector2i _posInTexture, bool _animation, unsigned int _frame) :
		title(_title),
		textureId(_textureId),
		spriteId(_spriteId),
		dimensions(_dimensions),
		posInTexture(_posInTexture),
		animation(_animation),
		frame(_frame) {

}


/***********************************************************************************
 Sprite :: singleton
 *********************/
Sprite* Sprite::_instance = 0;

Sprite* Sprite::instance() {
	if(_instance == 0) {
		_instance = new Sprite;
		LOG("Spirite");
	}

  return _instance;
}


/***********************************************************************************
 Sprite :: methods
 *********************/
bool Sprite::insertTexture(std::string filename, bool animation) {
	unsigned int id = texture.size();
	unsigned int startTitle = filename.find_last_of('/') + 1;
	unsigned int stopTitle  = filename.find_last_of('.');
	std::string title = filename.substr(startTitle, stopTitle-startTitle);

	sf::Image img;
	if(!img.LoadFromFile(filename)) {
		LOG("Nie mozna zaladowac pliku: " + filename);
	  return false;
	}

	img.SetSmooth(false);

	if(textureId.find(title) != textureId.end()) {
		LOG("Textura \"" + title + "\" juz istnieje");
	  return false;
	}

	texture.push_back(TextureInfo(img, animation));
	textureId.insert(std::make_pair(title, id));
  return true;
}

bool Sprite::insertSprite(std::string title, std::string textureTitle, sf::Vector2i dimensions, sf::Vector2i posInTexture, bool animation, unsigned int frame) {
	unsigned int id = sprite.size();

	if(textureId.find(textureTitle) == textureId.end()) {
		LOG("Textura \"" + textureTitle + "\" nie istnieje");
	  return false;
	}

	if(spriteId.find(title) != spriteId.end()) {
		LOG("Sprite \"" + textureTitle + "\" juz istnieje");
	  return false;
	}

	SpriteData info(title, textureId.at(textureTitle), sprite.size(), dimensions, posInTexture, animation, frame);

	sprite.push_back(info);
	spriteId.insert(std::make_pair(title, id));
  return true;
}

bool Sprite::insertSprite(std::string title, std::string textureTitle, unsigned int width, unsigned int height, unsigned int x, unsigned int y, bool animation, unsigned int frame) {
  return insertSprite(title, textureTitle, sf::Vector2i(width, height), sf::Vector2i(x, y), animation, frame);
}

sf::Sprite Sprite::getSprite(const unsigned int &id) {
	if(id >= sprite.size()) {
		LOG("ID niepoprawne");
	  // TODO: Dodaæ wyj¹tki
	}

	unsigned int textureId = sprite.at(id).textureId;
	sf::Vector2i dimensions = sprite.at(id).dimensions;
	sf::Vector2i posInTexture = sprite.at(id).posInTexture;

	sf::Sprite newSprite;
	newSprite.SetImage(texture.at(textureId).img);
	if(!sprite.at(id).animation)
		newSprite.SetSubRect(sf::IntRect(posInTexture.x, posInTexture.y, posInTexture.x + dimensions.x, posInTexture.y + dimensions.y));

	newSprite.SetCenter(0, dimensions.y);

  return newSprite;
}

sf::Sprite Sprite::getSprite(std::string name) {
	if(spriteId.find(name) == spriteId.end()) {
		LOG("Name: " + name + " niepoprawna");
	 // TODO: Dodaæ wyj¹tki
	}

  return getSprite(spriteId.at(name));
}

SpriteData Sprite::getSpriteData(const unsigned int &id) {
	if(id >= sprite.size()) {
		LOG("ID niepoprawne");
	  return SpriteData();
	}

  return sprite.at(id);
}

SpriteData Sprite::getSpriteData(std::string name) {
	if(spriteId.find(name) == spriteId.end()) {
		LOG("Name: " + name + " niepoprawna");
	  return SpriteData();
	}

  return getSpriteData(spriteId.at(name));
}

void Sprite::showTextureList() {
	std::cout << "Texture list: " << std::endl;
	FOREACH(textureId, it)
		std::cout << "  Title: " << it->first << ", id: " << it->second << std::endl;
}

void Sprite::showSpriteList() {
	std::cout << "Sprite list: " << std::endl;
	FOREACH(spriteId, it)
	    std::cout << "  Title: " << it->first << ", id: " << it->second << std::endl;
}
