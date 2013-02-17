#ifndef __LAYERS_H__
#define __LAYERS_H__

#include "../StdAfx.h"

/**
 * Przy edycji enuma nale¿y zedytowac plik Layers.cpp
 */
enum class LayerType {
    LAYER_BACKGROUND,
    LAYER_SHADOWS,
    LAYER_EQUIPMENTS,
    LAYER_BLOCKS,
    LAYER_DOORS,
    LAYER_STONES,
    LAYER_BOMBS,
    LAYER_EXPLOSIONS,
    LAYER_CHARACTERS,
    LAYER_GUI
};

LayerType StrToLayer(std::string name);
std::string LayerToStr(LayerType layer);

#endif /*__LAYERS_H__*/

