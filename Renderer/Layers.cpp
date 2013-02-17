#include "Layers.h"

static const uint LAYER_COUNT = 10;

static std::string strToLayer[LAYER_COUNT] = {
		"BACKGROUND",
		"SHADOWS",
		"EQUIPMENTS",
		"BLOCKS",
		"DOORS",
		"STONES",
		"BOMBS",
		"EXPLOSIONS",
		"CHARACTERS",
		"GUI"
};

LayerType StrToLayer(std::string name) {
	for(int i = 0; i < LAYER_COUNT; ++i)
		if(name == strToLayer[i])
		   return (LayerType)i;

    LOG("Nie ma takiej warstyw: " + name);

  return (LayerType)LAYER_COUNT;
}

std::string LayerToStr(LayerType layer) {
    if((int)layer < LAYER_COUNT)
      return strToLayer[(int)layer];

  return "NONE";
}
