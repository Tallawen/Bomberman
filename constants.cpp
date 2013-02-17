#include "constants.h"

namespace Constants {

    namespace Video {

        ConstInt SCREEN_WIDTH("video.screen_width", 800);
        ConstInt SCREEN_HEIGHT("video.screen_height", 600);
        ConstStr SCREEN_TITLE("Bomberman");

    }

    namespace Menu {

        ConstInt SCREEN_WIDTH(570);
        ConstInt SCREEN_HEIGHT(570);
        ConstStr SCREEN_TITLE("Bomberman | menu");

    }

    namespace Player {

        ConstInt SPEED("player.speed", 100);

    }

    namespace Bomb {

        ConstInt NUMBER("bomb.number", 2);
        ConstNum LIFE_TIME("bomb.life_time", 2);

    }

    namespace Explosion {

        ConstInt LENGTH("explosion.length", 2);
        ConstNum DELAY("explosion.delay", 0.1f);

    }

}
