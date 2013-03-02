#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "Utils/ConstTypes.h"

namespace Constants {

    namespace Video {

        extern ConstInt SCREEN_WIDTH;
        extern ConstInt SCREEN_HEIGHT;
        extern ConstStr SCREEN_TITLE;

    }

    namespace Menu {

        extern ConstInt SCREEN_WIDTH;
        extern ConstInt SCREEN_HEIGHT;
        extern ConstStr SCREEN_TITLE;

    }

    namespace Player {

        extern ConstInt SPEED;
        extern ConstInt HEALTH;
        extern ConstInt MAX_HEALTH;
        extern ConstNum BLINK_TIME;
        extern ConstNum IMMORTAL_TIME;

    }

    namespace Bomb {

        extern ConstInt START_AMOUNT;
        extern ConstInt MAX_AMOUNT;
        extern ConstNum LIFE_TIME;

    }

    namespace Explosion {

        extern ConstInt LENGTH;
        extern ConstNum DELAY;

    }

    namespace UI {

        namespace Avatar {

            extern ConstInt X;
            extern ConstInt Y;

        }

        namespace Scores {

        	extern ConstInt X;
        	extern ConstInt Y;

        }

        namespace HealthBar {

            extern ConstInt X;
            extern ConstInt Y;
            extern ConstInt LENGHT;
            extern ConstInt ALPHA;

        }

        namespace BombBar {

            extern ConstInt X;
            extern ConstInt Y;
            extern ConstInt OFFSET;
            extern ConstInt ALPHA;

        }

        namespace FPS {

            extern ConstInt X;
            extern ConstInt Y;
            extern ConstInt SIZE;

        }

    }

}

#endif /*__CONSTANTS_H__*/
