#include "SpriteManager.h"

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
SpriteManager* SpriteManager::_instance = 0;

SpriteManager* SpriteManager::instance() {
	if(_instance == 0) {
		_instance = new SpriteManager;
		LOG("Spirite");
	}

  return _instance;
}


/***********************************************************************************
 Sprite :: methods
 *********************/
SpriteManager::~SpriteManager() {
	textures.clear();
	texturesId.clear();

	sprites.clear();
	spritesId.clear();
}

bool SpriteManager::insertTexture(std::string filename, bool animation) {
	unsigned int id = textures.size();
	unsigned int startTitle = filename.find_last_of('/') + 1;
	unsigned int stopTitle  = filename.find_last_of('.');
	std::string title = filename.substr(startTitle, stopTitle-startTitle);

	sf::Image img;
	if(!img.LoadFromFile(filename)) {
		LOG("Nie mozna zaladowac pliku: " + filename);
	  return false;
	}

	img.SetSmooth(false);

	if(texturesId.find(title) != texturesId.end()) {
		LOG("Textura \"" + title + "\" juz istnieje");
	  return false;
	}

	textures.push_back(TextureInfo(img, animation));
	texturesId.insert(std::make_pair(title, id));
  return true;
}

bool SpriteManager::insertSprite(std::string title, std::string textureTitle, sf::Vector2i dimensions, sf::Vector2i posInTexture, bool animation, unsigned int frame) {
	unsigned int id = sprites.size();

	if(texturesId.find(textureTitle) == texturesId.end()) {
		LOG("Textura \"" + textureTitle + "\" nie istnieje");
	  return false;
	}

	if(spritesId.find(title) != spritesId.end()) {
		LOG("Sprite \"" + textureTitle + "\" juz istnieje");
	  return false;
	}

	SpriteData info(title, texturesId.at(textureTitle), sprites.size(), dimensions, posInTexture, animation, frame);

	sprites.push_back(info);
	spritesId.insert(std::make_pair(title, id));
  return true;
}

bool SpriteManager::insertSprite(std::string title, std::string textureTitle, unsigned int width, unsigned int height, unsigned int x, unsigned int y, bool animation, unsigned int frame) {
  return insertSprite(title, textureTitle, sf::Vector2i(width, height), sf::Vector2i(x, y), animation, frame);
}

sf::Sprite SpriteManager::getSprite(const unsigned int &id) {
	if(id >= sprites.size()) {
		LOG("ID niepoprawne");
	  // TODO: Dodaæ wyj¹tki
	}

	unsigned int textureId = sprites.at(id).textureId;
	sf::Vector2i dimensions = sprites.at(id).dimensions;
	sf::Vector2i posInTexture = sprites.at(id).posInTexture;

	sf::Sprite newSprite;
	newSprite.SetImage(textures.at(textureId).img);
	if(!sprites.at(id).animation)
		newSprite.SetSubRect(sf::IntRect(posInTexture.x, posInTexture.y, posInTexture.x + dimensions.x, posInTexture.y + dimensions.y));

	newSprite.SetCenter(0, dimensions.y);

  return newSprite;
}

sf::Sprite SpriteManager::getSprite(std::string name) {
	if(spritesId.find(name) == spritesId.end()) {
		LOG("Name: " + name + " niepoprawna");
	 // TODO: Dodaæ wyj¹tki
	}

  return getSprite(spritesId.at(name));
}

SpriteData SpriteManager::getSpriteData(const unsigned int &id) {
	if(id >= sprites.size()) {
		LOG("ID niepoprawne");
		// TODO: Dodaæ wyj¹tki
	}

  return sprites.at(id);
}

SpriteData SpriteManager::getSpriteData(std::string name) {
	if(spritesId.find(name) == spritesId.end()) {
		LOG("Name: " + name + " niepoprawna");
		// TODO: Dodaæ wyj¹tki
	}

  return getSpriteData(spritesId.at(name));
}

void SpriteManager::showTextureList() {
	std::cout << "Texture list: " << std::endl;
	FOREACH(texturesId, it)
		std::cout << "  Title: " << it->first << ", id: " << it->second << std::endl;
}

void SpriteManager::showSpriteList() {
	std::cout << "Sprite list: " << std::endl;
	FOREACH(spritesId, it)
	    std::cout << "  Title: " << it->first << ", id: " << it->second << std::endl;
}
